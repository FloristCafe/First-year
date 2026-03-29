
#include<iostream>
#include<set>
#include<vector>
using namespace std;
#define N 1005
set<int>ch;
int fa[2050]={0};
int find(int x){
    if(fa[x]==x)return x;
    fa[x]=find(fa[x]);
    return fa[x];
}
void join(int a,int b){
    int x=find(a);
    int y=find(b);
    if(x!=y){
    fa[x]=y;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    char opt;
    int p,q;
    for(int i=1;i<=n;i++){
        fa[i]=i;
        fa[N+i]=N+i;
    }
    for(int i=0;i<m;i++){
cin>>opt>>p>>q;
if(opt=='F'){
    join(p,q);
}else{
    join(p+N,q);
    join(p,q+N);
}
    }
    for(int i=1;i<=n;i++){
ch.insert(find(i));     
    }

    cout<<ch.size()<<endl;
    return 0;
}