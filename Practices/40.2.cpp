#include <iostream>
#include <vector>

using namespace std;

// 物理探针：内联展开 f 函数，榨干最后一丝算力
inline int f(int x, int k) {
    return (((x * x + k * k) % 8) ^ k);
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> k_seq(m);
    for (int i = 0; i < m; ++i) {
        cin >> k_seq[i];
    }

    // 状态空间映射引擎：只有 512 个物理插槽
    vector<int> out_to_in(512);
    
    // 全宇宙穷举点火
    for (int i = 0; i < 512; ++i) {
        int cur = i;
        for (int step = 0; step < m; ++step) {
            int k = k_seq[step];
            
            // 掩码切割，提取高、中、低位
            int a = cur >> 6;
            int b = (cur >> 3) & 7;
            int c = cur & 7;

            // 状态跃迁
            int a_new = b;
            int b_new = c ^ f(b, k);
            int c_new = a ^ f(c, k);

            // 物理缝合
            cur = (a_new << 6) | (b_new << 3) | c_new;
        }
        // 记录时空坐标的绝对映射
        out_to_in[cur] = i;
    }

    // O(1) 终局清算
    for (int i = 0; i < n; ++i) {
        int a_val;
        cin >> a_val;
        cout << out_to_in[a_val] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}