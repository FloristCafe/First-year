#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long MOD = 998244353;

// 绝对防爆：2x2 矩阵物理结构
struct Matrix {
    long long a, b, c, d;
};

Matrix mul(const Matrix& m1, const Matrix& m2) {
    Matrix res;
    res.a = (m1.a * m2.a + m1.b * m2.c) % MOD;
    res.b = (m1.a * m2.b + m1.b * m2.d) % MOD;
    res.c = (m1.c * m2.a + m1.d * m2.c) % MOD;
    res.d = (m1.c * m2.b + m1.d * m2.d) % MOD;
    return res;
}

const Matrix Identity = {1, 0, 0, 1};

// 状态压缩：将左乘与右乘剥离
struct MatrixPair {
    Matrix L, R;
};

const MatrixPair IdentityPair = {Identity, Identity};

// 绝对结合律：合并两段操作序列 S1 (时间在前) 和 S2 (时间在后)
MatrixPair merge_pair(const MatrixPair& S1, const MatrixPair& S2) {
    MatrixPair res;
    // S2 的左插发生在 S1 的左插之后，所以 S2 在更外层（左边）
    res.L = mul(S2.L, S1.L);
    // S2 的右插发生在 S1 的右插之后，所以 S2 在更外层（右边）
    res.R = mul(S1.R, S2.R);
    return res;
}

// 核心雷达：动态回退线段树节点
struct Node {
    int del;           // 向左发送的撤销指令数量
    int cnt;           // 该区间独立存活的指令数量
    MatrixPair prod;   // 这 cnt 个存活指令的累积状态
    MatrixPair val_left; // 缓存：用于 O(log N) 快速合并的左侧存活前缀
} tree[100005 << 2];

// 引擎核心：提取节点 p 中，前 len 个存活指令的乘积
MatrixPair get_prefix(int p, int len) {
    if (len == 0) return IdentityPair;
    if (len == tree[p].cnt) return tree[p].prod;
    
    int lc = p << 1;
    int rc = p << 1 | 1;
    int left_survive = max(0, tree[lc].cnt - tree[rc].del);
    
    if (len <= left_survive) {
        // 所求前缀完全落在左儿子的幸存区
        return get_prefix(lc, len);
    } else {
        // 所求前缀跨越了左右儿子
        return merge_pair(tree[p].val_left, get_prefix(rc, len - left_survive));
    }
}

// 物理状态向上坍缩
void push_up(int p) {
    int lc = p << 1;
    int rc = p << 1 | 1;
    
    // 撤销指令的向左穿透
    tree[p].del = tree[lc].del + max(0, tree[rc].del - tree[lc].cnt);
    // 幸存指令的向上累加
    tree[p].cnt = tree[rc].cnt + max(0, tree[lc].cnt - tree[rc].del);
    
    int left_survive = max(0, tree[lc].cnt - tree[rc].del);
    tree[p].val_left = get_prefix(lc, left_survive);
    tree[p].prod = merge_pair(tree[p].val_left, tree[rc].prod);
}

// 叶子节点装配
void set_leaf(int p, int type, Matrix m) {
    if (type == 1) {
        tree[p] = {0, 1, {m, Identity}, {Identity, Identity}};
    } else if (type == 2) {
        tree[p] = {0, 1, {Identity, m}, {Identity, Identity}};
    } else if (type == 3) {
        tree[p] = {1, 0, IdentityPair, IdentityPair};
    }
}

// 单点修改引擎
void update(int p, int l, int r, int idx, int type, Matrix m) {
    if (l == r) {
        set_leaf(p, type, m);
        return;
    }
    int mid = (l + r) >> 1;
    if (idx <= mid) update(p << 1, l, mid, idx, type, m);
    else update(p << 1 | 1, mid + 1, r, idx, type, m);
    push_up(p);
}

// 全局查询探针
int current_del = 0;
MatrixPair current_res = IdentityPair;

// 极其优雅的从右向左查询机制，完美避免了动态节点的构建
void query_process(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        int survive = max(0, tree[p].cnt - current_del);
        if (survive > 0) {
            current_res = merge_pair(get_prefix(p, survive), current_res);
        }
        current_del = tree[p].del + max(0, current_del - tree[p].cnt);
        return;
    }
    int mid = (l + r) >> 1;
    // 💥 绝对纪律：必须先访问右子树，这样撤销指令才能正确向左传导
    if (qr > mid) query_process(p << 1 | 1, mid + 1, r, ql, qr);
    if (ql <= mid) query_process(p << 1, l, mid, ql, qr);
}

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; i++) {
        int type;
        cin >> type;
        Matrix mat = Identity;
        if (type == 1 || type == 2) {
            cin >> mat.a >> mat.b >> mat.c >> mat.d;
        }
        update(1, 1, n, i, type, mat);
    }

    for (int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int idx, type;
            cin >> idx >> type;
            Matrix mat = Identity;
            if (type == 1 || type == 2) {
                cin >> mat.a >> mat.b >> mat.c >> mat.d;
            }
            update(1, 1, n, idx, type, mat);
        } else if (op == 2) {
            int l, r;
            cin >> l >> r;
            
            // 每次查询前重置时空探针
            current_del = 0;
            current_res = IdentityPair;
            
            query_process(1, 1, n, l, r);
            
            // 最终物理状态坍缩：P_L * I * P_R
            Matrix final_mat = mul(current_res.L, current_res.R);
            cout << final_mat.a << " " << final_mat.b << "\n"
                 << final_mat.c << " " << final_mat.d << "\n";
        }
    }

    return 0;
}