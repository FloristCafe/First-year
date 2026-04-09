#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

using namespace std;

const long long MOD = 998244353; // 绝对的素数防爆力场

// 💥 引擎底层：快速幂求逆元 (代替危险的除法)
long long qpow(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

long long inv(long long a) {
    return qpow(a, MOD - 2);
}

// 💥 第一阶段：词法分析器 (我们上一回合打造的防越界战车)
map<string, int> parse_formula(const string& formula) {
    map<string, int> elements;
    int len = formula.length();
    int i = 0;
    while (i < len) {
        string name = "";
        while (i < len && isalpha(formula[i])) {
            name += formula[i];
            i++;
        }
        int count = 0;
        while (i < len && isdigit(formula[i])) {
            count = count * 10 + (formula[i] - '0');
            i++;
        }
        if (count == 0) count = 1;
        elements[name] += count;
    }
    return elements;
}

void solve() {
    int m;
    cin >> m;

    // 动态分配内存池
    map<string, int> elem_to_id;
    int row_cnt = 0; // 记录有多少种不同的化学元素 (矩阵的行数)

    // A[行:元素][列:物质]
    // 假设最多 500 种元素，m 种物质，绝对够用
    vector<vector<long long>> A(505, vector<long long>(m, 0));

    // 💥 第二阶段：矩阵装载
    for (int col = 0; col < m; col++) {
        string formula;
        cin >> formula;
        map<string, int> elems = parse_formula(formula);

        for (auto const& [name, count] : elems) {
            // 给每个新出现的元素分配一个绝对物理 ID
            if (elem_to_id.find(name) == elem_to_id.end()) {
                elem_to_id[name] = row_cnt++;
            }
            int row = elem_to_id[name];
            A[row][col] = count % MOD; // 注入矩阵
        }
    }

    // 💥 第三阶段：模空间高斯消元引擎 (求秩)
    int rank = 0;
    for (int col = 0; col < m && rank < row_cnt; col++) {
        // 1. 寻找主元 (寻找防爆锚点)
        int pivot = rank;
        while (pivot < row_cnt && A[pivot][col] == 0) {
            pivot++;
        }
        
        // 如果这列全碎了，说明存在自由变量，直接跳过
        if (pivot == row_cnt) continue; 

        // 2. 行交换 (物理对齐)
        if (pivot != rank) {
            swap(A[rank], A[pivot]);
        }

        // 3. 主元归一化 (逆元除法替换)
        long long inv_val = inv(A[rank][col]);
        for (int j = col; j < m; j++) {
            A[rank][j] = (A[rank][j] * inv_val) % MOD;
        }

        // 4. 绝对消除 (向下清扫所有能量)
        for (int i = rank + 1; i < row_cnt; i++) {
            if (A[i][col] != 0) {
                long long factor = A[i][col];
                for (int j = col; j < m; j++) {
                    // C++ 负数取模防爆盾：先减去，再加 MOD，再取模
                    A[i][j] = (A[i][j] - factor * A[rank][j]) % MOD;
                    if (A[i][j] < 0) A[i][j] += MOD; 
                }
            }
        }
        rank++; // 确立一个维度的绝对壁垒
    }

    // 💥 最终裁决
    if (rank < m) cout << "Y\n";
    else cout << "N\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (cin >> n) {
        while (n--) {
            solve();
        }
    }
    return 0;
}