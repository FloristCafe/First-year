#include<iostream>
#include<vector>
#include<queue>
#define INF 0x3f3f3f3f
using namespace std;
int c[102];
int u[5005];
int v[5005];
int d[5005];
vector<pair<int,int>>adj[102];//前者距离
int dp[102][1<<9];
int color[33];//表示在路径上第几个出现的颜色
int main(){

   int n,m,l,k;
   cin>>n>>m>>l>>k;
    for(int i=0;i<n;i++){
        for(int t=0;t<(1<<(l));t++){
            dp[i][t]=INF;
        }
    }   
    dp[0][1]=1
   for(int i=0;i<n;i++){
    cin>>c[i];
   } 
   color[c[0]]=1;
   for(int i=0;i<m;i++){
    cin>>u[i];
   }
   for(int i=0;i<m;i++){
    cin>>v[i];
   }
   for(int i=0;i<m;i++){
    cin>>d[i];
   }
   for(int i=0;i<m;i++){
    adj[u[i]].push_back({d[i],v[i]});
   }

}