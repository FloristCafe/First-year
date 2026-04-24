#include<iostream>
#include<vector>
#include<queue>
using namespace std;
vector<int>a(200005);
vector<int>adj[200005];
vector<int>fa(200005);
vector<int>fa1(200005);
struct node{
   int min1;//子树最小值
   int min2;//父直链最小值--到上一个fa1[u]
};
vector<node>tree(200005);
vector<bool>visited(200005,false);
node dfs(int i){

}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    //dfs判定fa[u]fa1[u]
    queue<pair<int,int>>q;
    visited[1]=true;
    fa[1]=1;
    fa1[1]=1;
    if(adj[j].size()>1)q.push({1,1});
    else q.push({1,-1});//如果为-1，fa1直接继承
    while(!q.empty()){
        int a=q.front().first;
        int mark=q.front().second;
        if(mark==1){
   fa1[a]=fa[a];
        }else{
  fa1[a]=fa1[fa[a]];
        }
        if(adj[a].size()>2){
        for(int c:adj[a]){
            if(visited[c])continue;
            fa[c]=a;
            visited[c]=true;
            q.push({c,1});
        }
        }else{

        for(int c:adj[a]){
            if(visited[c])continue;
            q.push({c,-1});
        fa[c]=a;
        visited[c]=true;
        }
        }
    }
    dfs(1);
    
}