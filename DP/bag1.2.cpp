#include<iostream>
#include<vector>
using namespace std;
int main(){
        ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
        vector<int> w(n + 1, 0);
    vector<int> v(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> w[i] >> v[i];
    }
    vector<int>dp(m+1,0);
    for(int i=1;i<=n;i++){
        for(int j=w[i];j<=m;j++){
            dp[j]=max(d[j],d[j-w[i]]+v[i]);
        }
    }
    cout<<dp[m]<<endl;
}