#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
int N,pq;
const int INF = 1e9;
// 邻接表：存的是 pair<目标节点 v, 边权 w>
vector<pair<int, int>> adj[N]; 

int dist[N]; // 距离数组，初始已全部设定为 INF
bool vis[N]; // 锁定装甲，初始已全部设定为 false

// 💥 终极武器：绝对小根堆！
// 存的是 pair<距离 d, 节点编号 u>。注意：必须把距离 d 放在 first，因为 pair 默认按 first 排序！
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

dist[S] = 0;
pq.push({0, S}); // 起点入堆
while (!pq.empty()) {
    int d = pq.top().first;
    int u = pq.top().second;
    pq.pop();

    // 1. 终极防爆判定：用物理距离直接拦截历史垃圾数据，连 vis 数组都可以省掉！
    if (d > dist[u]) continue; 

    // 2. 战术松弛：遍历下属
    // 使用 auto& edge 直接拿到 pair，或者在 C++17 中直接用 auto [v, w]
    for (auto& edge : adj[u]) {
        int v = edge.first;  // 绝对清醒：adj 的 first 是目标节点
        int w = edge.second; // 绝对清醒：adj 的 second 是边权/耗时

        // 3. 贪心波纹扩散：如果借道 u 能让到达 v 的时间更短
        if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            
            // 压入小根堆。绝对清醒：pq 的 first 必须是距离，second 是节点！
            pq.push({dist[v], v}); 
        }
    }
}