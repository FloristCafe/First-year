#include<iostream>
#include<vector>
#define ll long long
using namespace std;
void pushdown(int p, int l, int r) {
    if (lazy[p] == 0) return; // 没欠条，直接关机撤退

    int mid = l + (r - l) / 2;

    // 1. 儿子的能量暴增（绝对是更新儿子的 tree！乘上各自的领土大小）
    tree[p << 1] += lazy[p] * (mid - l + 1);
    tree[p << 1 | 1] += lazy[p] * (r - mid);

    // 2. 欠条的代际传承（叠加给儿子）
    lazy[p << 1] += lazy[p];
    lazy[p << 1 | 1] += lazy[p];

    // 3. 父亲债务清零
    lazy[p] = 0;
    
    // 绝对纪律：到此为止，绝不递归！
}
void pushup(int x){
    tree[x]=tree[x<<1]+tree[x<<1|1];
}
void update(int p,int l,int r,int L,int R,ll v){
    if(r<=R&&L<=l){
        tree[p]+=v*(r-l+1);
        lazy[p]+=v;
        return ;
    }
    int mid=(r+l)/2;
    pushdown(p,l,r);//欠条有需要再分发，不需要就节省算力
    if(L<=mid){
       update(p<<1,l,mid,L,R,v);
    }
    if(R>mid)update(p<<1|1,mid+1,r,L,R,v);
pushup(p);
}
ll query(int p, int l, int r, int L, int R) {
    // 1. 绝对包裹律：当前领土 [l, r] 被目标区间 [L, R] 完全吞噬
    // 领土被吞噬，直接上交能量，立刻撤退！
    if (L <= l && r <= R) {
        return tree[p]; 
    }

    int mid = l + (r - l) / 2;
    ll cur = 0;

    // 💥 懒标记唯一的介入点：时空撕裂前的清算！
    // 既然不能直接返回，必须往下劈开，那就必须先把欠条发下去，保证下面拿到的是真数据。
    pushdown(p, l, r);

    // 2. 精准制导（只读操作，去左右半球收集战利品）
    if (L <= mid) {
        cur += query(p << 1, l, mid, L, R);
    }
    if (R > mid) {
        cur += query(p << 1 | 1, mid + 1, r, L, R);
    }

    // 3. 带着干净的能量返回
    return cur;
}