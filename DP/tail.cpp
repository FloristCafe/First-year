#include <iostream>
#include <vector>
#include <algorithm> // lower_bound 的绝对载体

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // tails 数组：存放每个长度下的最小结尾值
    vector<int> tails;
//代表存在一个长为i的序列，结尾是tail[i]
    // 引擎启动
    for (int i = 0; i < n; ++i) {
        // 在 tails 中二分寻找第一个 >= a[i] 的迭代器
        auto it = lower_bound(tails.begin(), tails.end(), a[i]);

        if (it == tails.end()) {
            // 指针越界了，说明 a[i] 比当前所有结尾都大
            // 绝对扩张！
            tails.push_back(a[i]);
        } else {
            // 找到了，极其冷血地将其替换，压榨出更大的潜能
            *it = a[i];
        }
    }

    // tails.size() 绝对等于最长递增子序列的物理长度！
    // (注意：tails 里的元素集合，不一定等于最终的那个子序列本身)
    cout << tails.size() << "\n";

    return 0;
}