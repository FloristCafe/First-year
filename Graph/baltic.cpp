#include<iostream>
#include<vector>
using namespace std;
vector<pair<int,int>>fa(1010);
int find(int x){
    if(fa[x].first()==x)return x;
    fa[x].first()=find(fa[x]);
    return fa[x].first;
}
int friend(int x,int y){
      int a=find(x);
      int b=find(y);
    if(a!=b){
        fa[a].first=b;
    }

    }
    

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    for(int i=0;i<n;i++){
        fa[i].first()=i;
        fa[i].second()=1;
    }
    for(int i=0;i<m;i++){
        char opt;
        int p,q;
        cin>>opt>>p>>q;

    }
}