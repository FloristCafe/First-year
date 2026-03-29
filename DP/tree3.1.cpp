#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100005;

// 齿轮一：物理内存开辟，绝对的 4 倍法则！
vector<int> a(MAXN, 0);           // 原生数组
vector<int> tree(MAXN * 4, 0);    // 线段树装甲

// 齿轮二：向上折叠引擎
// p 是当前节点的物理编号
void pushup(int p) {
    // 父亲的区间和 = 左儿子(p*2) + 右儿子(p*2+1)
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
}

// 齿轮三：递归建树引擎
// p: 当前节点编号; l: 当前管辖的左边界; r: 当前管辖的右边界
void build(int p, int l, int r) {
    // 基线条件：时空坍缩到绝对原子态（单点）
    if (l == r) {
        tree[p] = a[l]; // 注入原生数组的真实物理能量
        return;         // 绝对不能漏掉的回溯指令！
    }

    // 寻找物理中点，防止大数相加溢出
    int mid = l + (r - l) / 2;

    // 向左子树递归：编号变为 p*2，管辖区间缩小为 [l, mid]
    build(p << 1, l, mid);
    
    // 向右子树递归：编号变为 p*2+1，管辖区间缩小为 [mid+1, r]
    build(p << 1 | 1, mid + 1, r);

    // 绝对纪律：左右儿子的能量装填完毕，父亲必须立刻聚合！
    pushup(p);
}
void update(int p, int l, int r, int x, int v) {
    // 1. 绝对的刹车制动：抵达原子态
    if (l == r) {
        tree[p] += v; // 真实物理能量的注入
        return;       // 绝对不能漏掉的刹车！
    }

    int mid = l + (r - l) / 2; // 防溢出中点计算

    // 2. 基因制导
    if (x <= mid) {
        // 目标在左半球，向左深潜
        update(p << 1, l, mid, x, v);
    } else {
        // 目标在右半球，向右深潜。绝对是 mid + 1！
        update(p << 1 | 1, mid + 1, r, x, v);
    }

    // 3. 绝对纪律：回溯时的向上折叠！
    // 无论是求和、求最值，只需在 pushup 里改一行代码，这里的逻辑永远不用动！
    pushup(p); 
}
long long query(int p, int l, int r, int L, int R) {
    // 1. 绝对包裹律：当前领土被目标区间完全吞噬，直接上交能量，立刻刹车！
    if (L <= l && r <= R) {
        return tree[p]; 
    }

    int mid = l + (r - l) / 2;
    long long total_energy = 0; // 用于收集战利品，绝对不污染 tree[p]

    // 2. 时空撕裂：精准制导，绝不盲搜
    if (L <= mid) {
        // 目标区间探入了左半球，向左子树索要能量
        total_energy += query(p << 1, l, mid, L, R);
    }
    
    if (R > mid) {
        // 目标区间探入了右半球，向右子树索要能量
        total_energy += query(p << 1 | 1, mid + 1, r, L, R);
    }

    // 3. 带着收集到的总能量安全撤退
    return total_energy; 
}