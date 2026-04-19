#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int max_a = 0;
    vector<int> A(n + 1, 0); // 物理设定：A[0] = 0 作为绝对海平面起点
    
    for (int i = 1; i <= n; ++i) {
        cin >> A[i];
        if (A[i] > max_a) {
            max_a = A[i];
        }
    }

    // CCF 官方数据中 max_a 一般在 10^4 级别，直接开辟物理空间
    // 如果极端情况下 max_a 高达 10^9，只需将 diff 换成 std::map 或进行坐标离散化
    vector<int> diff(max_a + 2, 0);

    // 💥 引擎点火：左岸势能注入
    for (int i = 1; i <= n; ++i) {
        if (A[i] > A[i - 1]) {
            // 当 p 落在 [A[i-1] + 1, A[i]] 区间时，位置 i 成为合法左岸
            // 差分数组标准操作：起点 +1，终点后一位 -1
            diff[A[i - 1] + 1]++;
            diff[A[i] + 1]--;
        }
    }

    int current_segments = 0;
    int max_segments = 0;

    // 💥 终局清算：前缀和还原各水位的绝对非零段数量
    for (int p = 1; p <= max_a; ++p) {
        current_segments += diff[p];
        if (current_segments > max_segments) {
            max_segments = current_segments;
        }
    }

    // 如果整个数组都是 0，max_segments 会维持 0，符合物理逻辑
    cout << max_segments << "\n";

    return 0;
}