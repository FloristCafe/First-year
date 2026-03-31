#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n, m;
int t[10005];
int in_degree[10005]; // 💥 绝对核心：入度雷达（记录每个组件还有多少个前置依赖没完成）
int dp[10005];        // 记录组件的【最早完成时间】
vector<int> adj[10005];

int main() {
    // 解除物理封锁
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++; // 💥 物理挂载：v 的前置依赖数量 + 1
    }

    queue<int> q; // 普通队列足矣，不需要存时间，时间在 dp 数组里
    int processed_count = 0; // 死锁探测器

    // 第一波点火：所有【零依赖】的源头组件，立刻并发启动
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
            dp[i] = t[i]; // 源头组件的完成时间就是它自己的耗时
        }
    }

    // 引擎运转
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        processed_count++; // 💥 成功彻底编译完一个组件！

        // 当前组件编译完了，通知所有依赖它的下游组件
        for (int next_node : adj[curr]) {
            // 状态转移：下游的最早完成时间，取决于它所有前置里最晚的那个
            dp[next_node] = max(dp[next_node], dp[curr] + t[next_node]);

            in_degree[next_node]--; // 💥 核心物理法则：解除一层依赖封锁！

            // 只有当该组件的【所有前置依赖】都彻底完成（入度清零），才允许进入启动队列！
            if (in_degree[next_node] == 0) {
                q.push(next_node);
            }
        }
    }

    // 💥 死锁绝对探测：如果吐出的组件数少于总数 N，说明有组件被卡在环里（入度永远无法清零）
    if (processed_count != n) {
        cout << "-1\n";
        return 0;
    }

    // 结算总耗时：所有组件完成时间的最大值
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }

    cout << ans << "\n";
    return 0;
}