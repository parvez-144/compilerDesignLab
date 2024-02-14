#include<bits/stdc++.h>
#include<fstream>
using namespace std;

vector<vector<int>> evaluate(string currLine){
    vector<vector<int>>toRet;
    int n=currLine.length();
    int i=0;
    while(i<n){
        while(i<n && currLine[i]==' '){
            i++;
        }
        vector<int>temp;
        bool flag=0;
        while(i<n&&currLine[i]!=' '){
            flag=1;
            if(currLine[i]==','){
               i++;
               continue;
            }   
            else if(currLine[i]=='-'){
                temp.push_back(-1);
            }
            else{
                temp.push_back(currLine[i]-'0');
            }
            i++;
        }
        if(flag){
            toRet.push_back(temp);
        }
        i++;
    }
    return toRet;
    
}
 void Print(vector<vector<vector<int>>>table){
    for(auto i:table){
        for(auto j:i){
            for(auto k:j){
                cout<<k<<",";
            }
            cout<<" ";
        }
        cout<<endl;
    }
 }


void NFA_to_DFA(){

    fstream file("NFA_Table.txt",ios::in);
    string currLine;
    vector<vector<vector<int>>>nfaTable;

    if(file.is_open()){
        while(getline(file,currLine)){
              vector<vector<int>>temp=evaluate(currLine);
              nfaTable.push_back(temp);
        }
    }
    file.close();

    vector<int>fStates=nfaTable[1][0];
    unordered_map<string,bool>mp;
    int n=nfaTable.size();
    bool newState=1;

    mp[to_string(-1)]=1;
    for(int i=2;i<n;i++){
       mp[to_string((i-2))]=1;
    }
    Print(nfaTable);
    cout<<"hello"<<endl;
    int sz=nfaTable[2].size();
    for(int i=2;i<nfaTable.size();i++){
        for(int j=0;j<nfaTable[i].size();j++){
            string temp="";
            for(int t=0;t<nfaTable[i][j].size();t++){
                temp+=to_string(nfaTable[i][j][t]);
            }
            if(!mp[temp]){           
               vector<vector<int>>newEntry;
               for(int k=0;k<sz;k++){
                set<int>st;
                for(int l=0;l<temp.size();l++){
                    for(int m=0;m<nfaTable[l-'0'][k].size();m++){
                        st.insert(nfaTable[l-'0'][k][m]);
                    }

                }
                vector<int>newSt;
                for(auto it:st){
                    newSt.push_back(it);
                }
                newEntry.push_back(newSt);
               }
               nfaTable.push_back(newEntry);
            }
        }

    }

    cout<<"hello"<<endl;
    Print(nfaTable);
}
int main(){
    NFA_to_DFA();
    return 0;
}