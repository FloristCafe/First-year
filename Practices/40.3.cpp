#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 物理探针：将当前虚拟视角的坐标，映射到真实的物理内存坐标
pair<int, int> get_phys(int r, int c, int global_cw, int Z) {
    if (global_cw == 0) return {r, c};
    if (global_cw == 1) return {Z - 1 - c, r};
    if (global_cw == 2) return {Z - 1 - r, Z - 1 - c};
    return {c, Z - 1 - r};
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Z;
    if (!(cin >> Z)) return 0;

    vector<string> A(Z);
    for (int i = 0; i < Z; ++i) {
        cin >> A[i];
    }

    int k;
    cin >> k;
    vector<int> K(k);
    for (int i = 0; i < k; ++i) {
        cin >> K[i];
    }

    int t = K[0];
    int global_cw = 0; // 记录整个宇宙的相对顺时针旋转次数

    // 💥 引擎点火：时间轴绝对倒转
    for (int i = t - 1; i >= 0; --i) {
        int idx = 1 + i * 6;
        int op = K[idx];

        if (op == 1) {
            // 物理校准：全部转换为 0-based
            int u = K[idx + 1] - 1;
            int v = K[idx + 2] - 1;
            int L = K[idx + 3];
            int d = K[idx + 4];
            int r = K[idx + 5];

            // 1. 逆转全局旋转：原本是 CCW r 次，逆向操作为 CW r 次
            global_cw = (global_cw + r) % 4;

            // 2. 抽取当前虚拟视图下的子阵列
            vector<vector<char>> temp(L, vector<char>(L));
            for (int row = 0; row < L; ++row) {
                for (int col = 0; col < L; ++col) {
                    auto p = get_phys(u + row, v + col, global_cw, Z);
                    temp[row][col] = A[p.first][p.second];
                }
            }

            // 3. 逆向局部旋转：原本是 CW d 度，现在进行 CCW d 度
            vector<vector<char>> next_temp(L, vector<char>(L));
            for (int row = 0; row < L; ++row) {
                for (int col = 0; col < L; ++col) {
                    if (d == 90) {
                        next_temp[L - 1 - col][row] = temp[row][col];
                    } else if (d == 180) {
                        next_temp[L - 1 - row][L - 1 - col] = temp[row][col];
                    } else if (d == 270) {
                        next_temp[col][L - 1 - row] = temp[row][col];
                    }
                }
            }

            // 4. 写回物理内存
            for (int row = 0; row < L; ++row) {
                for (int col = 0; col < L; ++col) {
                    auto p = get_phys(u + row, v + col, global_cw, Z);
                    A[p.first][p.second] = next_temp[row][col];
                }
            }
        } else if (op == 2) {
            int u = K[idx + 1] - 1;
            int d_idx = K[idx + 2] - 1;
            int l = K[idx + 3] - 1;
            int r_idx = K[idx + 4] - 1;
            int o = K[idx + 5];

            int H = d_idx - u + 1;
            int W = r_idx - l + 1;

            // 提取
            vector<vector<char>> temp(H, vector<char>(W));
            for (int row = 0; row < H; ++row) {
                for (int col = 0; col < W; ++col) {
                    auto p = get_phys(u + row, l + col, global_cw, Z);
                    temp[row][col] = A[p.first][p.second];
                }
            }

            // 逆翻转（翻转的逆操作就是它本身）
            vector<vector<char>> next_temp(H, vector<char>(W));
            for (int row = 0; row < H; ++row) {
                for (int col = 0; col < W; ++col) {
                    if (o == 1) { // 上下翻转
                        next_temp[H - 1 - row][col] = temp[row][col];
                    } else if (o == -1) { // 左右翻转
                        next_temp[row][W - 1 - col] = temp[row][col];
                    }
                }
            }

            // 写回
            for (int row = 0; row < H; ++row) {
                for (int col = 0; col < W; ++col) {
                    auto p = get_phys(u + row, l + col, global_cw, Z);
                    A[p.first][p.second] = next_temp[row][col];
                }
            }
        }
    }

    // 💥 坍缩量子态，通过最终计算好的视角，提取解密图景
    vector<string> final_A(Z, string(Z, ' '));
    for (int i = 0; i < Z; ++i) {
        for (int j = 0; j < Z; ++j) {
            auto p = get_phys(i, j, global_cw, Z);
            final_A[i][j] = A[p.first][p.second];
        }
    }

    // 探测原始尺寸（系统在右下方补齐 '?'，因此非 '?' 的最远边界即为长宽）
    int n = 0, m = 0;
    while (n < Z && final_A[n][0] != '?') n++;
    while (m < Z && final_A[0][m] != '?') m++;

    cout << n << " " << m << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << final_A[i][j];
        }
        cout << "\n";
    }

    return 0;
}