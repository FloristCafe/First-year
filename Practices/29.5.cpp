#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9; // 物理极限负无穷的绝对防爆设定
int n, m;

struct Node {
    int max_val;
    int min_val;
    int count_max;
    int lazy; // 懒标记：记录当前区间是否被彻底覆盖成了某一个固定的值
} tree[400005]; // 绝对防爆：4 倍空间

// --- 向上聚合：你刚刚放弃的物理坍缩 ---
void push_up(int p) {
    int ls = p << 1, rs = p << 1 | 1;
    tree[p].max_val = max(tree[ls].max_val, tree[rs].max_val);
    tree[p].min_val = min(tree[ls].min_val, tree[rs].min_val);

    if (tree[ls].max_val == tree[rs].max_val) {
        tree[p].count_max = tree[ls].count_max + tree[rs].count_max;
    } else if (tree[ls].max_val > tree[rs].max_val) {
        tree[p].count_max = tree[ls].count_max;
    } else {
        tree[p].count_max = tree[rs].count_max;
    }
}

// --- 物理装载：将懒标记实质化 ---
void apply_tag(int p, int l, int r, int val) {
    tree[p].max_val = val;
    tree[p].min_val = val;
    tree[p].count_max = r - l + 1; // 既然全部变成了 val，那 count 就是整个区间的长度！
    tree[p].lazy = val;
}

// --- 向下释能：传递懒标记 ---
void push_down(int p, int l, int r) {
    if (tree[p].lazy != -1) {
        int mid = (l + r) >> 1;
        apply_tag(p << 1, l, mid, tree[p].lazy);
        apply_tag(p << 1 | 1, mid + 1, r, tree[p].lazy);
        tree[p].lazy = -1; // 释放完毕，弹药清零
    }
}

// --- 建树：初始化绝对零度 ---
void build(int p, int l, int r) {
    tree[p].lazy = -1; // -1 代表没有标记
    if (l == r) {
        tree[p].max_val = -INF; // 初始状态：没有任何车，最远到达范围为负无穷
        tree[p].min_val = -INF;
        tree[p].count_max = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

// --- 核心引擎：Segment Tree Beats 的绝对剪枝法则 ---
// 目标：将 [ql, qr] 范围内，所有原本 >= threshold 的值，强行覆盖为 val
void update(int p, int l, int r, int ql, int qr, int threshold, int val) {
    // 物理越界，直接返回
    if (l > qr || r < ql) return;

    // 💥 绝对剪枝法则一：免疫区
    // 如果这片区域里连最大的数值都达不到要求（够不到施肥车），那全部都不可能达到！
    // 节省极其庞大的算力，直接回城！
    if (tree[p].max_val < threshold) return;

    // 💥 绝对剪枝法则二：全员沦陷区
    // 如果这片区域完全在目标范围内，且连最小的数值都达到了要求（全部都能搭上车）！
    // 那么这片区域里的所有元素，统统给我变成 val！打上 Lazy Tag，直接回城！
    if (ql <= l && r <= qr && tree[p].min_val >= threshold) {
        apply_tag(p, l, r, val);
        return;
    }

    // 💥 绝对剪枝法则三：量子叠加态 (分裂)
    // 既不是全军覆没，也不是全员达标。只能将区间撕裂，往下层钻探！
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    update(p << 1, l, mid, ql, qr, threshold, val);
    update(p << 1 | 1, mid + 1, r, ql, qr, threshold, val);
    push_up(p);
}

// (注：后续的 main 函数逻辑就是扫描线遍历，将施肥车按 R 排序。
// 对于每一辆车 [l_i, R]：
// 1. 点火起点：update(1, 1, n, l_i, l_i, -INF, R)
// 2. 连锁延伸：update(1, 1, n, 1, l_i, l_i, R)
// 3. 统计答案：如果 tree[1].max_val == R，说明有方案成功，ans += tree[1].count_max)