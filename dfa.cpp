#include<bits/stdc++.h>
#include<fstream>
using namespace std;

bool find(vector<int>finalStates,int currState){
    for(int i=0;i<finalStates.size();i++){
               if(finalStates[i]==currState){
                return true;
               }
    }
    return false;
}
vector<int>eval(string line){
    vector<int>temp;
    int n=line.length();
    for(int i=0;i<n;i++){
        if(line[i]=='-'){
            temp.push_back(-1);
        }
        else{
            temp.push_back(line[i]-'0');
        }
    }
    return temp;
}
bool isAccepted(string input){
    fstream file("dfa.txt",ios::in);
    vector<vector<int>>table;
    string line;
    if(file.is_open()){
        while(getline(file,line)){
              vector<int>temp=eval(line);
              table.push_back(temp);
        }
    }
    file.close();
    int currState=0,n=input.length();
    int i=0,size=table[2].size();
    vector<int>finalStates=table[1];
    while(currState!=-1&&i<n){
        if(input[i]-'0'>=size){
            return 0;
        }
        else{
            currState=table[currState+2][input[i]-'0'];
        }
        i++;
    }
    if(find(finalStates,currState)){
        return true;
    }

    return false;
}
int main(){
    string input;
    getline(cin,input);
    if(isAccepted(input)){
        cout<<"Accepted"<<endl;
    }
    else{
        cout<<"rejected"<<endl;
    }
    return 0;
}