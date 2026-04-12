#include<iostream>
#include<vector>
#define ll long long
using namespace std;
vector<int>a(10005);
vector<ll>dp(10005,0);
int main(){
    int n,m;
    cin>>n>>m;
    a[0]=0;
      for(int i=1;i<=m;i++){
        cin>>a[i];
      }
      for(int i=1;i<=m;i++){
        for(int j=i;j<=n;j++){
            dp[j]=max(dp[j],dp[j-i]+a[i]);
        }
      }
      cout<<dp[n]<<endl;
      return 0;
}