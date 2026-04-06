#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

// 绝对防爆：8个方向的向量定义 (0:右, 1:右上, 2:上, ... 7:右下)
int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

struct Employee {
    ll x, y;
} emp[100005];

// 核心雷达：只存员工编号 id，按照具体的 x 或 y 排序
map<ll, set<pair<ll, int>>> idx_x;    // x -> {y, id}
map<ll, set<pair<ll, int>>> idx_y;    // y -> {x, id}
map<ll, set<pair<ll, int>>> idx_add;  // x+y -> {x, id}
map<ll, set<pair<ll, int>>> idx_sub;  // y-x -> {x, id}

ll n, m, p, q;

// 💥 物理迁跃函数：绝对安全地更新 4 个雷达
void move_emp(int id, ll nx, ll ny) {
    ll cx = emp[id].x, cy = emp[id].y;
    // 拔除旧坐标
    idx_x[cx].erase({cy, id});
    idx_y[cy].erase({cx, id});
    idx_add[cx + cy].erase({cx, id});
    idx_sub[cy - cx].erase({cx, id});
    
    // 更新物理实体
    emp[id].x = nx;
    emp[id].y = ny;
    
    // 植入新坐标
    idx_x[nx].insert({ny, id});
    idx_y[ny].insert({nx, id});
    idx_add[nx + ny].insert({nx, id});
    idx_sub[ny - nx].insert({nx, id});
}

// 💥 雷达探测函数：寻找在直线 set 里，当前坐标 val_axis 沿着方向 sign (1 或 -1) 的最近员工距离
ll get_dist(const set<pair<ll, int>>& s, ll val_axis, int sign) {
    if (s.empty()) return INF;
    if (sign == 1) { // 找大于 val_axis 的最小值
        auto it = s.upper_bound({val_axis, INF});
        if (it != s.end()) return abs(it->first - val_axis);
    } else { // 找小于 val_axis 的最大值
        auto it = s.lower_bound({val_axis, -1});
        if (it != s.begin()) {
            --it;
            return abs(val_axis - it->first);
        }
    }
    return INF;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m >> p >> q)) return 0;

    for (int i = 1; i <= p; i++) {
        ll x, y;
        cin >> x >> y;
        emp[i] = {x, y};
        idx_x[x].insert({y, i});
        idx_y[y].insert({x, i});
        idx_add[x + y].insert({x, i});
        idx_sub[y - x].insert({x, i});
    }

    while (q--) {
        ll u, v, t;
        cin >> u >> v >> t;

        ll k = INF;

        // 💥 第一阶段：探测 8 个方向的最小距离
        // 0: 右 (x变大, y不变)
        k = min(k, get_dist(idx_y[v], u, 1));
        // 4: 左 (x变小, y不变)
        k = min(k, get_dist(idx_y[v], u, -1));
        // 2: 上 (x不变, y变大)
        k = min(k, get_dist(idx_x[u], v, 1));
        // 6: 下 (x不变, y变小)
        k = min(k, get_dist(idx_x[u], v, -1));
        // 1: 右上 (x+ y+, y-x 不变)
        k = min(k, get_dist(idx_sub[v - u], u, 1));
        // 5: 左下 (x- y-, y-x 不变)
        k = min(k, get_dist(idx_sub[v - u], u, -1));
        // 7: 右下 (x+ y-, x+y 不变)
        k = min(k, get_dist(idx_add[u + v], u, 1));
        // 3: 左上 (x- y+, x+y 不变)
        k = min(k, get_dist(idx_add[u + v], u, -1));

        // 碰撞墙壁的最小距离
        ll k_bound = min({u - 1, n - u, v - 1, m - v});

        // 如果撞墙了或者找不到人，k 置 0
        if (k > k_bound || k == INF) {
            k = 0;
        }

        if (k == 0) continue;

        // 💥 第二阶段：精准抓取这 8 个点的实体
        vector<pair<int, int>> moves; // 存 {员工ID, 新的方向索引}
        for (int i = 0; i < 8; i++) {
            ll tx = u + k * dx[i];
            ll ty = v + k * dy[i];
            
            // 用 x 雷达直接点对点查询这个绝对坐标上有没有人
            auto it = idx_x[tx].lower_bound({ty, 0});
            if (it != idx_x[tx].end() && it->first == ty) {
                int id = it->second;
                int new_dir = (i + t) % 8; // 逆时针旋转
                moves.push_back({id, new_dir});
            }
        }

        // 💥 第三阶段：执行物理跃迁
        // 必须先存下来再统一移动，防止有人移动到了接下来要扫描的旧坐标上产生幽灵碰撞！
        for (auto& m : moves) {
            int id = m.first;
            int dir = m.second;
            ll nx = u + k * dx[dir];
            ll ny = v + k * dy[dir];
            move_emp(id, nx, ny);
        }
    }

    // 终极结算
    ll ans = 0;
    for (ll i = 1; i <= p; i++) { // 💥 员工上限是 p！
        ans ^= (i * emp[i].x + emp[i].y);
    }
    cout << ans << "\n";

    return 0;
}