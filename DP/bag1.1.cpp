// File: exact_knapsack.cpp
// 描述: 01背包变种 - 恰好装满的绝对状态机
// 编译指令建议: g++ -Wall -Wextra -O2 exact_knapsack.cpp -o exact_knapsack

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 极其冷血的毒药定义：负无穷大
const int NEG_INF = -1e9;

int main() {
    // 物理层 I/O 压榨
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 绝对的 1 号位对齐：规避 0 号黑洞，长度开到 n+1
    vector<int> w(n + 1, 0);
    vector<int> v(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> w[i] >> v[i];
    }

    // 内存装甲强化：M 最大 10^5，数组必须开到 100005
    // 代数降维核心：除 dp[0] 外，全部毒化为 NEG_INF
    vector<int> dp(m + 1, NEG_INF);
    dp[0] = 0; // 唯一的合法物理奇点

    // 状态机启动
    for (int i = 1; i <= n; ++i) {
        // 逆推法则绝对坚守
        for (int j = m; j >= w[i]; --j) {
            // 如果 dp[j-w[i]] 是毒药，加上 v[i] 后依然是极小的负数
            // max() 会极其理性地将其淘汰
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }

    // 终极清算：如果 dp[m] 依然小于 0，说明没有任何合法路径能恰好装满
    if (dp[m] < 0) {
        cout << "-1\n";
    } else {
        cout << dp[m] << "\n";
    }

    return 0;
}