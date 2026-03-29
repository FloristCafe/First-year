#include<iostream>
#include<vector>
using namespace std;
vector<int>adj[100005];
bool visited[100005]={false};
void dfs(int u){
    visited[u]=true;
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];

        if(!visited[v]){
            dfs[v];
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        if(!visited[i]){
            dfs(i);
        }
    }
    return 0;
}