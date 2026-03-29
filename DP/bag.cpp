// File: 01_knapsack.cpp
// 描述: 01背包问题 (一维空间优化)
// 编译指令建议: g++ -Wall -Wextra -O2 01_knapsack.cpp -o 01_knapsack

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 极其冷血的 I/O 优化
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M; 
    // N: 物品总数, M: 背包绝对容量上限
    if (!(cin >> N >> M)) return 0;

    // 绝对规范的变量命名与内存开辟
    vector<int> weight(N + 1, 0);
    vector<int> value(N + 1, 0);
    
    // dp 数组：记录容量为 j 时的最大价值。全部初始化为 0 的干净内存
    vector<long long> dp(M + 1, 0);

    // 严苛的 1 号位对齐，坚决避开 0 号黑洞
    for (int i = 1; i <= N; ++i) {
        cin >> weight[i] >> value[i];
    }

    // 状态机启动：外层遍历物品，内层逆向遍历容量
    for (int i = 1; i <= N; ++i) {
        // 绝对纪律：必须从 M 逆推至 weight[i]，防止物理状态跨维度自我污染
        for (int j = M; j >= weight[i]; --j) {
            //j表示容量
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }//对所有容量循环，看拿上会不会更好（dp[i]已经是目前最优）
    }

    // dp[M] 即为所有状态推演完毕后，容量为 M 时的绝对最优解
    cout << dp[M] << "\n";

    return 0;
}