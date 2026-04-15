#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

// === 原图与圆方树底座 ===
vector<int> adj[MAXN];
vector<int> bct[MAXN * 2];
int dfn[MAXN], low[MAXN], timer;
int stk[MAXN], top;
int bcc_cnt;

// === 树上倍增雷达与拓扑记录 ===
int v_dfn[MAXN * 2], v_timer;
int dep[MAXN * 2], Rdep[MAXN * 2]; // Rdep 记录从根到该节点路径上的“圆点”数量
int up[MAXN * 2][20];

// === 虚树引擎 ===
vector<int> vt[MAXN * 2];
vector<int> nodes_in_vt;
int sz[MAXN * 2];
bool in_S[MAXN * 2];
int C; // 当前攻略的博物馆总数
long long total_ans;
long long count_processed;

// 1. Tarjan 拓扑坍缩：构建圆方树
void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    stk[++top] = u;
    for (int v : adj[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                bcc_cnt++;
                while (true) {
                    int w = stk[top--];
                    bct[bcc_cnt].push_back(w);
                    bct[w].push_back(bcc_cnt);
                    if (w == v) break;
                }
                bct[bcc_cnt].push_back(u);
                bct[u].push_back(bcc_cnt);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// 2. 空间测绘：DFS 获取虚树所需序列和倍增 LCA 表
void dfs_bct(int u, int p) {
    v_dfn[u] = ++v_timer;
    dep[u] = dep[p] + 1;
    Rdep[u] = Rdep[p] + (u <= bcc_cnt / 2 ? 1 : 0); // u <= 原始 n 说明是圆点
    up[u][0] = p;
    for (int i = 1; i < 20; i++) {
        up[u][i] = up[up[u][i-1]][i-1];
    }
    for (int v : bct[u]) {
        if (v != p) dfs_bct(v, u);
    }
}

// 绝对防爆 LCA 雷达
int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 19; i >= 0; i--) {
        if (dep[up[u][i]] >= dep[v]) u = up[u][i];
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

// 3. 虚树状态机：动态演算删点代价
void dfs_dp(int u, int n) {
    sz[u] = in_S[u] ? 1 : 0;
    if (u <= n) count_processed++; // 统计处理过的圆点
    
    long long max_branch = 0;
    
    for (int v : vt[u]) {
        dfs_dp(v, n);
        sz[u] += sz[v];
        max_branch = max(max_branch, (long long)sz[v]);
        
        // 物理缝合：处理被压缩在虚树边上的隐藏圆点
        long long internal_round = Rdep[v] - Rdep[u] - (v <= n ? 1 : 0);
        if (internal_round > 0) {
            count_processed += internal_round;
            long long val = max((long long)sz[v], (long long)C - sz[v]);
            total_ans += internal_round * val;
        }
    }
    
    if (u <= n) {
        long long up_branch = C - sz[u];
        max_branch = max(max_branch, up_branch);
        total_ans += max_branch;
    }
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;
    
    bcc_cnt = n; // 方点编号从 n+1 开始
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // 启动坍缩引擎
    tarjan(1);
    dfs_bct(1, 0);
    
    vector<int> S;
    int vt_stk[MAXN * 2];
    
    for (int query = 0; query < q; query++) {
        cin >> C;
        S.resize(C);
        for (int i = 0; i < C; i++) {
            cin >> S[i];
            in_S[S[i]] = true;
        }
        
        // 构建虚树：按照 DFS 序排序
        auto cmp = [](int a, int b) { return v_dfn[a] < v_dfn[b]; };
        sort(S.begin(), S.end(), cmp);
        
        nodes_in_vt.clear();
        int top_stk = 0;
        vt_stk[++top_stk] = S[0];
        nodes_in_vt.push_back(S[0]);
        
        for (int i = 1; i < C; i++) {
            int u = S[i];
            int lca = get_lca(u, vt_stk[top_stk]);
            if (lca != vt_stk[top_stk]) {
                while (top_stk > 1 && v_dfn[vt_stk[top_stk-1]] >= v_dfn[lca]) {
                    vt[vt_stk[top_stk-1]].push_back(vt_stk[top_stk]);
                    top_stk--;
                }
                if (vt_stk[top_stk] != lca) {
                    vt[lca].push_back(vt_stk[top_stk]);
                    vt_stk[top_stk] = lca;
                    nodes_in_vt.push_back(lca);
                }
            }
            vt_stk[++top_stk] = u;
            nodes_in_vt.push_back(u);
        }
        while (top_stk > 1) {
            vt[vt_stk[top_stk-1]].push_back(vt_stk[top_stk]);
            top_stk--;
        }
        
        int root = vt_stk[1];
        
        total_ans = 0;
        count_processed = 0;
        
        // 启动虚树清算
        dfs_dp(root, n);
        
        // 清算虚树外部的背景圆点
        total_ans += (n - count_processed) * C;
        
        cout << total_ans << "\n";
        
        // 扫尾工作：精准清空，绝不造成全局 memset 的算力污染
        for (int u : nodes_in_vt) {
            vt[u].clear();
            in_S[u] = false;
        }
    }
    
    return 0;
}