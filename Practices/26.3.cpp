#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>
using namespace std;
struct character{
    set<string>ope;
    set<string>type;
    set<string>names;
};
map<string,character>all_char;
map<string,vector<string>>connect_mem;
map<string,vector<string>>connect_group;
int main(){
   int n,m,q;
   cin>>n>>m>>q;
   for(int j=0;j<n;j++){
    string name,ope,type,names;
    set<string>ope1;
    set<string>type1;
    set<string>names1;    
    int nv,no,nn;
    cin>>name>>nv;
    for(int i=0;i<nv;i++){
        cin>>ope;
        ope1.insert(ope);
    }
    cin>>no;
    for(int i=0;i<no;i++){
        cin>>type;
        type1.insert(type);
    }
    cin>>nn;
    for(int i=0;i<nn;i++){
        cin>>names;
        names1.insert(names);
    }
all_char[name]={ope1,type1,names1};
   }
   for(int i=0;i<m;i++){
    string name,a,aname;
    cin>>name;
    int ns;
    cin>>ns;
    for(int j=0;j<ns;j++){
      cin>>a>>aname;

      if(a=="g"){
         connect_group[aname].push_back(name);
      }
      if(a=="u"){
        connect_mem[aname].push_back(name);
      }
    }
   }
   for(int i=0;i<q;i++){
    string mem;
    vector<string>groups;
    int ng=0;
    string ope,type,names;
    cin>>mem>>ng;
    for(int j=0;j<ng;j++){
        string gro;
        cin>>gro;
        groups.push_back(gro);

    }
    cin>>ope>>type>>names;
    int decide=0;
    for(string mid:connect_mem[mem]){
        character char1=all_char[mid];
        if(char1.ope.find(ope)==char1.ope.end()&&char1.ope.find("*")==char1.ope.end()){
           continue;
        }
        if(char1.type.find(type)!=char1.type.end()||char1.type.find("*")!=char1.type.end()){
          cout<<"1"<<endl;
        decide=1;
        break;
        }
        if(char1.names.find(names)!=char1.names.end()){
        cout<<"1"<<endl;
        decide=1;
        break;
        }
    }
    if(decide==1)continue;
    for(string gro:groups){
    for(string mid:connect_group[gro]){
        character char1=all_char[mid];
        if(char1.ope.find(ope)==char1.ope.end()){
             continue;
        }
        if(char1.type.find(type)!=char1.type.end()){
          cout<<"1"<<endl;
        decide=1;
        break;
        }
        if(char1.names.find(names)!=char1.names.end()){
        cout<<"1"<<endl;
        decide=1;
        break;
        }
    }
    if(decide==1)break;
    }
    if(decide==1)continue;
    cout<<"0"<<endl;
   }
   return 0;
}