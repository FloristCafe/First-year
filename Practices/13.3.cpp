#include<iostream>
#include<vector>

using namespace std;
struct node{
    vector<string>sa;
    string name;
};
vector<node> rules(102);
node div(string s){
    int l=1,r=1;
    node a;
    while(1){
        while(r!='/'&&r!=' '){
            r++;
        }
        if(s[r]==' '||s[r+1]==' ')break;
    string s1=s.substr(l,r-l);
    a.sa.push_back(s1);
    l=r+1;
    r=r+1;
    }
    if(s[r]!=' ')r++;
    a.name=s.substr(r+1);
    return a;
}
int main(){
    int n,m;
    cin>>n>>m;
    cin.ignore();
    for(int i=1;i<=n;i++){
    getline(cin,s);
    rules[i]=div(s);
    }
    for(int i=0;i<m;i++){
        
    }
}