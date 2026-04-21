#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 2e14; // 绝对安全的时空上限预估
int N, M, K;
int demand[105][15];
vector<pair<int, long long>> adj[105];
long long cost[15][105];

// 物理探针：一次 DFS 算尽单车的悲欢离合
struct Result {
    bool has_demand;
    long long sum_edges;
    long long max_dist;
};

Result dfs(int u, int p, int k, long long current_dist) {
    // 初始状态：如果当前节点需要该食材，则将其记录入雷达
    Result res = {demand[u][k] == 1, 0, demand[u][k] ? current_dist : 0};
    
    for (auto& edge : adj[u]) {
        int v = edge.first;
        long long w = edge.second;
        if (v != p) {
            Result child_res = dfs(v, u, k, current_dist + w);
            // 如果子树中存在需求，当前这条边(u->v)必须被走两次（一去一回的势能基础）
            if (child_res.has_demand) {
                res.has_demand = true;
                res.sum_edges += child_res.sum_edges + 2 * w;
                res.max_dist = max(res.max_dist, child_res.max_dist);
            }
        }
    }
    return res;
}

// 降维打击核心：在时空死线 T 之下，检验系统的物理可能性
bool check(long long T) {
    vector<int> cover(N + 1, 0);
    // 1. 将每一个节点的救援能力压缩为二进制基因
    for (int u = 1; u <= N; ++u) {
        for (int k = 1; k <= K; ++k) {
            if (cost[k][u] <= T) {
                cover[u] |= (1 << (k - 1));
            }
        }
    }

    // 2. 状态压缩 DP：用最少的节点拼出全集
    int full_mask = (1 << K) - 1;
    vector<int> dp(full_mask + 1, 1e9);
    dp[0] = 0; // 初始宇宙：无任何食材被分配，消耗 0 个检查点

    for (int mask = 0; mask <= full_mask; ++mask) {
        if (dp[mask] >= 1e9) continue; // 过滤掉无法到达的虚空状态
        
        for (int u = 1; u <= N; ++u) {
            int nxt_mask = mask | cover[u];
            if (dp[nxt_mask] > dp[mask] + 1) {
                dp[nxt_mask] = dp[mask] + 1;
            }
        }
    }
    
    // 最终审判：所需的最小检查点是否在 M 的容忍范围之内
    return dp[full_mask] <= M;
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> N >> M >> K)) return 0;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= K; ++j) {
            cin >> demand[i][j];
        }
    }

    for (int i = 1; i < N; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // 💥 第一阶段：降维预处理，彻底解除图论遍历与二分答案的纠缠
    for (int k = 1; k <= K; ++k) {
        for (int u = 1; u <= N; ++u) {
            Result res = dfs(u, 0, k, 0);
            cost[k][u] = res.sum_edges - res.max_dist;
        }
    }

    // 💥 第二阶段：二分时间轴，进行绝对的物理碾压
    long long L = 0, R = 2e14; // 根据 N=100, W=10^6 推演的安全上限
    long long ans = R;

    while (L <= R) {
        long long mid = L + (R - L) / 2;
        if (check(mid)) {
            ans = mid;
            R = mid - 1; // 尝试继续压榨极限
        } else {
            L = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
