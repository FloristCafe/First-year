#include<iostream>
#include<vector>
#define ll long long
using namespace std;
vector<int >a(100005);
vector<ll>tree(100005);
void build(int p,int l,int r){
    if(l==r){
        tree[p]=a[l];
        return ;
    }
    int mid=(l+r)/2;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    pushup(p);
}
void pushup(int p){
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
}
void update(int p, int l, int r, int x, int v){
    if(l==r){
        tree[p]+=v;
        return ;
    }
    
    int mid=(l+r)/2;
    if(x<=mid){
        update(p<<1,l,mid,x,v);
    }else{
        update(p<<1|1,mid+1,r,x,v);
    }
pushup(p);

}
ll query(int p,int l,int r,int L,int R){
    if(l>=L&&r<=R){
        return tree[p];
    }
    int mid=(l+r)/2;
    ll cur=0;
    if(mid>=L){
      cur+=query(p<<1,l,mid,L,R);
    }
    if(mid<R){
        cur+=query(p<<1|1,mid+1,r,L,R);
    }
    return cur;
}