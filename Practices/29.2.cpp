#include <iostream>
#include <vector>

using namespace std;

// 💥 维度跃迁：算力代价极有可能击穿 int，必须全局 long long！
typedef long long ll;

int n, k;
ll m;
int t[100005];
int c[100005];

// 核心雷达：测试能否在 target 天内完工
bool check(int target) {
    ll required_cost = 0;
    for (int i = 1; i <= n; i++) {
        if (t[i] > target) {
            // 💥 注意：(t[i] - target) * c[i] 会产生大数，必须强制转换为 long long 运算！
            required_cost += 1LL * (t[i] - target) * c[i];
            
            // 极限防爆剪枝：如果中途发现需要的代价已经超过了拥有的资源 m，直接宣告失败！
            if (required_cost > m) return false;
        }
    }
    return required_cost <= m;
}

int main() {
    // 解除物理封锁
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m >> k)) return 0;

    int max_t = 0;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> c[i];
        if (t[i] > max_t) max_t = t[i]; // 寻找初始状态下最长的那一天，作为二分的右边界
    }

    // 二分引擎点火
    int left = k;          // 物理极限：最少不能少于 k 天
    int right = max_t;     // 初始状态：最多就是不加速时的最大天数
    int ans = max_t;

    while (left <= right) {
        int mid = left + (right - left) / 2; // 防溢出的中点求法
        if (check(mid)) {
            ans = mid;       // 记录当前能达到的天数
            right = mid - 1; // 尝试继续施压，看能不能压缩得更短
        } else {
            left = mid + 1;  // 算力不够，目标定得太高了，必须放宽天数
        }
    }

    cout << ans << "\n";
    return 0;
}