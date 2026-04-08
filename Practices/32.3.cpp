#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 2005; // 物理内存雷达极限
vector<int> adj[MAXN];
long long w[MAXN];
long long initial_W[MAXN]; // 初始全量后代权重和

// Euler Tour 空间雷达
int in_time[MAXN], out_time[MAXN];
int parent[MAXN];
int timer_cnt = 0;

// 引擎冷启动：探测全树物理拓扑
void dfs(int u) {
    in_time[u] = ++timer_cnt;
    initial_W[u] = w[u];
    for (int v : adj[u]) {
        dfs(v);
        initial_W[u] += initial_W[v]; // 能量向上聚合
    }
    out_time[u] = ++timer_cnt;
}

// O(1) 绝对空间判定：v 是否在 u 的子树的物理视界内
bool is_ancestor(int u, int v) {
    return in_time[u] <= in_time[v] && out_time[v] <= out_time[u];
}

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 2; i <= n; i++) {
        cin >> parent[i];
        adj[parent[i]].push_back(i);
    }

    // 启动雷达
    dfs(1);

    // 接受指挥部的高频查询
    for (int q = 0; q < m; q++) {
        int target;
        cin >> target;

        // 状态重置：每次查询都是一个新的平行宇宙
        vector<int> valid_nodes;
        for (int i = 1; i <= n; i++) valid_nodes.push_back(i);

        long long valid_weight[MAXN];
        for (int i = 1; i <= n; i++) valid_weight[i] = initial_W[i];

        long long total_W = initial_W[1];

        // 状态机运转：直到只剩下一个节点
        while (valid_nodes.size() > 1) {
            long long min_diff = -1;
            int best_u = -1;

            // 💥 寻找能量中枢：遍历当前有效节点
            for (int v : valid_nodes) {
                long long diff = abs(2 * valid_weight[v] - total_W);
                // 绝对判定与 ID 兜底
                if (min_diff == -1 || diff < min_diff || (diff == min_diff && v < best_u)) {
                    min_diff = diff;
                    best_u = v;
                }
            }//这里只需要最小值，不需要排序

            cout << best_u << " "; // 锁定提问目标

            // 💥 物理宇宙撕裂与坍缩
            if (is_ancestor(best_u, target)) {
                // 回答“是”：目标在子树内。总能量直接收缩。
                total_W = valid_weight[best_u];
                
                // 过滤出新的存活名单 (保留子树内)
                vector<int> next_valid;
                for (int v : valid_nodes) {
                    if (is_ancestor(best_u, v)) {
                        next_valid.push_back(v);
                    }
                }
                valid_nodes = next_valid;
                // 注意：这里绝对不需要更新 valid_weight！子树内部的相对引力场没有改变！
            } else {
                // 回答“否”：目标不在子树内。剔除该子树的能量。
                total_W -= valid_weight[best_u];
                
                // 💥 核心修正：只有 best_u 的祖先们失去了这部分能量
                int curr = parent[best_u];
                while (curr != 0) {
                    valid_weight[curr] -= valid_weight[best_u];
                    curr = parent[curr]; // 向上攀爬修正
                }
                
                // 过滤出新的存活名单 (剔除子树内)
                vector<int> next_valid;
                for (int v : valid_nodes) {
                    if (!is_ancestor(best_u, v)) {
                        next_valid.push_back(v);
                    }
                }
                valid_nodes = next_valid;
            }
        }
        cout << "\n";
    }
    return 0;
}