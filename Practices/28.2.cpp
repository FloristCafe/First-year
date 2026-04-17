#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> p(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> p[i];
    }

    vector<int> t(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> t[i];
    }

    vector<int> earliest(m + 1, 1);
    bool possible = true;

    // 💥 第一阶段：正向光速顺推，计算最早时间
    for (int i = 1; i <= m; ++i) {
        if (p[i] != 0) {
            earliest[i] = earliest[p[i]] + t[p[i]];
        }
        // 物理防爆探针：如果最早开始时间加上耗时已经越界，宣告任务失败
        if (earliest[i] + t[i] - 1 > n) {
            possible = false;
        }
    }

    // 打印第一行：最早开始时间
    for (int i = 1; i <= m; ++i) {
        cout << earliest[i] << (i == m ? "" : " ");
    }
    cout << "\n";

    // 如果越界，直接掐断进程，拒绝执行无意义的死线推演
    if (!possible) return 0;

    // 💥 第二阶段：逆向时光倒流，收缩最晚死线
    vector<int> latest(m + 1);
    for (int i = 1; i <= m; ++i) {
        latest[i] = n - t[i] + 1; // 设定初始的绝对物理边界
    }

    // 从后往前剥离依赖
    for (int i = m; i >= 1; --i) {
        if (p[i] != 0) {
            // 被依赖者的最晚时间，受到依赖者最晚时间的强制挤压
            latest[p[i]] = min(latest[p[i]], latest[i] - t[p[i]]);
        }
    }

    // 打印第二行：最晚开始时间
    for (int i = 1; i <= m; ++i) {
        cout << latest[i] << (i == m ? "" : " ");
    }
    cout << "\n";

    return 0;
}
