#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
const int MAX_INF = 2e9 + 7;

// ==========================================
// 物理实体定义
// ==========================================
struct NodeObj {
    int x, y, id;
} nodes_arr[200005];

struct StationObj {
    int x, y, r, t, id;
} stations_arr[200005];

int cmp_dim; // KD-Tree 切分维度指示器
bool cmp_node(const NodeObj& a, const NodeObj& b) {
    return cmp_dim == 0 ? a.x < b.x : a.y < b.y;
}
bool cmp_station(const StationObj& a, const StationObj& b) {
    return cmp_dim == 0 ? a.x < b.x : a.y < b.y;
}

// 优先队列状态：{距离, {类型(0=点, 1=基站), 物理ID}}
typedef pair<long long, pair<int, int>> State;
priority_queue<State, vector<State>, greater<State>> pq;

long long dist_node[200005];
long long dist_station[200005];

// ==========================================
// 引擎 1：节点 KD-Tree (存储所有节点)
// 使命：给定一个基站正方形，极速找出里面所有存活的节点
// ==========================================
struct KDT_Node {
    int ls, rs;
    int minx, maxx, miny, maxy;
    NodeObj dat;
    bool deleted; // 物理抹杀标记
} tr_node[200005];

void pushup_node(int u) {
    tr_node[u].minx = tr_node[u].miny = MAX_INF;
    tr_node[u].maxx = tr_node[u].maxy = -MAX_INF;
    
    // 如果自己没死，贡献物理包围盒
    if (!tr_node[u].deleted) {
        tr_node[u].minx = tr_node[u].maxx = tr_node[u].dat.x;
        tr_node[u].miny = tr_node[u].maxy = tr_node[u].dat.y;
    }
    // 吸收左儿子的存活空间
    if (tr_node[u].ls) {
        int v = tr_node[u].ls;
        tr_node[u].minx = min(tr_node[u].minx, tr_node[v].minx);
        tr_node[u].maxx = max(tr_node[u].maxx, tr_node[v].maxx);
        tr_node[u].miny = min(tr_node[u].miny, tr_node[v].miny);
        tr_node[u].maxy = max(tr_node[u].maxy, tr_node[v].maxy);
    }
    // 吸收右儿子的存活空间
    if (tr_node[u].rs) {
        int v = tr_node[u].rs;
        tr_node[u].minx = min(tr_node[u].minx, tr_node[v].minx);
        tr_node[u].maxx = max(tr_node[u].maxx, tr_node[v].maxx);
        tr_node[u].miny = min(tr_node[u].miny, tr_node[v].miny);
        tr_node[u].maxy = max(tr_node[u].maxy, tr_node[v].maxy);
    }
}

int build_node(int l, int r, int dim) {
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    cmp_dim = dim;
    nth_element(nodes_arr + l, nodes_arr + mid, nodes_arr + r + 1, cmp_node);
    
    int u = mid;
    tr_node[u].dat = nodes_arr[mid];
    tr_node[u].deleted = false;
    tr_node[u].ls = build_node(l, mid - 1, dim ^ 1);
    tr_node[u].rs = build_node(mid + 1, r, dim ^ 1);
    
    pushup_node(u);
    return u;
}

// 雷达扫描：寻找落在 [X1, X2] x [Y1, Y2] 范围内的存活节点
void query_node(int u, int x1, int x2, int y1, int y2, long long d) {
    if (!u || tr_node[u].minx > x2 || tr_node[u].maxx < x1 || 
        tr_node[u].miny > y2 || tr_node[u].maxy < y1) return; // 绝对相离或全灭，直接剪枝
    
    // 如果当前点存活，且在正方形内，直接捕获！
    if (!tr_node[u].deleted && 
        tr_node[u].dat.x >= x1 && tr_node[u].dat.x <= x2 && 
        tr_node[u].dat.y >= y1 && tr_node[u].dat.y <= y2) {
        
        tr_node[u].deleted = true; // 绝对物理抹杀
        dist_node[tr_node[u].dat.id] = d;
        pq.push({d, {0, tr_node[u].dat.id}});
    }
    
    // 递归搜索子宇宙
    query_node(tr_node[u].ls, x1, x2, y1, y2, d);
    query_node(tr_node[u].rs, x1, x2, y1, y2, d);
    
    pushup_node(u); // 物理坍缩：更新当前子树的存活边界
}

// ==========================================
// 引擎 2：基站 KD-Tree (存储所有基站)
// 使命：给定一个点，极速找出所有能覆盖到该点的存活基站
// ==========================================
struct KDT_Station {
    int ls, rs;
    int minx, maxx, miny, maxy; // 注意：这里维护的是基站【覆盖范围】的包围盒！
    StationObj dat;
    bool deleted;
} tr_station[200005];

