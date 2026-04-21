<<<<<<< HEAD
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 物理探针：设定最大规模，直接开辟内存。采用 1-based 索引。
const int MAXN = 605;
int A[MAXN][MAXN];
long long P[MAXN][MAXN]; // 前缀和宇宙，可能极大，直接上 long long 防爆

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, L, r, t;
    if (!(cin >> n >> L >> r >> t)) return 0;

    // 💥 第一阶段：构建二维前缀和金字塔
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> A[i][j];
            // 容斥缝合：左边 + 上边 - 左上角重复区域 + 自身
            P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + A[i][j];
        }
    }

    int dark_count = 0;

    // 💥 第二阶段：O(1) 绝对清算
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            // 计算当前像素 (i, j) 邻域的物理边界，并死死锁在 [1, n] 范围内
            int x1 = max(1, i - r);
            int y1 = max(1, j - r);
            int x2 = min(n, i + r);
            int y2 = min(n, j + r);

            // 邻域的真实像素总数
            long long area = (long long)(x2 - x1 + 1) * (y2 - y1 + 1);

            // O(1) 提取邻域灰度总和
            long long current_sum = P[x2][y2] - P[x1 - 1][y2] - P[x2][y1 - 1] + P[x1 - 1][y1 - 1];

            // 比较均值，避免浮点数除法带来的极微小精度坍缩
            // current_sum / area <= t  绝对等价于 current_sum <= t * area
            if (current_sum <= (long long)t * area) {
                dark_count++;
            }
        }
    }

    cout << dark_count << "\n";
    return 0;
=======
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 物理探针：设定最大规模，直接开辟内存。采用 1-based 索引。
const int MAXN = 605;
int A[MAXN][MAXN];
long long P[MAXN][MAXN]; // 前缀和宇宙，可能极大，直接上 long long 防爆

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, L, r, t;
    if (!(cin >> n >> L >> r >> t)) return 0;

    // 💥 第一阶段：构建二维前缀和金字塔
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> A[i][j];
            // 容斥缝合：左边 + 上边 - 左上角重复区域 + 自身
            P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + A[i][j];
        }
    }

    int dark_count = 0;

    // 💥 第二阶段：O(1) 绝对清算
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            // 计算当前像素 (i, j) 邻域的物理边界，并死死锁在 [1, n] 范围内
            int x1 = max(1, i - r);
            int y1 = max(1, j - r);
            int x2 = min(n, i + r);
            int y2 = min(n, j + r);

            // 邻域的真实像素总数
            long long area = (long long)(x2 - x1 + 1) * (y2 - y1 + 1);

            // O(1) 提取邻域灰度总和
            long long current_sum = P[x2][y2] - P[x1 - 1][y2] - P[x2][y1 - 1] + P[x1 - 1][y1 - 1];

            // 比较均值，避免浮点数除法带来的极微小精度坍缩
            // current_sum / area <= t  绝对等价于 current_sum <= t * area
            if (current_sum <= (long long)t * area) {
                dark_count++;
            }
        }
    }

    cout << dark_count << "\n";
    return 0;
>>>>>>> e3718e7119451d180d0fc9eee75a2b96fa2e0eb4
}