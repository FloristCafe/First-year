#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// 物理上限预估：n <= 16, k <= 5 (通常的卡牌收集数据规模限制)
// 最多需要的硬币数为 16 * 5 = 80。
double dp[1 << 16][85]; 
double p[20];
double sum_p[1 << 16];
vector<int> masks_by_popcnt[20];

// 物理探针：计算二进制状态中的 1 的个数
int get_popcount(int x) {
    int cnt = 0;
    while (x) {
        cnt++;
        x &= (x - 1);
    }
    return cnt;
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    int max_mask = 1 << n;

    // 💥 预处理降维：提前计算好每个集合转化硬币的概率，杜绝内层循环的算力浪费
    for (int S = 0; S < max_mask; ++S) {
        double current_sum = 0;
        for (int i = 0; i < n; ++i) {
            if (S & (1 << i)) {
                current_sum += p[i];
            }
        }
        sum_p[S] = current_sum;
        masks_by_popcnt[get_popcount(S)].push_back(S);
    }

    // 💥 核心引擎点火：逆向拓扑排序
    // 从收集了 n-1 种卡牌开始，一路倒推回 0 种卡牌的初始宇宙
    for (int cnt = n - 1; cnt >= 0; --cnt) {
        int max_coins = (n - cnt) * k;
        
        for (int S : masks_by_popcnt[cnt]) {
            // 硬币数量从极限阈值往下递推
            for (int c = max_coins - 1; c >= 0; --c) {
                double expected = 1.0; // 抽一次卡的固定代价
                
                for (int i = 0; i < n; ++i) {
                    if (!(S & (1 << i))) {
                        // 如果抽到了新卡，因为是全局初始化为 0，所以如果新状态达到终点，dp 值为 0 是绝对准确的
                        expected += p[i] * dp[S | (1 << i)][c];
                    }
                }
                
                // 抽到废卡转化为硬币的期望
                expected += sum_p[S] * dp[S][c + 1];
                
                dp[S][c] = expected;
            }
        }
    }

    // 输出初始状态：0张卡，0枚硬币
    cout << fixed << setprecision(5) << dp[0][0] << "\n";

    return 0;
}//