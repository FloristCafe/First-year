#include<iostream>
#include<vector>

using namespace std;
vector<int>a(10005);
vector<int>s(105,-1);
vector<vector<int>>ss(105);
vector<int>t(105,-1);
vector<vector<int>>tt(105);
int check(vector<int>n,vector<int>m){
    if(n.size()!=m.size()){
        return 0;
    }
    for(size_t i=0;i<n.size();i++){
        if(n[i]!=m[i])return 0;
    }
    return 1;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=0;i<m;i++){
        int num;
        cin>>num;
        ss[i].reserve(num);
        for(int j=0;j<num;j++){
            if(s[i]==-1){
        cin>>s[i];
        s[i]=a[s[i]];
        ss[i].push_back(s[i]);
            }else{
        int mid;
        cin>>mid;
        s[i]=s[i]^a[mid];
        ss[i].push_back(mid);
            }
        }

    }
    for(int i=0;i<m;i++){
        int num;
        cin>>num;
        tt[i].reserve(num);
        for(int j=0;j<num;j++){
            if(t[i]==-1){
        cin>>t[i];
        t[i]=a[t[i]];
        tt[i].push_back(t[i]);
            }else{
        int mid;
        cin>>mid;
        t[i]=t[i]^a[mid];
        tt[i].push_back(mid);
            }
        }

    }
    for(int i=0;i<m;i++){
       if(t[i]==s[i]&&check(tt[i],ss[i])){
        cout<<"correct"<<endl;
    continue;   
    }
    if((t[i]!=s[i])&&check(tt[i],ss[i])==0){
        cout<<"correct"<<endl;
    continue;   
    }
    cout<<"wrong"<<endl;

    }
    return 0;
    
}