void pushup_station(int u) {
    tr_station[u].minx = tr_station[u].miny = MAX_INF;
    tr_station[u].maxx = tr_station[u].maxy = -MAX_INF;
    
    if (!tr_station[u].deleted) {
        // 基站的引力场范围
        tr_station[u].minx = tr_station[u].dat.x - tr_station[u].dat.r;
        tr_station[u].maxx = tr_station[u].dat.x + tr_station[u].dat.r;
        tr_station[u].miny = tr_station[u].dat.y - tr_station[u].dat.r;
        tr_station[u].maxy = tr_station[u].dat.y + tr_station[u].dat.r;
    }
    if (tr_station[u].ls) {
        int v = tr_station[u].ls;
        tr_station[u].minx = min(tr_station[u].minx, tr_station[v].minx);
        tr_station[u].maxx = max(tr_station[u].maxx, tr_station[v].maxx);
        tr_station[u].miny = min(tr_station[u].miny, tr_station[v].miny);
        tr_station[u].maxy = max(tr_station[u].maxy, tr_station[v].maxy);
    }
    if (tr_station[u].rs) {
        int v = tr_station[u].rs;
        tr_station[u].minx = min(tr_station[u].minx, tr_station[v].minx);
        tr_station[u].maxx = max(tr_station[u].maxx, tr_station[v].maxx);
        tr_station[u].miny = min(tr_station[u].miny, tr_station[v].miny);
        tr_station[u].maxy = max(tr_station[u].maxy, tr_station[v].maxy);
    }
}

int build_station(int l, int r, int dim) {
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    cmp_dim = dim;
    nth_element(stations_arr + l, stations_arr + mid, stations_arr + r + 1, cmp_station);
    
    int u = mid;
    tr_station[u].dat = stations_arr[mid];
    tr_station[u].deleted = false;
    tr_station[u].ls = build_station(l, mid - 1, dim ^ 1);
    tr_station[u].rs = build_station(mid + 1, r, dim ^ 1);
    
    pushup_station(u);
    return u;
}

// 雷达扫描：寻找所有引力场覆盖了点 (px, py) 的存活基站
void query_station(int u, int px, int py, long long d) {
    // 如果目标点不在当前子树所有基站的引力场并集之内，直接剪枝
    if (!u || px < tr_station[u].minx || px > tr_station[u].maxx || 
        py < tr_station[u].miny || py > tr_station[u].maxy) return;
        
    if (!tr_station[u].deleted) {
        long long dx = abs(px - tr_station[u].dat.x);
        long long dy = abs(py - tr_station[u].dat.y);
        if (dx <= tr_station[u].dat.r && dy <= tr_station[u].dat.r) {
            tr_station[u].deleted = true; // 绝对物理抹杀
            int sid = tr_station[u].dat.id;
            dist_station[sid] = d + tr_station[u].dat.t; // 加上进入基站的代价
            pq.push({dist_station[sid], {1, sid}});
        }
    }
    
    query_station(tr_station[u].ls, px, py, d);
    query_station(tr_station[u].rs, px, py, d);
    
    pushup_station(u); // 物理坍缩
}

// ==========================================
// 主控中心
// ==========================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    // 初始化物理距离为深渊
    for (int i = 1; i <= n; i++) dist_node[i] = INF;
    for (int i = 1; i <= m; i++) dist_station[i] = INF;
    
    // 快速坐标索引用
    vector<pair<int, int>> orig_nodes(n + 1);
    vector<StationObj> orig_stations(m + 1);
    
    for (int i = 1; i <= n; i++) {
        cin >> nodes_arr[i].x >> nodes_arr[i].y;
        nodes_arr[i].id = i;
        orig_nodes[i] = {nodes_arr[i].x, nodes_arr[i].y};
    }
    
    for (int i = 1; i <= m; i++) {
        cin >> stations_arr[i].x >> stations_arr[i].y >> stations_arr[i].r >> stations_arr[i].t;
        stations_arr[i].id = i;
        orig_stations[i] = stations_arr[i];
    }
    
    // 构建双子宇宙
    int root_node = build_node(1, n, 0);
    int root_station = build_station(1, m, 0);
    
    // 启动源点：节点 1
    // 需要手动在 KD-Tree 中将节点 1 抹杀，防止自循环
    auto init_start_node = [&](auto& self, int u, int target_id) -> void {
        if (!u) return;
        if (tr_node[u].dat.id == target_id) tr_node[u].deleted = true;
        self(self, tr_node[u].ls, target_id);
        self(self, tr_node[u].rs, target_id);
        pushup_node(u);
    };
    init_start_node(init_start_node, root_node, 1);
    
    dist_node[1] = 0;
    pq.push({0, {0, 1}});
    
    // 核心寻路引擎
    while (!pq.empty()) {
        auto [d, info] = pq.top();
        pq.pop();
        
        int type = info.first;
        int id = info.second;
        
        // 剪枝：处理过期的队列元素
        if (type == 0 && d > dist_node[id]) continue;
        if (type == 1 && d > dist_station[id]) continue;
        
        // 抵达终点，绝对最优解立刻终止！
        if (type == 0 && id == n) {
            cout << d << "\n";
            return 0;
        }
        
        if (type == 0) {
            // 当前处于一个点：去基站树里找能覆盖它的基站
            int px = orig_nodes[id].first;
            int py = orig_nodes[id].second;
            query_station(root_station, px, py, d);
        } else {
            // 当前处于一个基站：去节点树里找被它覆盖的点
            int sx = orig_stations[id].x;
            int sy = orig_stations[id].y;
            int sr = orig_stations[id].r;
            query_node(root_node, sx - sr, sx + sr, sy - sr, sy + sr, d);
        }
    }
    
    cout << "Nan\n";
    return 0;
}