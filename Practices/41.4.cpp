#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 500005;
const int D = 30; // 足够覆盖绝大多数题目数据，可以根据实际情况调整

ll n, m, k;
ll inv2; // 2 的逆元

// 预处理 2 在模 k 下的逆元 (前提是 k 为奇数)
ll get_inv2(ll mod) {
    return (mod + 1) / 2;
}

// 提取一个数在 k 进制下的各数位
vector<ll> extract(ll val) {
    vector<ll> bits(D, 0);
    int idx = 0;
    while (val > 0 && idx < D) {
        bits[idx++] = val % k;
        val /= k;
    }
    return bits;
}

struct Node {
    ll len;
    ll S[D];
    ll S00;
    ll C[D];
    ll tag[D];
    bool has_tag;

    // 清空节点状态
    void clear() {
        len = 0;
        S00 = 0;
        has_tag = false;
        for (int i = 0; i < D; ++i) {
            S[i] = C[i] = tag[i] = 0;
        }
    }
} tree[MAXN << 2];

ll a[MAXN];

// 向上合并物理状态
void push_up(int p) {
    tree[p].S00 = (tree[p << 1].S00 + tree[p << 1 | 1].S00) % k;
    for (int j = 0; j < D; ++j) {
        tree[p].S[j] = (tree[p << 1].S[j] + tree[p << 1 | 1].S[j]) % k;
        tree[p].C[j] = (tree[p << 1].C[j] + tree[p << 1 | 1].C[j]) % k;
    }
}

// 将懒标记推演入节点的代数公式中
void apply_tag(int p, const vector<ll>& v) {
    ll v0 = v[0];
    
    // 必须用老的状态去更新新的状态，防止自相覆盖
    ll old_S[D];
    ll old_S00 = tree[p].S00;
    for (int j = 0; j < D; ++j) {
        old_S[j] = tree[p].S[j];
    }

    // 1. 更新 S00' = S00 + 2*v0*S0 + v0^2 * len
    tree[p].S00 = (old_S00 + 2 * v0 * old_S[0] % k + v0 * v0 % k * tree[p].len % k) % k;

    for (int j = 0; j < D; ++j) {
        // 2. 更新 C[j]' = C[j] + v0*S[j] + vj*S[0] + vj*v0 * len
        tree[p].C[j] = (tree[p].C[j] + v0 * old_S[j] % k + v[j] * old_S[0] % k + v[j] * v0 % k * tree[p].len % k) % k;
        
        // 3. 更新 S[j]' = S[j] + vj * len
        tree[p].S[j] = (old_S[j] + v[j] * tree[p].len % k) % k;

        // 累积懒标记
        tree[p].tag[j] = (tree[p].tag[j] + v[j]) % k;
    }
    tree[p].has_tag = true;
}

// 释放积累的物理势能
void push_down(int p) {
    if (tree[p].has_tag) {
        vector<ll> v(D);
        for (int i = 0; i < D; ++i) v[i] = tree[p].tag[i];
        
        apply_tag(p << 1, v);
        apply_tag(p << 1 | 1, v);
        
        for (int i = 0; i < D; ++i) tree[p].tag[i] = 0;
        tree[p].has_tag = false;
    }
}

// 建树
void build(int p, int l, int r) {
    tree[p].clear();
    tree[p].len = r - l + 1;
    if (l == r) {
        vector<ll> bits = extract(a[l]);
        for (int j = 0; j < D; ++j) {
            tree[p].S[j] = bits[j];
            tree[p].C[j] = (bits[j] * bits[0]) % k;
        }
        tree[p].S00 = (bits[0] * bits[0]) % k;
        return;
    }
    int mid = (l + r) / 2;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

// 区间异或累加操作
void update(int p, int l, int r, int L, int R, const vector<ll>& v) {
    if (L <= l && r <= R) {
        apply_tag(p, v);
        return;
    }
    push_down(p);
    int mid = (l + r) / 2;
    if (L <= mid) update(p << 1, l, mid, L, R, v);
    if (R > mid) update(p << 1 | 1, mid + 1, r, L, R, v);
    push_up(p);
}

// 查询区间 f(x) 的异或和：只需返回各数位上的代数和
vector<ll> query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        vector<ll> res(D, 0);
        // f(x)_0 = (n0^2 + n0) / 2
        res[0] = ((tree[p].S00 + tree[p].S[0]) % k * inv2) % k;
        
        // f(x)_j = nj * n0 + nj (即 C[j] + S[j])
        for (int j = 1; j < D; ++j) {
            res[j] = (tree[p].C[j] + tree[p].S[j]) % k;
        }
        return res;
    }
    push_down(p);
    int mid = (l + r) / 2;
    vector<ll> res(D, 0);
    if (L <= mid) {
        vector<ll> left_res = query(p << 1, l, mid, L, R);
        for (int i = 0; i < D; ++i) res[i] = (res[i] + left_res[i]) % k;
    }
    if (R > mid) {
        vector<ll> right_res = query(p << 1 | 1, mid + 1, r, L, R);
        for (int i = 0; i < D; ++i) res[i] = (res[i] + right_res[i]) % k;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> k)) return 0;
    
    inv2 = get_inv2(k);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    build(1, 1, n);

    for (int i = 0; i < m; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            ll v_val;
            cin >> l >> r >> v_val;
            vector<ll> v_bits = extract(v_val);
            update(1, 1, n, l, r, v_bits);
        } else {
            int l, r;
            cin >> l >> r;
            vector<ll> ans_bits = query(1, 1, n, l, r);
            
            // 将各位的值还原为真实数字
            ll final_ans = 0;
            ll base = 1;
            for (int j = 0; j < D; ++j) {
                final_ans += ans_bits[j] * base;
                base *= k;
            }
            cout << final_ans << "\n";
        }
    }

    return 0;
}