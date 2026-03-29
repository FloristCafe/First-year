#include <iostream>
using namespace std;

int n, m;
long long tree[500005] = {0};

// 引擎一：提取最低位的 1
int lowbit(int x) {
    return x & (-x);
}

// 引擎二：单点修改，物理波纹向上扩散
void add(int x, int k) {
    while (x <= n) {
        tree[x] += k;
        x += lowbit(x);
    }
}

// 引擎三：前缀查询，物理区块向下拼接
long long query(int x) {
    long long sum = 0;
    while (x > 0) {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}

int main() {
    // 极速 I/O 装甲
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    // 初始建树：用极速修改代替静态赋值
    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        add(i, val);
    }

    // 战争循环：处理 M 次指令
    for (int i = 1; i <= m; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            // 单点加上 y
            add(x, y);
        } else if (op == 2) {
            // 区间查询 [x, y]
            cout << query(y) - query(x - 1) << "\n";
        }
    }

    return 0;
}
