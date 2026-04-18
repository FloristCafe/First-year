#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

const int MAXN = 100005;

// 物理探针：事件队列
struct Event {
    int u, v;
    long long delta;
};

// 局部独立宇宙：每个节点的存活邻居红黑树
set<pair<long long, int>> nodes[MAXN];
unordered_map<int, long long> edge_weight[MAXN];

// 全局状态监控板
int main_obj[MAXN];
int island_count;
int pair_count = 0;

// O(1) 极速索敌引擎
// 权重最大优先，权重相同则负数 ID 最大（即正数 ID 最小）优先
int get_max(int u) {
    if (nodes[u].empty()) return 0;
    return -(nodes[u].rbegin()->second);
}

// 核心状态机：绝对防爆的增量更新机制
void apply(int u, int v, long long delta) {
    if (u == v) return;
    
    // 1. 冻结历史状态
    int old_mu = main_obj[u];
    int old_mv = main_obj[v];
    
    bool was_uv = (old_mu == v && old_mv == u);
    bool was_u_other = (old_mu != 0 && old_mu != v && main_obj[old_mu] == u);
    bool was_v_other = (old_mv != 0 && old_mv != u && main_obj[old_mv] == v);
    
    // 2. 剥离历史纠缠 (势能对消)
    if (was_uv) pair_count--;
    if (was_u_other) pair_count--;
    if (was_v_other) pair_count--;
    
    // 3. 物理数据覆写
    long long old_w = edge_weight[u][v];
    long long new_w = old_w + delta;
    
    if (old_w > 0) {
        nodes[u].erase({old_w, -v});
        nodes[v].erase({old_w, -u});
    }
    if (new_w > 0) {
        nodes[u].insert({new_w, -v});
        nodes[v].insert({new_w, -u});
    }
    
    if (new_w == 0) {
        // 清理哈希碎片，防止内存爆破
        edge_weight[u].erase(v);
        edge_weight[v].erase(u);
    } else {
        edge_weight[u][v] = new_w;
        edge_weight[v][u] = new_w;
    }
    
    // 4. 重构当下状态
    main_obj[u] = get_max(u);
    main_obj[v] = get_max(v);
    
    int new_mu = main_obj[u];
    int new_mv = main_obj[v];
    
    bool is_uv = (new_mu == v && new_mv == u);
    bool is_u_other = (new_mu != 0 && new_mu != v && main_obj[new_mu] == u);
    bool is_v_other = (new_mv != 0 && new_mv != u && main_obj[new_mv] == v);
    
    // 5. 注入新势能
    if (is_uv) pair_count++;
    if (is_u_other) pair_count++;
    if (is_v_other) pair_count++;
    
    // 6. 孤岛状态判定
    if (old_mu != 0 && new_mu == 0) island_count++;
    if (old_mu == 0 && new_mu != 0) island_count--;
    if (old_mv != 0 && new_mv == 0) island_count++;
    if (old_mv == 0 && new_mv != 0) island_count--;
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 宇宙初始态：所有机器皆为绝对孤岛
    island_count = n;
    for (int i = 1; i <= n; ++i) {
        main_obj[i] = 0;
    }

    // 时间差分队列
    vector<vector<Event>> expirations(m + 2);

    // 时间轴推进
    for (int day = 1; day <= m; ++day) {
        
        // 1. 引爆时间轴上埋藏的过期炸弹
        for (const auto& ev : expirations[day]) {
            apply(ev.u, ev.v, ev.delta);
        }
        
        // 2. 接收今日指令并埋设未来炸弹
        int k;
        cin >> k;
        for (int i = 0; i < k; ++i) {
            int u, v;
            long long x;
            int y;
            cin >> u >> v >> x >> y;
            apply(u, v, x);
            
            // 只有当失效时间在观测范围内时，才进行物理记录
            if (day + y <= m + 1) {
                expirations[day + y].push_back({u, v, -x});
            }
        }
        
        // 3. 执行单点观测
        int l;
        cin >> l;
        for (int i = 0; i < l; ++i) {
            int u;
            cin >> u;
            cout << main_obj[u] << "\n";
        }
        
        // 4. 执行宏观状态统计
        int p, q;
        cin >> p >> q;
        if (p == 1) {
            cout << island_count << "\n";
        }
        if (q == 1) {
            cout << pair_count << "\n";
        }
    }

    return 0;
}