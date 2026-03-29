#include<iostream>
#include<vector>
using namespace std;
int main(){
    int dp[1000][1000];
    string a,b;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(a[i]==b[j]){
    if(i==0||j==0)
    {dp[i][j]=1;}
    else{
                dp[i][j]=dp[i-1][j-1]+1;}//注意到只与i-1有关
                //考虑curr,prev前后对照的唯二变量，节省内存
            }else{
                if(i==0||j==0)
                {dp[i][j]=1;}
                else{
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);}
            }
        }
    }
    cout<<dp[n-1][n-1]<<endl;
    return 0;
}