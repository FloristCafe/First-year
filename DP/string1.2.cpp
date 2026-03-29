#include<iostream>
#include<vector>
using namespace std;
int n;
int findm(vector<int>s1,vector<int>s2){
// 绝对内存纪律：只开辟 2 行！
int dp[2][10005] = {0}; 

for (int i = 1; i <= N; i++) {
    // 💥 物理指针交替：利用二进制的最低位进行 0 和 1 的来回反转
    int curr = i & 1;       // 当前行的物理真实索引
    int prev = (i - 1) & 1; // 上一行的物理真实索引

    for (int j = 1; j <= M; j++) {
        if (s1[i - 1] == s2[j - 1]) {
            // 继承左上角的历史能量 + 1
            dp[curr][j] = dp[prev][j - 1] + 1; 
        } else {
            // 在上方和左方中进行冷血的打擂台
            dp[curr][j] = max(dp[prev][j], dp[curr][j - 1]); 
        }
    }
}
// 最终的答案，绝对驻留在最后一次充当 "curr" 的那一行里
}//dp滚动一定为O(n^2)(用树可能O（nlogn）),否则漏解