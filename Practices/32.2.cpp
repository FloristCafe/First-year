#include <iostream>
#include <vector>

using namespace std;

const int MAX_SQRT = 100005; // 10^5 是 10^10 的绝对平方根物理上限
vector<int> primes;
bool is_prime[MAX_SQRT];

// 引擎冷启动：欧拉线性筛预处理素数雷达
void euler_sieve() {
    fill(is_prime, is_prime + MAX_SQRT, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MAX_SQRT; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (int p : primes) {
            if (i * p >= MAX_SQRT) break;
            is_prime[i * p] = false;
            if (i % p == 0) break; // 绝对剪枝：保证每个合数只被其最小素因子筛去
        }
    }
}

int main() {
    // 解除 I/O 物理封锁，这是高频数据流查询的绝对起手式
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    euler_sieve();

    int q;
    if (!(cin >> q)) return 0;

    while (q--) {
        long long n;
        int k;
        cin >> n >> k;

        long long ans = 1;
        long long temp = n;

        // 扫描素数雷达
        for (int p : primes) {
            // 💥 动态边界坍缩：如果剩下的数字连当前素数的平方都不到，直接停止钻探！
            if (1LL * p * p > temp) break; 
            
            if (temp % p == 0) {
                int count = 0;
                long long current_pow = 1;
                
                // 剥离该素数的所有维度
                while (temp % p == 0) {
                    count++;
                    current_pow *= p;
                    temp /= p;
                }
                
                // 指挥部判定：是否达到阈值 k
                if (count >= k) {
                    ans *= current_pow;
                }
            }
        }

        // 💥 终极防线：残留幽灵素数
        // 如果 temp 被榨干后依然 > 1，说明它本身就是一个巨大的素数，且其指数绝对为 1！
        if (temp > 1) {
            if (1 >= k) { // 只有当阈值 k <= 1 (即 k == 1) 时，指数为 1 的幽灵素数才配活下来
                ans *= temp;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}