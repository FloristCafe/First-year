#include<iostream>
#include<vector>
using namespace std;
int fa[1000010];
int find(int x){
    if(fa[x]==x)return x;
    fa[x]=find(fa[x]);
    return fa[x];
    
}
void join(int x,int y){
    int g=find(x);
    int h=find(y);
    if(g!=h){
fa[g]=h;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        if(fa[b]==0)fa[b]=b;
        if(fa[c]==0)fa[c]=c;
        if(a==1){
            join(b,c);
        }
        else{
            if(find(b)==find(c))cout<<"Y"<<endl;
            else{
                cout<<"N"<<endl;
            }
        }
    }
    return 0;
}