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

string moore(string input){
       fstream file("moore.txt",ios::in);
        string line;
        vector<vector<int>>table;
     if(file.is_open()){
          while(getline(file,line)){
              vector<int>temp=eval(line);
              table.push_back(temp);
        }
    }
    file.close();
    int currState=0,n=input.length();
    int i=0,size=table[1].size()-1;
    string ans="";
    while(currState!=-1&&i<n){
        ans+=to_string(table[currState+1][size]);
        if(input[i]-'0'>=size){
            return ans;
        }
        currState=table[currState+1][input[i]-'0'];
        i++;
    }
    if(currState!=-1){
       ans+=to_string(table[currState+1][size]);
    }
    return ans;
}

int main(){
    string input;
    cin>>input;
    cout<<input<<endl;
    string output=moore(input);
    if(input.length()+1==output.length()){
        cout<<"string is Accepted the output is "<<output<<endl;
    }
    else{
        cout<<"invalid input output is -->"<<output<<endl;
    }
}