#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cctype>

using namespace std;

const long long MOD = 998244353;
int n, m;

// 极其严谨的结构体，必须使用 long long 防爆
struct node {
    long long a, b;
    long long c, d;
};

// 绝对的单位矩阵常量
const node Identity = {1, 0, 0, 1};

// 矩阵乘法引擎：满足结合律，但不满足交换律！
node mul(const node& A, const node& B) {
    node res;
    res.a = (A.a * B.a + A.b * B.c) % MOD;
    res.b = (A.a * B.b + A.b * B.d) % MOD;
    res.c = (A.c * B.a + A.d * B.c) % MOD;
    res.d = (A.c * B.b + A.d * B.d) % MOD;
    return res;
}

// 状态压缩：将左乘与右乘物理剥离
struct nodePair {
    node L;
    node R;
};

// ---------------------------------------------------------
// 物理底层：线段树引擎 (无懒标记，纯单点修改)
// ---------------------------------------------------------
nodePair tree[200005 << 2];

// 向上坍缩：左边的矩阵，左乘时在外面，右乘时在里面
void pushup(int p) {
    int lc = p << 1;
    int rc = p << 1 | 1;
    // S_rc(左插) * S_lc(左插)
    tree[p].L = mul(tree[rc].L, tree[lc].L); 
    // S_lc(右插) * S_rc(右插)
    tree[p].R = mul(tree[lc].R, tree[rc].R); 
}

// 单点修改探针：将第 idx 个插槽的矩阵强行覆盖为 nd
// type = 'L' 左插, 'R' 右插, 其他代表无效 (单位阵)
void update(int p, int l, int r, int idx, node nd, char type) {
    if (l == r) {
        if (type == 'L') {
            tree[p].L = nd;
            tree[p].R = Identity;
        } else if (type == 'R') {
            tree[p].L = Identity;
            tree[p].R = nd;
        } else {
            tree[p].L = Identity;
            tree[p].R = Identity;
        }
        return;
    }
    int mid = (l + r) >> 1;
    if (idx <= mid) update(p << 1, l, mid, idx, nd, type);
    else update(p << 1 | 1, mid + 1, r, idx, nd, type);
    pushup(p);
}

// 区间查询雷达
nodePair query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p];
    int mid = (l + r) >> 1;
    if (qr <= mid) return query(p << 1, l, mid, ql, qr);
    if (ql > mid) return query(p << 1 | 1, mid + 1, r, ql, qr);
    
    nodePair left_res = query(p << 1, l, mid, ql, qr);
    nodePair right_res = query(p << 1 | 1, mid + 1, r, ql, qr);
    
    nodePair res;
    res.L = mul(right_res.L, left_res.L);
    res.R = mul(left_res.R, right_res.R);
    return res;
}

// ---------------------------------------------------------
// 指挥部与状态机装配
// ---------------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    if (!(cin >> n >> m)) return 0;
    
    // 初始化全树为单位矩阵
    for (int i = 0; i < (200005 << 2); i++) {
        tree[i].L = Identity;
        tree[i].R = Identity;
    }
    
    int a, b;
    // 你的静态时间线模拟
    stack<pair<char, node>> st;
    vector<pair<char, node>> v(n + 1, {'X', Identity}); // 1-based indexing
    
    for (int i = 1; i <= n; i++) {
        cin >> a;
        if (a == 1) {
            node nd;
            cin >> nd.a >> nd.b >> nd.c >> nd.d;
            st.push({'L', nd});
            v[i] = {'L', nd};
            update(1, 1, n, i, nd, 'L');
        } else if (a == 2) {
            node nd;
            cin >> nd.a >> nd.b >> nd.c >> nd.d;
            st.push({'R', nd});
            v[i] = {'R', nd};
            update(1, 1, n, i, nd, 'R');
        } else if (a == 3) {
            if (!st.empty()) {
                // 模拟撤销，但不修改线段树，只标记 v[i] 的类型
                st.pop(); 
            }
            // 撤销指令本身在线段树中贡献单位阵 (type='X')
            v[i] = {'X', Identity};
            update(1, 1, n, i, Identity, 'X');
        }
    }
    
    // 接受指挥部的动态修改
    for (int i = 0; i < m; i++) {
        cin >> a;
        if (a == 1) {
            int idx;
            cin >> idx >> b;
            // 致命妥协点：如果这里把插入改成了撤销，你的栈逻辑已经失效！
            // 这里仅仅是单点覆盖矩阵
            if (b == 1) {
                node nd;
                cin >> nd.a >> nd.b >> nd.c >> nd.d;
                v[idx] = {'L', nd};
                update(1, 1, n, idx, nd, 'L');
            } else if (b == 2) {
                node nd;
                cin >> nd.a >> nd.b >> nd.c >> nd.d;
                v[idx] = {'R', nd};
                update(1, 1, n, idx, nd, 'R');
            } else if (b == 3) {
                v[idx] = {'X', Identity};
                update(1, 1, n, idx, Identity, 'X');
            }
        } else if (a == 2) {
            int l, r;
            cin >> l >> r;
            nodePair res = query(1, 1, n, l, r);
            // 最终坍缩：P_L * I * P_R
            node ans = mul(res.L, res.R);
            cout << ans.a << ' ' << ans.b << "\n" << ans.c << " " << ans.d << "\n";
        }
    }
    
    return 0;
}