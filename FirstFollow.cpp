#include <bits/stdc++.h>
#include <fstream>
using namespace std;
void tableMakin(string &line, unordered_map<char, vector<string>> &mp)
{
    int l = line.length();
    mp[line[0]].push_back(line.substr(3, l - 3));
}
void First(char ch, unordered_map<char, vector<string>> mp, unordered_map<char, set<char>> &firsts)
{
    if (!(ch >= 'A' && ch <= 'Z'))
    {
        firsts[ch].insert(ch);
    }
    for (auto it : mp[ch])
    {

        for (int i = 0; i < it.length(); i++)
        {
            if (it[i] == ch)
            {
                break;
            }
            First(it[i], mp, firsts);
            bool flag = true;
            for (auto itr : firsts[it[i]])
            {
                if (itr == '#')
                {
                    flag = false;
                }
                if (itr != '#')
                {
                    firsts[ch].insert(itr);
                }
                else if (i == it.length() - 1)
                {
                    firsts[ch].insert('#');
                }
            }
            if (flag)
            {
                break;
            }
        }
    }
}
void Follow(char ch, unordered_map<char, vector<string>> mp, unordered_map<char, set<char>> firsts, unordered_map<char, set<char>> &follow)
{
    for (auto i : mp)
    {
        for (auto j : i.second)
        {
            for (int k = 0; k < j.length(); k++)
            {
                if (j[k] == ch)
                {
                    for (int l = k+1; l <= j.length(); l++)
                    {
                        bool flag = true;
                        if (l < j.length())
                        {
                            if (j[l] <= 'Z' && j[l] >= 'A')
                            {
                                for (auto it : firsts[j[l]])
                                {
                                    if (it != '#')
                                    {
                                        follow[ch].insert(it);
                                    }
                                    else
                                        flag = false;
                                }
                            }
                            else
                            {
                                follow[ch].insert(j[l]);
                                break;
                            }
                        }
                        else{
                            if(i.first==ch){
                                break;
                            }
                            Follow(i.first,mp,firsts,follow);
                            for(auto it:follow[i.first]){
                                follow[ch].insert(it);
                            }
                        }
                        if(flag){
                            break;
                        }
                    }
                }
            }
        }
    }
}
void printGrammer(unordered_map<char, vector<string>> mp)
{
    for (auto i : mp)
    {
        cout << i.first << " -> ";
        for (auto it : i.second)
        {
            cout << it << " | ";
        }
        cout << endl;
    }
}
int main()
{
    unordered_map<char, vector<string>> mp;
    fstream file("FirstFollow.txt", ios::in);
    string currLine;
    vector<vector<vector<int>>> nfaTable;
    unordered_map<char, set<char>> firsts;
    unordered_map<char,set<char>>follow;

    if (file.is_open())
    {
        while (getline(file, currLine))
        {
            tableMakin(currLine, mp);
        }
    }
    file.close();
    printGrammer(mp);
    cout << endl
         << endl;
    for (auto it : mp)
    {
        First(it.first, mp, firsts);
    }

    for (auto it : firsts)
    {
        if (it.first >= 'A' && it.first <= 'Z')
        {
            cout << it.first << " -> ";
            for (auto i : it.second)
            {
                cout << i << " , ";
            }
            cout << endl;
        }
    }
     cout << endl
         << endl;
    follow['S'].insert('$');
    for(auto i:mp){
       
        Follow(i.first,mp,firsts,follow);
    }

      for (auto it : follow)
    {
        if (it.first >= 'A' && it.first <= 'Z')
        {
            cout << it.first << " -> ";
            for (auto i : it.second)
            {
                cout << i << " , ";
            }
            cout << endl;
        }
    }
    return 0;
}