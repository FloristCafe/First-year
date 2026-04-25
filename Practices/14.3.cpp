#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<algorithm>
#include<sstream>
using namespace std;
struct node{
   vector<pair<string,string>>ance;//祖先的标签，id
   string name;
   string id;
};
bool check1(vector<pair<string,string>>a,vector<string>b){
    size_t cur=0;
    size_t l=0;
    while(cur<b.size()){
        string s=b[cur];
        if(s[0]=='#'){
          while(l<a.size()&&a[l].second!=s)l++;
          if(l==a.size())return false;
          
        }else{
          while(l<a.size()&&a[l].first!=s)l++;
          if(l==a.size())return false;
        
        }
        l++;
        cur++;
    }
    return true;
}
vector<node>tree(103);
int main(){
    int n,m;
    cin>>n>>m;
    vector<int>a(100);
    cin.ignore();
    for(int i=1;i<=n;i++){
        string s;
    getline(cin,s);
    int num=0;
    while(s[num]=='.')num++;
    int cur=num/2;
    while(s[num]!=' '&&s[num]!='\n'&&num<(int)s.size())num++;
    string name1=s.substr(2*cur,num-2*cur);
    a[cur]=i;
    if(cur>0){
        tree[i].ance=tree[a[cur-1]].ance;
        tree[i].ance.push_back({tree[a[cur-1]].name,tree[a[cur-1]].id});
    }
    tree[i].name=name1;
    if(num<(int)s.size()){
        if(s[num]==' '&&s[num+1]=='#'){
            string id1=s.substr(num+1);
        
        tree[i].id=id1;
            }    }
    }
    for(int i=0;i<m;i++){
    string s;
    getline(cin,s);
    stringstream ss(s);
    vector<string>ope;
    string s1;
    vector<set<int>>sets;
    while(ss>>s1){
       ope.push_back(s1);
    }
    ope.pop_back();
    vector<int>get;
    for(int j=1;j<=n;j++){
        if(s1[0]=='#'){
        if(tree[j].id!=s1)continue;
        }else{
    if(tree[j].name!=s1)continue;
        }
    if(check1(tree[j].ance,ope)){
     get.push_back(j);
    }
    }
    cout<<get.size();
    for(size_t j=0;j<get.size();j++){
        cout<<" ";
        cout<<get[j];
    }
    cout<<endl;
    }
    return 0;
}