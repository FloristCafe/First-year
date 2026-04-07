#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 解除 I/O 物理封锁，这是你以后写每一道题的绝对起手式
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 💥 抛弃容易越界的全局原生数组，使用现代 C++ 的 vector 矩阵
    // 维度设为 (n + 1) 行 m 列，完美贴合从 1 开始的编号习惯
    vector<vector<int>> pos(n + 1, vector<int>(m));
    
    // 录入数据
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> pos[i][j];
        }
    }

    // 核心检阅引擎
    for (int i = 1; i <= n; i++) {
        int upper_id = 0; // 默认没有上级

        for (int j = 1; j <= n; j++) {
            if (i == j) continue; // 绝对物理法则：自己不能是自己的上级

            bool is_upper = true; // 预设 j 是 i 的上级
            
            for (int k = 0; k < m; k++) {
                // 💥 一票否决法则：只要有一维不满足严格大于，直接枪毙
                if (pos[j][k] <= pos[i][k]) {
                    is_upper = false;
                    break; 
                }
            }

            // 如果经历了所有维度的审查，开关依然是 true
            if (is_upper) {
                upper_id = j;
                break; // 💥 贪心拦截：因为 j 是从小到大遍历的，第一个找到的绝对是编号最小的！直接结束寻找！
            }
        }

        cout << upper_id << "\n";
    }

    return 0;
}