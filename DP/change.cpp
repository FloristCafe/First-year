// File: coin_change.cpp
// 描述: 零钱兑换 (最少硬币数) - 完全背包的物理变种
// 编译指令建议: g++ -Wall -Wextra -O2 coin_change.cpp -o coin_change

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 极其冷血的毒药定义：正无穷大 (防溢出，用 1e9)
const int INF = 1e9;

int main() {
    // 物理层 I/O 压榨
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    // n: 硬币种类数, m: 目标总金额
    if (!(cin >> n >> m)) return 0;

    // 绝对的 1 号位对齐
    vector<int> coins(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> coins[i];
    }

    // 内存装甲强化：金额最大 m，数组开到 m + 1
    // 法则一：求 min，除 dp[0] 外全部毒化为正无穷 INF
    vector<int> dp(m + 1, INF);
    dp[0] = 0; // 唯一的合法物理奇点：0元需要0个硬币

    // 状态机启动
    for (int i = 1; i <= n; ++i) {
        // 法则三：硬币无限，必须从 coins[i] 正向引力场推进至 m！
        for (int j = coins[i]; j <= m; ++j) {
            // 法则二：代价降维，+1 绝对在方括号外面！
            // 如果 dp[j-coins[i]] 是毒药 (INF)，加 1 后依然是极大的数，会被 min 无情淘汰
            dp[j] = min(dp[j], dp[j - coins[i]] + 1);
        }
    }

    // 终极清算：如果 dp[m] 依然是 INF，说明没有任何合法路径能凑出 m
    if (dp[m] == INF) {
        cout << "-1\n";
    } else {
        cout << dp[m] << "\n";
    }

    return 0;
}