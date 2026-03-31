#include<iostream>
#include<vector>
#include<queue>
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;
int n,m;
struct node{
    int pos;
    int d;
    ll  c;
    bool operator>(const node & other)const{
        if(d==other.d)return c>other.c;
        return d>other.d;
    }
};
vector<pair<int,ll>>dp(10005);//前者延迟，后者维护成本
vector<node>adj[10005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    int u,v,d1;
    ll c1;
    for(int i=0;i<m;i++){
        cin>>u>>v>>d1>>c1;
        adj[u].push_back({v,d1,c1});
        adj[v].push_back({u,d1,c1});
    }
    for(int i=2;i<=n;i++){
        dp[i].first=INF;
        dp[i].second=INF;
    }
    dp[1].first=0;
    dp[1].second=0;
    priority_queue<node,vector<node>,greater<node>>pq;
    pq.push({1,0,0});
    while(!pq.empty()){
      int pos0=pq.top().pos;
      int d0=pq.top().d;
      ll c0=pq.top().c;
      pq.pop();
      if(d0>dp[pos0].first)continue;
      if(c0>dp[pos0].second)continue;
      for(auto cd:adj[pos0]){
    int pos2=cd.pos;
    int d2=cd.d;
    ll c2=cd.c;
    if(dp[pos2].first>d0+d2){
        dp[pos2].first=d0+d2;
        dp[pos2].second=c0+c2;
        pq.push({pos2,dp[pos2].first,dp[pos2].second});
    }
    if((dp[pos2].first==d0+d2)&&dp[pos2].second>c0+c2){
        dp[pos2].first=d0+d2;
        dp[pos2].second=c0+c2;
        pq.push({pos2,dp[pos2].first,dp[pos2].second});
    }
      }
    }
    ll maxt=0;
    for(int i=1;i<=n;i++){
        maxt=max(maxt,dp[i].second);
    }
    cout<<maxt<<endl;
    return 0;
}