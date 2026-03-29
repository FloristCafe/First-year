#include<iostream>
#include<vector>
#define ll long long
using namespace std;
vector<ll>a(500010,0);
vector<ll>tree(500010,0);
    int n,m;
int lowbit(int x){
    int a=x&(-x);
    return a;
}
void add(int x,int k){
    while(x<=n){
        tree[x]+=k;
        x+=lowbit(x);
    }
}
long long query(int x) {
    long long sum = 0;
    while (x > 0) {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        add(i,a[i]);
    }
     int ac,sd,df;
    for(int i=1;i<=m;i++){
      cin>>ac>>sd>>df;
      if(ac==1){
add(sd,df);
      }else{
        cout<<query(df)-query(sd-1)<<endl;
      }
    }
    return 0;

}