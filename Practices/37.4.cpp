#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long
#define P 998244353

using namespace std;

// 绝对防爆：安全的 GCD 引擎，不需要任何多余的取模和防 0 判定
ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// 绝对防爆：等差数列求和
// 原理：(首项 + 末项) * 项数 / 2
ll sumi(ll a, ll b) {
    if (a > b) return 0;
    // 💥 修复数据溢出：(a+b)*(b-a+1) 必须在 long long 域内完成
    // 因为 a+b 和 b-a+1 的奇偶性不同，乘积绝对是偶数，可以直接除以 2，不会有精度损失！
    // 绝对不能先取模再除以 2，否则在模意义下除法必须算逆元！
    ll sum = (a + b) * (b - a + 1) / 2;
    return sum % P;
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (!(cin >> n)) return 0;

    // 避免 VLA，动态分配
    vector<ll> a(n + 1);
    vector<ll> q(n + 1); // q[i] 记录以 i 为起点的连续块的 GCD
    vector<int> num;     // 记录每个 GCD 变化块的起始下标

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ll total_sum = 0;

    // 时间轴推进：R 从 1 到 n
    for (int R = 1; R <= n; R++) {
        
        // 1. 将新来的 a[R] 作为一个独立的块加入
        num.push_back(R);
        q[R] = a[R];

        vector<int> next_num;
        ll last_q = -1;

        // 2. 遍历所有块的起始点，进行能量传导与物理合并
        for (size_t t = 0; t < num.size(); t++) {
            int i = num[t];
            
            // 重新计算这个起点的 GCD
            q[i] = gcd(q[i], a[R]);

            // 💥 摒弃 erase 灾难，采用双缓冲合并
            if (q[i] == last_q) {
                // 如果当前块的 GCD 和前一块的 GCD 相同，说明它们合并了！
                // 我们只需要丢弃当前的起点 i，让前一个块的领地自动延伸过来
            } else {
                // 如果不同，说明这是一个独立存在的块，保存它的起点
                next_num.push_back(i);
                last_q = q[i];
            }
        }
        
        // 转移内存控制权
        num = next_num;

        // 3. 结算当前 R 对全局答案的贡献
        ll current_R_sum = 0;
        
        for (size_t t = 0; t < num.size(); t++) {
            int start = num[t];
            // 当前块的末尾是：下一个块的起点 - 1。如果是最后一个块，末尾就是 R。
            int end = (t + 1 < num.size()) ? num[t + 1] - 1 : R;

            // 💥 极其严密的乘法防爆屏障
            ll l_sum = sumi(start, end);
            ll temp = (l_sum * q[start]) % P; // 先乘一个，立刻取模
            
            current_R_sum = (current_R_sum + temp) % P;
        }

        // 把 R 乘进最后的总和里，再次取模
        total_sum = (total_sum + current_R_sum * R) % P;
    }

    cout << total_sum << "\n";
    return 0;
}
