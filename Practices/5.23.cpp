#include <iostream>
#include <vector>
#include <algorithm>

using namespace std; // 💥 基础物理法则

int a[35];
int dp[300005] = {0};

int main() {
    // 解除物理封锁
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    int sum = 0; // 💥 绝对纪律：变量声明必须初始化！
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    // 核心 DP 引擎点火
    int capacity = sum - x;
    
    // 💥 边界防爆：如果所有商品加起来都不够 X，或者刚好等于 X，直接返回
    if (capacity <= 0) {
        cout << sum << "\n";
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = capacity; j >= a[i]; j--) {
            // 毫不犹豫地状态转移，不需要任何多余的 if 废话
            dp[j] = max(dp[j], dp[j - a[i]] + a[i]);
        }
    }

    // 完美提取答案
    cout << sum - dp[capacity] << "\n";
    return 0;
}