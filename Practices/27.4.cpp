#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// === ODT (老司机树) 物理底座 ===
struct Node {
    long long l, r;
    mutable int p; // 物理 ID
    Node(long long _l, long long _r = -1, int _p = 0) : l(_l), r(_r), p(_p) {}
    bool operator<(const Node& o) const {
        return l < o.l;
    }
};

set<Node> odt;

auto split(long long pos) {
    auto it = odt.lower_bound(Node(pos));
    if (it != odt.end() && it->l == pos) return it;
    --it;
    long long l = it->l, r = it->r;
    int p = it->p;
    odt.erase(it);
    odt.insert(Node(l, pos - 1, p));
    return odt.insert(Node(pos, r, p)).first;
}

// === 全局状态与映射引擎 ===
int n, m, q;
vector<long long> ans_count;      // 记录每个逻辑吉祥物的总票数
vector<int> L2P, P2L, dsu_parent; // 逻辑-物理双向映射与并查集
int pid_counter;                  // 物理 ID 发生器

// 利用红黑树自动维护最大值，寻找获胜者。存入 pair(票数, -逻辑ID)
set<pair<long long, int>> active_votes; 

// 并查集寻根探针：定位该物理块最终属于哪个根物理块
int dsu_find(int p) {
    return dsu_parent[p] == p ? p : dsu_parent[p] = dsu_find(dsu_parent[p]);
}

// 票数变更中枢：绝对防爆
void update_count(int logic_id, long long delta) {
    if (logic_id == 0) {
        ans_count[0] += delta;
        return;
    }
    // 先从雷达中剥离，修改后再重新接入
    active_votes.erase({ans_count[logic_id], -logic_id});
    ans_count[logic_id] += delta;
    active_votes.insert({ans_count[logic_id], -logic_id});
}

// === 核心事件处理器 ===

// 事件 1：区间物理覆盖
void assign_range(long long l, long long r, int new_logic_x) {
    auto itr = split(r + 1);
    auto itl = split(l);
    
    // 清算被覆盖区域的旧势能
    for (auto it = itl; it != itr; ++it) {
        int root_p = dsu_find(it->p);
        int old_logic = P2L[root_p];
        long long len = it->r - it->l + 1;
        update_count(old_logic, -len);
    }
    
    // 抹除旧空间，注入新物理块
    odt.erase(itl, itr);
    odt.insert(Node(l, r, L2P[new_logic_x]));
    update_count(new_logic_x, r - l + 1);
}

// 事件 2：大规模合并降维
void merge_works(int x, int w) {
    if (x == w) return;
    
    int px = L2P[x];
    int pw = L2P[w];
    int root_px = dsu_find(px);
    int root_pw = dsu_find(pw);
    
    // 并查集物理坍缩
    if (root_px != root_pw) {
        dsu_parent[root_px] = root_pw;
    }
    
    // 票数转移
    long long val = ans_count[x];
    if (val > 0) {
        update_count(x, -val);
        update_count(w, val);
    }
    
    // 为 x 重新分配全新的物理隔离舱
    ++pid_counter;
    L2P[x] = pid_counter;
    P2L[pid_counter] = x;
    dsu_parent[pid_counter] = pid_counter;
}

// 事件 3：逻辑镜像互换
void swap_works(int x, int y) {
    if (x == y) return;
    
    int px = L2P[x];
    int py = L2P[y];
    
    // 物理指针交叉对调 (O(1) 绝对替换，不需要碰任何区间)
    L2P[x] = py;
    L2P[y] = px;
    P2L[px] = y;
    P2L[py] = x;
    
    long long cx = ans_count[x];
    long long cy = ans_count[y];
    
    update_count(x, -cx);
    update_count(y, -cy);
    update_count(x, cy);
    update_count(y, cx);
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> q)) return 0;

    // 分配物理内存池 (考虑到每次 Event2 消耗 1 个，总量 m + q 足够)
    int MAX_P = m + q + 5;
    ans_count.assign(m + 1, 0);
    L2P.assign(m + 1, 0);
    P2L.assign(MAX_P, 0);
    dsu_parent.assign(MAX_P, 0);

    // 初始宇宙：所有票都属于弃权(0)
    ans_count[0] = n;
    pid_counter = m;
    
    for (int i = 0; i <= m; ++i) {
        L2P[i] = i;
        P2L[i] = i;
        dsu_parent[i] = i;
        if (i != 0) {
            active_votes.insert({0, -i});
        }
    }

    // 建立空间边界
    odt.insert(Node(1, n, L2P[0]));
    odt.insert(Node(n + 1, n + 1, L2P[0])); // 绝对防爆哨兵

    // 接收指令
    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            long long l, r;
            int x;
            cin >> l >> r >> x;
            assign_range(l, r, x);
        } else if (type == 2) {
            int x, w;
            cin >> x >> w;
            merge_works(x, w);
        } else if (type == 3) {
            int x, y;
            cin >> x >> y;
            swap_works(x, y);
        } else if (type == 4) {
            int w;
            cin >> w;
            cout << ans_count[w] << "\n";
        } else if (type == 5) {
            if (active_votes.empty()) {
                cout << 0 << "\n";
            } else {
                auto it = active_votes.rbegin();
                if (it->first == 0) cout << 0 << "\n";
                else cout << -(it->second) << "\n";
            }
        }
    }

    return 0;
}
