#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const long long INF = 1e15; // 绝对防爆：不可穿越的物理下界

// 极其安全的加法引擎，防止 -INF 运算时发生下溢
long long safe_add(long long x, long long y) {
    if (x <= -INF / 2 || y <= -INF / 2) return -INF;
    return x + y;
}

// 💥 广义矩阵 (max, +) 引擎
// 原本的 3x3 矩阵存在大量无用的 -INF 和 0。
// 架构师的降维打击：直接抽离出最核心的 4 个参数 a, c, d, f！
struct Matrix {
    long long a, c, d, f;
    Matrix() { a = -INF; c = 0; d = -INF; f = 0; }
    
    // 绝对结合律的物理具象化
    Matrix operator*(const Matrix& B) const {
        Matrix R;
        R.a = safe_add(a, B.a);
        R.c = max(safe_add(a, B.c), c);
        R.d = max(safe_add(d, B.a), B.d);
        R.f = max({safe_add(d, B.c), B.f, f});
        return R;
    }
};

// 绝对安全的动态集合 (维护轻儿子的能量)
struct MultiSet {
    multiset<long long, greater<long long>> s;
    void insert(long long x) { s.insert(x); }
    void erase(long long x) { s.erase(s.find(x)); }
    long long max1() { return *s.begin(); }
    long long max2() {
        auto it = s.begin();
        long long a = *it; ++it;
        long long b = *it;
        return a + b;
    }
};

const int MAXN = 100005;
int n, m;

struct Edge {
    int u, v;
    long long w, b;
} edges[MAXN];

vector<int> adj[MAXN];
int edge_node[MAXN]; 

// HLD 骨架
int fa[MAXN], sz[MAXN], dep[MAXN], son[MAXN];
int top_node[MAXN], dfn[MAXN], rnk[MAXN], bot[MAXN], dfn_cnt = 0;

// DP 雷达与动态集合
long long weight[MAXN]; 
long long dp[MAXN][2], g[MAXN][2];
MultiSet set0[MAXN], set1[MAXN];

// 线段树装甲
Matrix tree[MAXN << 2];

// ---------------------------------------------------------
// 阶段一：重轻链物理切割
// ---------------------------------------------------------
void dfs1(int u, int p) {
    fa[u] = p; dep[u] = dep[p] + 1; sz[u] = 1;
    for (int id : adj[u]) {
        int v = (edges[id].u == u) ? edges[id].v : edges[id].u;
        if (v == p) continue;
        weight[v] = edges[id].b - edges[id].w; // 物理收益：b - w
        edge_node[id] = v; // 锁定边与子节点的绝对映射
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top_node[u] = t;
    dfn[u] = ++dfn_cnt;
    rnk[dfn_cnt] = u;
    bot[t] = u; // 链底指针不断向下坍缩
    if (son[u]) dfs2(son[u], t);
    for (int id : adj[u]) {
        int v = (edges[id].u == u) ? edges[id].v : edges[id].u;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

// ---------------------------------------------------------
// 阶段二：初始能量池聚合
// ---------------------------------------------------------
void dfs3(int u) {
    if (son[u]) dfs3(son[u]);
    for (int id : adj[u]) {
        int v = (edges[id].u == u) ? edges[id].v : edges[id].u;
        if (v == fa[u] || v == son[u]) continue;
        dfs3(v);
        set0[u].insert(dp[v][0] + weight[v]);
        set1[u].insert(dp[v][1]);
    }
    g[u][0] = set0[u].max1();
    g[u][1] = max(set1[u].max1(), set0[u].max2());

    if (son[u]) {
        dp[u][0] = max(g[u][0], dp[son[u]][0] + weight[son[u]]);
        dp[u][1] = max({g[u][1], dp[son[u]][1], dp[son[u]][0] + weight[son[u]] + g[u][0]});
    } else {
        dp[u][0] = g[u][0];
        dp[u][1] = g[u][1];
    }
}

// ---------------------------------------------------------
// 阶段三：线段树矩阵点火
// ---------------------------------------------------------
Matrix get_mat(int u) {
    Matrix M;
    long long g0 = set0[u].max1();
    long long g1 = max(set1[u].max1(), set0[u].max2());
    long long wh = (son[u] ? weight[son[u]] : -INF);

    M.a = wh;
    M.c = g0;
    M.d = safe_add(wh, g0);
    M.f = g1;
    return M;
}

void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = get_mat(rnk[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    tree[p] = tree[p << 1] * tree[p << 1 | 1];
}

void modify(int p, int l, int r, int idx) {
    if (l == r) {
        tree[p] = get_mat(rnk[l]);
        return;
    }
    int mid = (l + r) >> 1;
    if (idx <= mid) modify(p << 1, l, mid, idx);
    else modify(p << 1 | 1, mid + 1, r, idx);
    tree[p] = tree[p << 1] * tree[p << 1 | 1];
}

Matrix query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p];
    int mid = (l + r) >> 1;
    if (qr <= mid) return query(p << 1, l, mid, ql, qr);
    if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
    return query(p << 1, l, mid, ql, qr) * query(p << 1 | 1, mid + 1, r, ql, qr);
}

// ---------------------------------------------------------
// 阶段四：动态 DP 极限跃迁
// ---------------------------------------------------------
void update_path(int x) {
    while (x) {
        int head = top_node[x];
        int p = fa[head];
        if (p) {
            // 剥离旧状态
            Matrix old_M = query(1, 1, n, dfn[head], dfn[bot[head]]);
            set0[p].erase(old_M.c + weight[head]);
            set1[p].erase(old_M.f);

            // 物理刷新核心
            modify(1, 1, n, dfn[x]);

            // 注入新状态
            Matrix new_M = query(1, 1, n, dfn[head], dfn[bot[head]]);
            set0[p].insert(new_M.c + weight[head]);
            set1[p].insert(new_M.f);

            x = p; // 向上坍缩
        } else {
            modify(1, 1, n, dfn[x]);
            x = 0;
        }
    }
}

void update_edge(int id, long long new_w) {
    int u = edge_node[id];
    long long val = edges[id].b - new_w;

    int p = fa[u];
    if (u == son[p]) {
        weight[u] = val;
        update_path(p); // 重儿子直接引发父亲矩阵剧变
    } else {
        Matrix M_u = query(1, 1, n, dfn[u], dfn[bot[top_node[u]]]);
        set0[p].erase(M_u.c + weight[u]);
        set1[p].erase(M_u.f);

        weight[u] = val; // 轻儿子引发父亲集合剧变

        set0[p].insert(M_u.c + weight[u]);
        set1[p].insert(M_u.f);
        update_path(p);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n - 1; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w >> edges[i].b;
        adj[edges[i].u].push_back(i);
        adj[edges[i].v].push_back(i);
    }

    // 初始化动态集合：放入足够多的 0，作为空路径和断链的物理保障
    for (int i = 1; i <= n; i++) {
        set0[i].insert(0); set0[i].insert(0);
        set1[i].insert(0);
    }

    dfs1(1, 0);
    dfs2(1, 1);
    dfs3(1);
    build(1, 1, n);

    // 起始状态输出：根节点所在重链的矩阵提取
    Matrix root_M = query(1, 1, n, 1, dfn[bot[1]]);
    cout << root_M.f << "\n";

    // 接受指挥部动态指令
    for (int i = 0; i < m; i++) {
        int x; long long y;
        cin >> x >> y;
        update_edge(x, y);
        
        root_M = query(1, 1, n, 1, dfn[bot[1]]);
        cout << root_M.f << "\n";
    }

    return 0;
}