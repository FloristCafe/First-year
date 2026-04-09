#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 绝对防爆：涉及金钱和成本，必须使用 long long
const long long INF = 1e18; 

struct Warehouse {
    long long b;
    long long c;
    priority_queue<long long> pq; // 贪心引擎核心
};

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long v;
    if (!(cin >> n >> m >> v)) return 0;

    vector<Warehouse> rep(n);
    for (int i = 0; i < n; i++) {
        cin >> rep[i].b >> rep[i].c;
    }

    // 💥 物理过滤与装填
    for (int i = 0; i < m; i++) {
        long long a;
        int t;
        cin >> a >> t;
        // 绝对剔除法则：净收益为负的垃圾资产当场抹杀
        if (a > rep[t].c) {
            rep[t].pq.push(a);
        }
    }

    // dp[j]：获得至少 j 的利润，所需要的最小绝对成本
    // 内存绝对坍缩：数组大小死死卡在 v + 1
    vector<long long> dp(v + 1, INF);
    dp[0] = 0; 

    // 💥 状态机启动：逐个跨越仓库维度
    for (int i = 0; i < n; i++) {
        if (rep[i].pq.empty()) continue;

        // 1. 策略池提取：将 pq 里的高能货物转化为具体的 (利润, 成本) 策略
        vector<pair<long long, long long>> choices;
        long long profit_sum = -rep[i].b; // 初始扣除基础开启费
        long long cost_sum = rep[i].b;
        int k = 0;

        while (!rep[i].pq.empty()) {
            long long a = rep[i].pq.top();
            rep[i].pq.pop(); // 正确的 pq 提取法则
            k++;
            profit_sum += (a - rep[i].c);
            cost_sum += rep[i].c;
            
            // 只有整套动作能带来正向收益，才有资格进入策略池
            if (profit_sum > 0) {
                choices.push_back({profit_sum, cost_sum});
            }
        }

        if (choices.empty()) continue;

        // 2. 分组背包跃迁：逆向遍历防止同一仓库被重复叠加
        vector<long long> new_dp = dp;
        for (const auto& choice : choices) {
            long long p = choice.first;
            long long cost = choice.second;

            // 必须遍历所有的已有状态 j
            for (int j = 0; j <= v; j++) {
                if (dp[j] != INF) {
                    // 💥 能量截断：超过目标 v 的利润，全部坍缩到 v 
                    long long nxt = min(v, j + p);
                    new_dp[nxt] = min(new_dp[nxt], dp[j] + cost);
                }
            }
        }
        
        // 3. 单调性物理修正：获得“至少 j 利润”的成本，绝对不能高于“至少 j+1 利润”
        for (long long j = v - 1; j >= 0; j--) {
            if (new_dp[j + 1] < new_dp[j]) {
                new_dp[j] = new_dp[j + 1];
            }
        }

        // 状态覆盖
        dp = move(new_dp);
    }

    // 最终裁决
    if (dp[v] == INF) {
        cout << -1 << "\n"; // 如果根本达不到目标
    } else {
        cout << dp[v] << "\n";
    }

    return 0;
}