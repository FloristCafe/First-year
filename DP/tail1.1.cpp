// File: lis_core.cpp
// 描述: O(N log N) 最长递增子序列 (LIS) 降维引擎

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getLIS(vector<int>& a) {
    vector<int> tails;
    
    // 绝对干净的遍历：x 直接就是数组里的每一个元素实体
    for (int x : a) {
        auto t = lower_bound(tails.begin(), tails.end(), x);
        
        if (t == tails.end()) {
            tails.push_back(x); // 潜能突破，绝对扩张
        } else {
            *t = x;             // 潜能降维，冷血替换
        }
    }
    
    return tails.size();
}