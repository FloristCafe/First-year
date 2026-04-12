#include<iostream>
#include<vector>
#include<queue>
#define INF 0x3f3f3f3f
using namespace std;
vector<int>a(100005);
vector<int>k(100005);
vector<int>dp(100005,INF);
bool chec[100005]={false};
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
      cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>k[i];
    }
   dp[1]=0;
   queue<pair<int,int>>q;
   q.push({1,0});
   while(!q.empty()){
    int pos=q.front().first;
    int dis=q.front().second;
    q.pop();
    if(dp[pos]<dis)continue;
    for(int i=pos+1;i<=min(pos+k[pos],n);i++){
          if(dp[i-a[i]]>dis+1){
            dp[i-a[i]]=dis+1;
          q.push({i-a[i],dis+1});
          chec[i-a[i]]=true;
          }
    }
   }
   if(chec[n]){
    cout<<dp[n]<<endl;
    return 0;
   }
   cout<<"-1"<<endl;
   return 0;

}