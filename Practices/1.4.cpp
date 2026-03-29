#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

// 物理基建：全局数组自动初始化为 0，极其干净
vector<int> adj[10005];
int in_degree[10005];
int t[10005];
int dp[10005]; 

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    // 💥 绝对纪律：先读取总控数据！
    if (!(cin >> n >> m)) return 0; 
    
    for(int i = 1; i <= n; i++){
       cin >> t[i];
    }

    int a, b;
    for(int i = 0; i < m; i++){
         cin >> a >> b;
         adj[a].push_back(b);
         in_degree[b]++;
    }
    
    // 普通队列即可，命名必须清晰
    queue<int> q; 
    for(int i = 1; i <= n; i++){
         if(in_degree[i] == 0){
            q.push(i);
         }
    }
    
    // 💥 绝对纪律：带好你的括号！
    while(!q.empty()){ 
        int u = q.front(); // 💥 绝对纪律：queue 用 front()
        q.pop();
        
        // 赋予绝对完成时间戳
        dp[u] += t[u]; 
        
        for(auto cd : adj[u]){
            in_degree[cd]--;
            // 变量名绝对统一：就是 u，不是 u1！
            dp[cd] = max(dp[cd], dp[u]); 
            if(in_degree[cd] == 0) q.push(cd);
        }
    }
    
    int max_time = 0;
    for(int i = 1; i <= n; i++){
        max_time = max(max_time, dp[i]);
    }
    
    cout << max_time << "\n";
    return 0;
}