#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 💥 维度跃迁：涉及路径长度，必须全局 long long！
typedef long long ll;
const ll INF = 1e18; // 真正的物理无穷大

int n, m;
ll max_b; // 最大容忍延迟
int c[10005]; // 警告级别
vector<pair<ll, int>> adj[10005]; // {延迟, 目标节点}

// 雷达探测引擎：在特权码 X 下，能否在 max_b 内到达终点
bool check(int X) {
    // 💥 起点/终点防爆：如果起终点本身就超权限，直接阵亡
    if (c[1] > X || c[n] > X) return false;

    vector<ll> dp(n + 1, INF);
    // 绝对法则：优先队列 {距离, 节点}，必须用 top()！
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dp[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop(); // 💥 普通队列 front，优先队列 top，刻在 DNA 里！

        if (d > dp[u]) continue; // 历史废料清理

        // 核心剪枝：如果当前延迟已经超过限制，没必要继续走了
        if (d > max_b) continue;

        for (auto edge : adj[u]) {
            ll w = edge.first;
            int v = edge.second;

            // 💥 审查协议拦截：节点 v 的安全级别高于特权 X，绝对不可通行
            if (c[v] > X) continue;

            if (dp[v] > d + w) {
                dp[v] = d + w;
                pq.push({dp[v], v}); // {距离, 节点}
            }
        }
    }

    return dp[n] <= max_b;
}

int main() {
    // I/O 解除物理限制
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m >> max_b)) return 0;

    int max_c = 0;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        max_c = max(max_c, c[i]);
    }

    int u, v;
    ll l;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> l;
        adj[u].push_back({l, v});
        adj[v].push_back({l, u});
    }

    // 提前雷达扫描：如果给你无穷大的权限你都到不了，那就彻底没救了
    if (!check(max_c)) {
        cout << "-1\n";
        return 0;
    }

    // 引擎点火：二分特权码区间
    int left = 1, right = max_c, ans = max_c;
    while (left <= right) {
        int mid = left + (right - left) / 2; // 防溢出写法
        if (check(mid)) {
            ans = mid;       // 记录当前成功解
            right = mid - 1; // 尝试寻找更小的特权码
        } else {
            left = mid + 1;  // 权限太小走不通，只能提权
        }
    }

    cout << ans << "\n";
    return 0;
}