#include<iostream>
#include<vector>
using namespace std;

int main() {
    int n, m, t;
    cin >> n >> m >> t;
    
    // 使用一维数组存储矩阵数据
    vector<int> data;
    data.reserve(n * m);
    
    // 读取初始矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int val;
            cin >> val;
            data.push_back(val);
        }
    }
    
    // 当前矩阵的状态
    int rows = n;      // 当前行数
    int cols = m;      // 当前列数
    bool transposed = false;  // 是否已转置
    
    for (int i = 0; i < t; i++) {
        int op;
        cin >> op;
        
        if (op == 1) {  // 重塑操作
            int p, q;
            cin >> p >> q;
            
            if (p * q != rows * cols) {
                continue;  // 实际上题目会保证合法
            }
            
            // 创建新的数据数组
            vector<int> new_data(p * q);
            
            if (transposed) {
                // 如果已转置，需要按列优先读取
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        // 计算在新矩阵中的位置
                        int new_idx = i * cols + j;
                        // 计算在原数据中的位置
                        int old_idx = j * rows + i;
                        new_data[new_idx] = data[old_idx];
                    }
                }
            }
            
            // 更新数据和状态
            data = move(new_data);
            rows = p;
            cols = q;
            transposed = false;  // 重塑后重置转置状态
            
        } else if (op == 2) {  // 转置操作
            int dummy1, dummy2;
            cin >> dummy1 >> dummy2;  // 读取两个0，但不使用
            
            // 交换行和列
            swap(rows, cols);
            // 翻转转置标志
            transposed = !transposed;
            
        } else if (op == 3) {  // 元素查询
            int i, j;
            cin >> i >> j;
            
            if (transposed) {
                // 如果已转置，访问data[j][i]
                cout << data[j * rows + i] << endl;
            } else {
                // 如果未转置，访问data[i][j]
                cout << data[i * cols + j] << endl;
            }
        }
    }
    
    return 0;
}