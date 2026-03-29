#include<iostream>
#include<vector>
using namespace std;
#define N 100000
#define ll long long
vector<int>v(100005);
vector<int>e(100005);
vector<ll>tree(100005*4);//管辖区间的最大值
void pushup(int p){
    tree[p]=max(tree[p<<1],tree[p<<1|1]);
}
void update(int p,int l,int r,int x,ll val){
     if(l==r){
        tree[p]=max(tree[p],val);
        return ;
     }
     int mid=(l+r)/2;
     if(x<=mid){
        update(p<<1,l,mid,x,val);
     }else{
        update(p<<1|1,mid+1,r,x,val);
     }
     pushup(p);

}//单点更新，无欠条
ll query(int p,int l,int r,int L,int R){
      if(R>=r){
    return tree[p];
      }
      int mid=(l+r)/2;
      ll maxl=0,maxr=0;
      if(mid<R)maxr=query(p<<1|1,mid+1,r,L,R);
      maxl=query(p<<1,l,mid,L,R);
      return max(maxl,maxr);
      
}

ll getMaxWeightSubsequence(void) {
    ll global_max = 0; // 全局最大战利品收集器
    int MAXV = 100000; // 绝对的物理体积上限（由题目数据范围决定）

    for (int i = 1; i <= N; i++) {
        ll max_prev_energy = 0;
        
        // 1. 防爆拦截：只有体积大于 1，才有资格向前查询！
        if (v[i] > 1) {
            max_prev_energy = query(1, 1, MAXV, 1, v[i] - 1);
        }
        
        // 2. 状态转移：历史最大能量 + 自身能量
        dp[i] = max_prev_energy + e[i];
        
        // 3. 顺手记录全局最大值，拒绝多余操作
        global_max = max(global_max, dp[i]);
        
        // 4. 能量注入：把当前的最大战利品刻入线段树的体积丰碑（注意边界是 MAXV）
        update(1, 1, MAXV, v[i], dp[i]);
    }
    
    return global_max;
}