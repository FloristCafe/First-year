#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
int n, m, k;

// 绝对防爆：用原生数组彻底取代缓慢的 map
int cost[10005][11];           // 城镇建设成本
int wire[1005][1005][11][11];  // 连线成本 (如果 N 很大，这里需要用邻接表里的 struct 存)
int dp[10005][11];             // 核心雷达：dp[u][i]
vector<int> adj[10005];        // 图的邻接表

// 核心引擎：后序遍历 DFS
void dfs(int u, int p) { // u 是当前节点，p 是物理父亲（防止走回头路）
    
    // 1. 初始化当前节点的造价：哪怕它没有儿子，它也得花自己的钱
    for (int i = 1; i <= k; i++) {
        dp[u][i] = cost[u][i];
    }

    // 2. 遍历所有的儿子
    for (int v : adj[u]) {
        if (v == p) continue; // 绝对纪律：不能连回父亲！
        
        dfs(v, u); // 💥 递归深潜！等这行代码执行完，儿子 v 的 dp 数组就已经全部算好了！

        // 3. 儿子算完了，开始将儿子 v 的能量聚合到父亲 u 身上
        for (int i = 1; i <= k; i++) {       // 枚举父亲 u 的所有状态 i
            int min_cost_from_v = INF;
            for (int j = 1; j <= k; j++) {   // 枚举儿子 v 的所有状态 j
                // 找出儿子 v 在状态 j 下，连到父亲 u(状态 i) 的最低代价
                min_cost_from_v = min(min_cost_from_v, dp[v][j] + wire[u][v][i][j]);
            }
            // 💥 绝对法则：是累加 (+)，不是覆盖 (min)！
            // 父亲 u 在状态 i 下的总代价，必须加上连接这个儿子 v 的最低代价！
            dp[u][i] += min_cost_from_v; 
        }
    }
}

// main 函数中：
// dfs(1, 0); // 从根节点 1 点火
// int ans = INF;
// for(int i=1; i<=k; i++) ans = min(ans, dp[1][i]); // 最后求所有合法状态的最小值