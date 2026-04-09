#include<iostream>
#include<vector>
#include<algorithm>
#include<cctype>
#include<set>
using namespace std;
set<string>a;
set<string>b;
set<string>ss;
int main(){
    int n,m;
    cin>>n>>m;
    string s;
    for(int i=0;i<n;i++){
        cin>>s;
        for(char &c:s){
            c=tolower(c);
        }
        a.insert(s);
        ss.insert(s);
    }
    for(int i=0;i<m;i++){
        cin>>s;
        for(char &c:s){
            c=tolower(c);
        }
        b.insert(s);
        ss.insert(s);
    }
    cout<<b.size()+a.size()-ss.size()<<endl;
    cout<<ss.size()<<endl;
    return 0;

}