#include<iostream>
#include<vector>
using namespace std;

// 绝对防爆：全部使用 long long，防止乘法溢出
long long q[10005][25];
long long k[25][10005]; // 物理前置转置 K^T
long long v[10005][25];
long long w[10005];

int main(){
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, d;
    if(!(cin >> n >> d)) return 0;
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < d; j++)
            cin >> q[i][j];
            
    // 完美的转置读入
    for(int i = 0; i < n; i++)
        for(int j = 0; j < d; j++)
            cin >> k[j][i]; 
            
    for(int i = 0; i < n; i++)
        for(int j = 0; j < d; j++)
            cin >> v[i][j];
            
    for(int i = 0; i < n; i++)
        cin >> w[i];
        
    // ------------------------------------------------
    // 物理引擎第一段：计算微型核心 T = K^T * V
    // 维度：(d * n) x (n * d) = d * d
    // ------------------------------------------------
    long long T[25][25] = {0}; 
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            for(int t = 0; t < n; t++){
                T[i][j] += k[i][t] * v[t][j];
            }
        }
    }
    
    // ------------------------------------------------
    // 物理引擎第二段：计算最终答案 Ans = (W * Q) * T
    // 维度：(n * d) x (d * d) = n * d
    // ------------------------------------------------
    for(int i = 0; i < n; i++){          // 行遍历 n
        for(int j = 0; j < d; j++){      // 列遍历 d
            long long ans_ij = 0;
            for(int t = 0; t < d; t++){  // 内积遍历 d
                // 实时将权重 w[i] 赋予 q[i][t]
                ans_ij += (q[i][t] * w[i]) * T[t][j]; 
            }
            // 直接输出，不需要开巨大的数组去存最终答案，节约内存
            cout << ans_ij << " ";
        }
        cout << "\n"; // 每算完一行，记得物理换行！
    }
    
    return 0;
}