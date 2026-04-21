#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include<string>
#include<algorithm>
#define ll long long
unordered_map<string,vector<string>>file;//子文件
unordered_map<string,vector<string>>files;//子文件夹
unordered_map<string,ll>file_size;
unordered_map<string,ll>restrict;
unordered_map<string,ll>restrict1;//子配额
using namespace std;
void clears(string s){
    restrict[s]=0;
    for(size_t i=0;i<files[s].size();i++){
        clears(files[s][i]);
        files[s].clear();
        file_size[files[s][i]]=0;
    }
    for(size_t i=0;i<file[s].size();i++){
        file_size[file[s][i]]=0;
    }
    file[s].clear();
    return ;

}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
    char decide;
    cin>>decide;
    if(decide=='C'){
    string line; 
    int siz;
    cin>>line>>siz;
    if(file[line].size()>0||files[line].size()>0){
        cout<<"N"<<endl;
        continue;
    }
    string s1,s2;
    s1=line;
    size_t pos=s1.find('/');
    s2=s1;
    s1=s1.substr(0,pos);
    if(restrict[s1]>0&&restrict[s1]<file_size[s1]+siz-file_size[s2]){
        cout<<"N"<<endl;
        continue;
    }
while(1){
    pos=s1.find('/');
    if(pos==0)break;
    s2=s1;
    s1=s1.substr(0,pos);
    if(file[s1].find(s2)!=file[s1].end()){
        cout<<"N"<<endl;
        break;
        continue;
    }
    if(restrict[s2]>0&&restrict[s2]<file_size[s2]+siz-file_size[line]){
           cout<<"N"<<endl;
        break;
        continue;
    }
}
s1=line;
s2=s1;
pos=s1.find('/');
s1=s1.substr(0,pos);
ll cur=0;
if(file[s1].find(s2)!=file[s1].end()){
    cur=siz-file_size[s2];
    file_size[s2]=siz;
}else{
    file[s1].push_back(s2);
    cur=siz;
    file_size[s2]=siz;
}     
    while(1){
     pos=s1.find('/');
    if(pos==0)break;
    s2=s1;
    s1=s1.substr(0,pos);
    if(files[s1].find(s2)==files[s1].end())files[s1].push_back(s2);
    file_size[s1]+=cur; 
}
cout<<"Y"<<endl;
    }
    if(decide=='R'){
string line;
size_t pos=line.find('/');
string s1=line.substr(0,pos);
for(size_t ss=0;ss<files[s1].size();ss++){
    if(files[s1][ss]==line){
        files[s1].erase(file[s1].begin()+ss);
        restrict[line]=0;
        clears(line);
    break;
    }
}
for(string ss:file[s1]){
    if(ss==line){
        file_size[line]=0;
   file[s1].erase(file[s1].begin()+ss);
   break;
    }
}
cout<<"Y"<<endl;
    }
    if(decide=='Q'){
string line;
int res1,res2;

    }
    }
    return 0;
}