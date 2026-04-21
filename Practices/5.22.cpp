#include <iostream>
#include <algorithm> // 为了使用 max

using namespace std;

// 💥 绝对防爆：时间轴极限是 2*10^5，开到 4*10^5 留下绝对安全的缓冲区！
const int MAX_TIME = 200005; 
int diff[MAX_TIME * 2] = {0}; 
int p[MAX_TIME * 2] = {0};

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, c;
    if (!(cin >> n >> m >> c)) return 0;

    int t, k;
    for (int i = 0; i < n; i++) {
        cin >> t >> k;

        // 核心数学映射：[L, R]
        int L = t - c - k + 1;
        int R = t - c;

        // 💥 极端防爆一：如果右边界都小于 1，说明即使在第 1 秒做核酸也来不及，直接丢弃该计划！
        if (R < 1) continue;

        // 💥 极端防爆二：如果左边界小于 1，强行锚定在合法的起点 1。
        L = max(1, L);

        // 差分法则：L 处 +1，R+1 处 -1
        diff[L] += 1;
        diff[R + 1] -= 1; 
    }

    // 状态还原：一次性将整个物理时间轴的前缀和全部推演完毕！
    // 不要依赖什么 tmax，直接推到题目给的查询上限即可
    for (int i = 1; i <= MAX_TIME; i++) {
        p[i] = p[i - 1] + diff[i];
    }

    int q;
    for (int i = 0; i < m; i++) {
        cin >> q;
        // O(1) 绝对响应
        cout << p[q] << "\n";
    }

    return 0;
}