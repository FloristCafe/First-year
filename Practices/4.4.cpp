#include <iostream>
using namespace std;

typedef long long ll;

int n, q;
ll pp; // 必须是全局 long long

struct Node {
    ll sum;
    ll mul;
    ll add;
} tree[400005];

void pushup(int p) {
    tree[p].sum = (tree[p<<1].sum + tree[p<<1|1].sum) % pp;
}

// 💥 维度补全：必须传入 l 和 r，才能算出儿子的区间长度！
void pushdown(int p, int l, int r) {
    // 性能优化：如果没有标记，直接终止，拒绝浪费算力
    if (tree[p].mul == 1 && tree[p].add == 0) return;

    int mid = (l + r) >> 1;
    ll len_left = mid - l + 1;
    ll len_right = r - mid;

    // ---------------------------------------------------------
    // 💥 绝对法则一：先下放乘法标记！
    // ---------------------------------------------------------
    // 左儿子：真实能量放大、乘法标记放大、旧加法标记随之放大！
    tree[p<<1].sum = (tree[p<<1].sum * tree[p].mul) % pp;
    tree[p<<1].mul = (tree[p<<1].mul * tree[p].mul) % pp;
    tree[p<<1].add = (tree[p<<1].add * tree[p].mul) % pp; 

    // 右儿子同理
    tree[p<<1|1].sum = (tree[p<<1|1].sum * tree[p].mul) % pp;
    tree[p<<1|1].mul = (tree[p<<1|1].mul * tree[p].mul) % pp;
    tree[p<<1|1].add = (tree[p<<1|1].add * tree[p].mul) % pp;

    // ---------------------------------------------------------
    // 💥 绝对法则二：再下放加法标记！
    // ---------------------------------------------------------
    // 左儿子：真实能量增加 (加法标记 * 区间长度)！加法标记累加！
    tree[p<<1].sum = (tree[p<<1].sum + tree[p].add * len_left) % pp;
    tree[p<<1].add = (tree[p<<1].add + tree[p].add) % pp;

    // 右儿子同理
    tree[p<<1|1].sum = (tree[p<<1|1].sum + tree[p].add * len_right) % pp;
    tree[p<<1|1].add = (tree[p<<1|1].add + tree[p].add) % pp;

    // ---------------------------------------------------------
    // 💥 绝对法则三：父节点状态重置清零！
    // ---------------------------------------------------------
    tree[p].mul = 1;
    tree[p].add = 0;
}

// 查询引擎
ll query(int p, int l, int r, int L, int R) {
    // 完美包容，直接返回，绝对不需要 pushdown！
    if (l >= L && r <= R) {
        return tree[p].sum; // 💥 必须返回 sum，不能返回结构体！
    }

    // 💥 只有当区间被撕裂，必须向下探测时，才下放标记！
    pushdown(p, l, r); 

    ll ans = 0;
    int mid = (l + r) >> 1;
    if (mid >= L) ans = (ans + query(p<<1, l, mid, L, R)) % pp;
    if (mid < R)  ans = (ans + query(p<<1|1, mid + 1, r, L, R)) % pp;

    return ans;
}
void update_add(int p, int l, int r, int L, int R, ll val){
    if(l>=L&&R>=r){
        tree[p].add=(val+tree[p].add)%pp;
        tree[p].sum=(tree[p].sum+val*(r-l+1))%pp;
        return ;
    }
    pushdown(p,l,r);
    int mid=(l+r)/2;
    if(mid>=L){
update_add(p<<1,l,mid,L,R,val);
    }
    if(mid<R){
        update_add(p<<1|1,mid+1,r,L,R,val);
    }
    
    pushup(p);
    return ;
}