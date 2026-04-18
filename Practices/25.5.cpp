#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>

using namespace std;

// 记忆化核心库，拒绝重复的算力挥霍
map<pair<vector<int>, int>, long long> memo;

// 核心状态机：A 为当前石子序列，turn 为当前回合 (0为小c，1为小z)
long long dfs(vector<int> A, int turn) {
    if (A.size() == 1) {
        return A[0];
    }
    
    pair<vector<int>, int> state = {A, turn};
    if (memo.count(state)) {
        return memo[state];
    }
    
    int n = A.size();
    long long res = (turn == 0) ? 1e18 : -1;
    
    // 物理切除：扔掉最左边的一堆
    vector<int> left_drop(A.begin() + 1, A.end());
    long long val_left = dfs(left_drop, 1 - turn);
    if (turn == 0) res = min(res, val_left);
    else res = max(res, val_left);
    
    // 物理切除：扔掉最右边的一堆
    vector<int> right_drop(A.begin(), A.end() - 1);
    long long val_right = dfs(right_drop, 1 - turn);
    if (turn == 0) res = min(res, val_right);
    else res = max(res, val_right);
    
    // 物理缝合：合并相邻的两堆
    for (int i = 0; i < n - 1; ++i) {
        vector<int> merged;
        merged.reserve(n - 1);
        for (int j = 0; j < i; ++j) merged.push_back(A[j]);
        merged.push_back(A[i] + A[i+1]);
        for (int j = i + 2; j < n; ++j) merged.push_back(A[j]);
        
        long long val_merge = dfs(merged, 1 - turn);
        if (turn == 0) res = min(res, val_merge);
        else res = max(res, val_merge);
    }
    
    return memo[state] = res;
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    if (!(cin >> n >> k)) return 0;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    cout << dfs(a, k) << "\n";
    
    return 0;
}