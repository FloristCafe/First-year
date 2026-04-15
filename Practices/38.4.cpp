#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 998244353;

// 17x17 的高维空间底座
struct Matrix {
    long long mat[17][17];
    Matrix() {
        for (int i = 0; i < 17; i++)
            for (int j = 0; j < 17; j++)
                mat[i][j] = 0;
    }
};

// 矩阵乘法引擎 (严格防爆)
Matrix multiply(const Matrix& A, const Matrix& B) {
    Matrix C;
    for (int i = 0; i < 17; i++) {
        for (int k = 0; k < 17; k++) {
            if (A.mat[i][k] == 0) continue;
            for (int j = 0; j < 17; j++) {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 核心微观状态机：绝对硬编码，杜绝任何运行时的搜索消耗
int next_state(int i, char ch) {
    if (i == 16) return 16; // 绝对胜利状态锁定
    
    if (i >= 0 && i <= 6) { // M0：兼顾追踪
        if (i == 0) return (ch == 'c') ? 1 : 0;
        if (i == 1) return (ch == 'c') ? 2 : (ch == 's' ? 3 : 0);
        if (i == 2) return (ch == 'c') ? 2 : (ch == 's' ? 3 : (ch == 'f' ? 7 : 0)); // f触发M1
        if (i == 3) return (ch == 'p') ? 4 : (ch == 'c' ? 1 : 0);
        if (i == 4) return (ch == 'a') ? 5 : (ch == 'c' ? 1 : 0);
        if (i == 5) return (ch == 'r') ? 6 : (ch == 'c' ? 1 : 0);
        if (i == 6) return (ch == 'k') ? 13 : (ch == 'c' ? 1 : 0); // k触发M2
    }
    if (i >= 7 && i <= 12) { // M1：只猎杀 cspark
        if (i == 7) return (ch == 'c') ? 8 : 7;
        if (i == 8) return (ch == 'c') ? 8 : (ch == 's' ? 9 : 7);
        if (i == 9) return (ch == 'p') ? 10 : (ch == 'c' ? 8 : 7);
        if (i == 10) return (ch == 'a') ? 11 : (ch == 'c' ? 8 : 7);
        if (i == 11) return (ch == 'r') ? 12 : (ch == 'c' ? 8 : 7);
        if (i == 12) return (ch == 'k') ? 16 : (ch == 'c' ? 8 : 7); // 击杀完成
    }
    if (i >= 13 && i <= 15) { // M2：只猎杀 ccf
        if (i == 13) return (ch == 'c') ? 14 : 13;
        if (i == 14) return (ch == 'c') ? 15 : 13;
        if (i == 15) return (ch == 'c') ? 15 : (ch == 'f' ? 7 : 13); // 找到ccf，状态并入M1
    }
    return -1;
}

// 井号 # 带来的物理断层：清空前缀，但绝不改变宏观目标
int next_state_hash(int i) {
    if (i >= 0 && i <= 6) return 0;
    if (i >= 7 && i <= 12) return 7;
    if (i >= 13 && i <= 15) return 13;
    if (i == 16) return 16;
    return -1;
}

Matrix pow_M[35];

// 降维打击：向量乘矩阵，从 O(17^3) 直接砍到 O(17^2)
vector<long long> multiply_vec(const vector<long long>& V, const Matrix& M) {
    vector<long long> res(17, 0);
    for (int i = 0; i < 17; i++) {
        if (V[i] == 0) continue;
        for (int j = 0; j < 17; j++) {
            res[j] = (res[j] + V[i] * M.mat[i][j]) % MOD;
        }
    }
    return res;
}

// 空格地带的空间跃迁
void apply_gap(vector<long long>& V, long long gap) {
    for (int i = 0; i <= 30; i++) {
        if ((gap >> i) & 1) {
            V = multiply_vec(V, pow_M[i]);
        }
    }
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 构建基础跃迁矩阵
    Matrix baseM;
    for (int i = 0; i < 17; i++) {
        for (char ch = 'a'; ch <= 'z'; ch++) {
            int nxt = next_state(i, ch);
            baseM.mat[i][nxt]++;
        }
    }

    // 预处理 2 的次幂矩阵
    pow_M[0] = baseM;
    for (int i = 1; i <= 30; i++) {
        pow_M[i] = multiply(pow_M[i-1], pow_M[i-1]);
    }

    long long n, m;
    if (!(cin >> n >> m)) return 0;

    // 初始态：100% 在 M0_0
    vector<long long> V(17, 0);
    V[0] = 1;

    long long pos = 0;
    for (int i = 0; i < m; i++) {
        long long target;
        cin >> target;
        
        long long gap = target - pos - 1;
        apply_gap(V, gap); // 光速跃迁过字母区
        
        // 执行 # 井号的物理断层
        vector<long long> next_V(17, 0);
        for (int s = 0; s < 17; s++) {
            if (V[s] == 0) continue;
            int nxt = next_state_hash(s);
            next_V[nxt] = (next_V[nxt] + V[s]) % MOD;
        }
        V = next_V;
        
        pos = target;
    }

    // 跃迁最后一段尾巴
    long long gap = n - pos;
    apply_gap(V, gap);

    // 提取唯一的胜利状态
    cout << V[16] << "\n";
    
    return 0;
}