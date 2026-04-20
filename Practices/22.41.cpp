#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;
const int MAX_A = 100005;

bool has_obs[MAX_A] = {false};
int obs_idx[MAX_A] = {0};
long long dp[1005] = {0};
int a[1005];

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int max_coord = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        has_obs[a[i]] = true;
        obs_idx[a[i]] = i;
        if (a[i] > max_coord) {
            max_coord = a[i];
        }
    }

    // 初始宇宙：第一个障碍物作为起点的方案数为 1
    dp[1] = 1;

    // 💥 引擎点火：正向拓扑扫描
    for (int i = 1; i < n; i++) {
        if (dp[i] == 0) continue; // 没有势能的节点直接跳过

        // 探针发射：枚举所有的步长 d
        for (int d = 1; a[i] + 2 * d <= max_coord; d++) {
            int pos = a[i] + d;
            
            // 物理法则限制：第一步绝对不能踩雷（防止空集产生）
            if (has_obs[pos]) {
                continue;
            }
            
            // 在真空中持续跃迁，直到撞击下一个星球(障碍物)
            pos += d;
            while (pos <= max_coord) {
                if (has_obs[pos]) {
                    int j = obs_idx[pos];
                    dp[j] = (dp[j] + dp[i]) % MOD; // 势能注入
                    break; // 撞击后完成该段种植，探针停止
                }
                pos += d;
            }
        }
    }

    // 终局汇报
    cout << dp[n] << "\n";

    return 0;
}
