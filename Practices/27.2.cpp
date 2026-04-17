#include<iostream>
#include<vector>

using namespace std;
vector<int>a(300,0);
vector<int>dp(30005,0);
int main(){
    int n,x;
    cin>>n>>x;
    int sum=0;
    for(int i=1;i<=n;i++){
       cin>>a[i];
       sum+=a[i];
    }
    int cap=sum-x;
    for(int i=1;i<=n;i++){
        for(int j=cap;j>=a[i];j--){
         
            dp[j]=max(dp[j-a[i]]+a[i],dp[j]);
        }
    }
    cout<<sum-dp[cap]<<endl;
    return 0;
}