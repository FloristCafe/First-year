#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
const ll INF = 1e18; // 💥 真正的物理无穷大！

struct Edge {
    int to;
    ll d, c;
};

vector<Edge> adj[10005];
ll dist[10005];  // 绝对雷达一：记录到每个节点的最短延迟
ll cost[10005];  // 绝对雷达二：记录这个节点【接入广播树】的那一条网线的最小成本

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        ll d, c;
        cin >> u >> v >> d >> c;
        adj[u].push_back({v, d, c});
        adj[v].push_back({u, d, c});
    }

    // 状态初始化
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        cost[i] = INF;
    }

    // 优先队列 {当前延迟, 当前节点}
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    
    dist[1] = 0;
    cost[1] = 0; // 首都节点不需要网线接入，成本为 0
    pq.push({0, 1});

    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto edge : adj[u]) {
            int v = edge.to;
            ll weight = edge.d;
            ll c = edge.c;

            // 💥 第一绝对法则：发现了更短的延迟！无条件覆盖！
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                cost[v] = c;  // 节点 v 接入树的成本，就是这根网线 c 的价格！绝不累加！
                pq.push({dist[v], v});
            }
            // 💥 第二绝对法则：延迟一样短！寻找更便宜的网线！
            else if (dist[v] == dist[u] + weight) {
                cost[v] = min(cost[v], c); // 贪心替换为更便宜的接入网线
            }
        }
    }

    // 终极结算：把所有节点（除了首都）的接入成本累加！
    ll total_cost = 0;
    for (int i = 2; i <= n; i++) {
        total_cost += cost[i];
    }

    cout << total_cost << "\n";
    return 0;
}