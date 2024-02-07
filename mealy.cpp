#include<bits/stdc++.h>
#include<fstream>
using namespace std;
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
string mealy(string input){
        fstream file("mealy.txt",ios::in);
        string line;
        vector<vector<int>>table;
     if(file.is_open()){
          while(getline(file,line)){
              vector<int>temp=eval(line);
              table.push_back(temp);
        }
    }
    file.close();
    string ans="";
    int currState=0,i=0;
    int n=input.length();
    int size=table[1].size()/2;
    while(currState!=-1&&i<n){
        if(input[i]-'0'>=size){
            return ans;
        }
        else{
            ans+=to_string(table[currState+1][(input[i]-'0')*2+1]);
            currState=table[currState+1][(input[i]-'0')*2];
        }
        i++;

    }
    return ans;
}

int main(){
    string input;
    cin>>input;
    string output=mealy(input);
    if(input.length()==output.length()){
        cout<<"string accepted -> "<<output<<endl;
    }
    else{
        cout<<"not accepted -> "<<output<<endl;
    }
}