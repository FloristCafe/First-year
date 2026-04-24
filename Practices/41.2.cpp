#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<double>dp(1005,0);
struct node{
    int o;
    double b;
    double a;
    bool operator<(const node &other){
        return (b/a)>(other.b/other.a);
    }
};
int main(){
   int n,m;
   cin>>n>>m;
   
vector<node>tree(n);
double sum=0;
   for(int i=0;i<n;i++){
    int o;
    double t,a,b;
    cin>>o>>t>>a>>b;
    sum+=t;
   tree[i]={o,b,a};
   }
   sort(tree.begin(),tree.end());
   for(int i=0;i<n;i++){
   if(tree[i].o==0){
    for(int j=m;j>=1;j--){
        double q=tree[i].b/tree[i].a;
        for(int k=1;k<=tree[i].a;k++){
            if(j-k<0)break;
   dp[j]=max(dp[j],dp[j-k]+k*q);}
    }
   
   }else{
    for(int j=m;j>=tree[i].a;j--){
   dp[j]=max(dp[j],dp[j-tree[i].a]+tree[i].b);
    }
   }
   }
   cout<<sum-dp[m]<<endl;
   return 0;
}