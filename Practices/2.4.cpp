#include<iostream>
#include<vector>
#include<queue>
#include<map>
#define INF 0x3f3f3f3f
using namespace std;
struct node{
    int first;
    int second;
    int third;
    bool operator>(const node & other)const{
        if(first==other.first)return third>other.third;
    return first>other.first;
    }
};
int dp[10005][12];
vector<pair<int,int>>adj[10005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
priority_queue<node,vector<node>,greater<node>>pq;
//前者距离，后者点位

    int n,m,k;
    cin>>n>>m>>k;
    int s,t;
    cin>>s>>t;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=k;j++){
    dp[i][j]=INF;
        }
    }
    int u,v,w;
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
adj[u].push_back({w,v});
adj[v].push_back({w,u});
    }
// 物理锚点锁定
    dp[s][0] = 0;
    pq.push({0, s, 0});
    
    // ... 读入边的代码保持不变 ...

    while(!pq.empty()){
        int d1 = pq.top().first;
        int u1 = pq.top().second;
        int k1 = pq.top().third;
        pq.pop();
        
        // 核心剪枝：如果这个状态已经是历史废料，直接丢弃
        if(d1 > dp[u1][k1]) continue;
        
        for(auto cd : adj[u1]){
            int v = cd.second;
            int w = cd.first;
            
            // 路径 1：像凡人一样步行（不使用特权，正常增加延迟）
            if(dp[v][k1] > d1 + w){
                dp[v][k1] = d1 + w;
                pq.push({dp[v][k1], v, k1});
            }
            
            // 路径 2：开启量子隧道（使用一次特权，跨越这条边，延迟增加 0！）
            if(k1 < k && dp[v][k1 + 1] > d1){
                dp[v][k1 + 1] = d1; // 距离依然是 d1！
                pq.push({d1, v, k1 + 1});
            }
        }
    }
int minx=INF;
for(int i=0;i<=k;i++){
    minx=min(minx,dp[t][i]);
}
cout<<minx<<endl;
return 0;

}