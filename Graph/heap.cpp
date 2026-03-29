#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;

// 邻接表：graph[u] 存储 {邻居 v, 权重 w}
vector<pair<int, int>> graph[100005]; 
int dist[100005];

int main() {
    // 性能装甲：切断 cin/cout 与 stdio 的绑定，极限加速 I/O
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m, s;
    cin >> n >> m >> s;
    
    // 1. 读入带权有向图
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    // 2. 极其悲观的雷达初始化
    for(int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[s] = 0; // 绝对的波源起步点

    // 3. 极其势利的绞肉机：小根堆 priority_queue
    // 绝对物理法则：存入的 pair 必须是 {距离, 城市编号}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    //greater减少循环
    pq.push({0, s});//核心初始值，将所有直接出发的值推到pq中

    // ==========================================
    // Dijkstra 核心松弛引擎启动
    // ==========================================
    while(!pq.empty()) {
        // 步骤 1：从堆顶（top）拿出距离最近的元素，绝对不用括号调用属性！
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop(); // 弹出堆顶
        
        // 步骤 2：懒惰删除防线（如果拿出的距离已经大于当前最短记录，直接抛弃）
        if(d > dist[u]) continue;

        // 步骤 3 & 4：工业级范围遍历，极其冷血的距离松弛
        for(auto edge : graph[u]) {
            int v = edge.first;  // 邻居
            int w = edge.second; // 边权
            
            // 发生松弛：如果走 u 这条路能比目前的记录更近
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v}); // 将更新后的状态塞进优先队列参与未来的插队竞争！
            }
        }
    }
    // ==========================================
    // 引擎停机
    // ==========================================

    // 4. 输出最终战果
    for(int i = 1; i <= n; i++) {
        if(dist[i] == INF) cout << 2147483647 << " ";
        else cout << dist[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
