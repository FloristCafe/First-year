#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const double PI = acos(-1.0);

// 提取的 alpha 常数计算探针
double alpha(int u) {
    if (u == 0) return 1.0 / sqrt(2.0);
    return 1.0;
}

// 矩阵输出模块，拒绝冗余代码
void print_matrix(const vector<vector<int>>& mat) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << mat[i][j] << (j == 7 ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> Q(8, vector<int>(8));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> Q[i][j];
        }
    }

    int n, T;
    if (!(cin >> n >> T)) return 0;

    vector<int> scan_data(n);
    for (int i = 0; i < n; i++) {
        cin >> scan_data[i];
    }

    vector<vector<int>> M(8, vector<int>(8, 0));

    // 💥 阶段 1：Z 字形扫描引擎 (碰撞反弹状态机)
    int x = 0, y = 0;
    int dx = -1, dy = 1; // 初始向右上角发射
    
    for (int k = 0; k < n; k++) {
        M[x][y] = scan_data[k];
        if (k == 63) break; // 防止扫描数据越过 64 像素物理极限
        
        int nx = x + dx;
        int ny = y + dy;
        
        // 边界碰撞检测与航向修正
        if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) {
            if (dx == -1 && dy == 1) { // 撞击上边界或右边界
                if (y == 7) x++;      // 撞死在右侧，只能往下
                else y++;             // 撞在顶部，向右平移
                dx = 1; dy = -1;      // 方向翻转为左下
            } else {                   // 撞击左边界或下边界
                if (x == 7) y++;      // 撞死在底部，只能往右
                else x++;             // 撞在左侧，向下平移
                dx = -1; dy = 1;      // 方向翻转为右上
            }
        } else {
            // 安全空域，继续航行
            x = nx;
            y = ny;
        }
    }

    if (T == 0) {
        print_matrix(M);
        return 0;
    }

    // 💥 阶段 2：量化矩阵相乘
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            M[i][j] *= Q[i][j];
        }
    }

    if (T == 1) {
        print_matrix(M);
        return 0;
    }

    // 💥 阶段 3：离散余弦逆变换 (IDCT) 算力降维
    vector<vector<int>> M_prime(8, vector<int>(8, 0));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            double sum = 0;
            for (int u = 0; u < 8; u++) {
                for (int v = 0; v < 8; v++) {
                    double term = alpha(u) * alpha(v) * M[u][v];
                    term *= cos((PI / 8.0) * (i + 0.5) * u);
                    term *= cos((PI / 8.0) * (j + 0.5) * v);
                    sum += term;
                }
            }
            sum /= 4.0;
            
            // 四舍五入，加 128
            int pixel = (int)round(sum + 128);
            
            // 物理色彩空间绝对截断
            if (pixel > 255) pixel = 255;
            if (pixel < 0) pixel = 0;
            
            M_prime[i][j] = pixel;
        }
    }

    if (T == 2) {
        print_matrix(M_prime);
    }

    return 0;
}