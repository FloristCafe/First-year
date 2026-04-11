#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const long long INF = 1e18; // 绝对的物理深渊

struct Station {
    long long x, y, r, t;
};

struct Point {
    long long x, y;
};

int main() {
    // 💥 绝对的 I/O 解封，防止被 2.5 * 10^7 次操作拖后腿
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Point> pts(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }

    vector<Station> sts(m + 1);
    for (int j = 1; j <= m; ++j) {
        cin >> sts[j].x >> sts[j].y >> sts[j].r >> sts[j].t;
    }

    // 💥 物理链路构建：动态邻接表
    // p2s[i] 存储点 i 能进入的所有基站
    // s2p[j] 存储基站 j 能覆盖的所有点
    vector<vector<int>> p2s(n + 1);
    vector<vector<int>> s2p(m + 1);

    for (int j = 1; j <= m; ++j) {
        long long sx = sts[j].x, sy = sts[j].y, sr = sts[j].r;
        for (int i = 1; i <= n; ++i) {
            // 正方形覆盖判定：切比雪夫距离 (Chebyshev distance)
            if (abs(pts[i].x - sx) <= sr && abs(pts[i].y - sy) <= sr) {
                s2p[j].push_back(i);
                p2s[i].push_back(j);
            }
        }
    }

    // 💥 核心寻路引擎：Dijkstra
    // 维度统一：1 到 n 是点，n+1 到 n+m 是基站
    vector<long long> dist(n + m + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // 剪枝：过期状态拦截
        if (d > dist[u]) continue;

        // 抵达绝对终点，立刻切断计算
        if (u == n) {
            cout << d << "\n";
            return 0;
        }

        if (u <= n) {
            // 当前处于点，探查其覆盖的所有基站
            for (int station_idx : p2s[u]) {
                int v = n + station_idx;
                long long weight = sts[station_idx].t; // 进入基站需要支付延迟
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        } else {
            // 当前处于基站，探查其覆盖的所有点
            int station_idx = u - n;
            for (int pt_idx : s2p[station_idx]) {
                // 离开基站到达点不需要额外延迟 (weight = 0)
                if (dist[u] < dist[pt_idx]) { 
                    dist[pt_idx] = dist[u];
                    pq.push({dist[pt_idx], pt_idx});
                }
            }
        }
    }

    cout << "Nan\n";
    return 0;
}