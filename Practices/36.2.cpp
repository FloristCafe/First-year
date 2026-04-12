#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 绝对防爆：能量总和极易超过 int 上限，必须启用 64 位整数
const long long MIN_INF = -4e18;

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> a[i];
    }

    vector<long long> b(n + 1, 0); 
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    // 阶段一：计算每个站点的绝对物理门槛 P_k
    vector<long long> P(n + 1);
    P[0] = a[0];
    for (int i = 1; i <= n; ++i) {
        P[i] = P[i - 1] + a[i] - b[i];
    }

    // 阶段二：建立时空缓存雷达（前缀最大值与后缀最大值）
    vector<long long> pref_max(n + 1);
    pref_max[0] = P[0];
    for (int i = 1; i <= n; ++i) {
        pref_max[i] = max(pref_max[i - 1], P[i]);
    }

    vector<long long> suff_max(n + 2, MIN_INF);
    suff_max[n] = P[n];
    for (int i = n - 1; i >= 0; --i) {
        suff_max[i] = max(suff_max[i + 1], P[i]);
    }

    // 阶段三：接受高频询问，进行 O(1) 的多维时空拼接
    for (int i = 1; i <= n; ++i) {
        // 意外发生前的历史最高门槛 vs 意外发生后的未来最高门槛 + 补偿
        long long ans = max(pref_max[i - 1], suff_max[i] + b[i]);
        cout << ans << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}