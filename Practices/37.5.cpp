#include<iostream>
#include<vector>
#include<queue>
#define INF 0x3f3f3f3f
#define ll long long
using namespace std;
int n,m;
vector<ll>a(100005);
vector<int>adj[100005];
vector<int>fa(100005);
vector<ll>dp(100005,0);//一定过点i
vector<ll>dps(100005,0);//在i子树域一定不过i
vector<bool>which(100005,false);//看dps是否依赖dp
void dfs(int i){
  int pos=i;
  dp[i]=a[i];
  dps[i]=-INF;
  ll maxt=-INF;
  for(int t:adj[pos]){
    if(t==fa[pos])continue;
    dfs(t);
    dp[i]+=max(dp[i],0);
    maxt=max(maxt,dps[t]);
    maxt=max(max,dp[t]);
  }
  dps[i]=max(maxt,dps[i]);
  return ;
}
void update(int t,int val){
    ll pre=dp[t];
    ll cur;
    dp[t]+=val-a[t];
    a[t]=val;
    int x=t;
    while(fa[x]!=x){
      if(dp[x]>0&&pre>0){
        cur=dp[fa[x]];
        dp[fa[x]]+=dp[x]-pre;
        pre=cur;
      }
      if(dp[x]>0&&pre<=0){
        cur=dp[fa[x]];
        dp[fa[x]]+=dp[x];
        pre=cur;
      }
      dps[fa[x]]=-INF;
      ll maxt=-INF;
      for(int i:adj[fa[x]]){
         maxt=max(maxt,dp[i]);
         maxt=max(maxt,dps[i]);
      }
      dps[fa[x]]=maxt;
      x=fa[x];
    }
}
void change(int sa,int sb);
int main(){
     ios::sync_with_stdio(false);
     cin.tie(0);
     cin>>n>>m;
     for(int i=1;i<=n;i++){
        cin>>a[i];
     }
     int u,v;
     for(int i=1;i<n;i++){
          cin>>u>>v;
          adj[u].push_back(v);
          adj[v].push_back(u);
     }
     queue<int>q;
     q.push(1);
     while(!q.empty()){
        int pos=q.front();
        q.pop();
        for(int i:adj[pos]){
            if(fa[pos]==i)continue;
            fa[i]=pos;
            q.push(i);
        }
     }
     fa[1]=1;
     dfs(1);
     int f,a,b,c,d;
     int point=1;
     for(int i=0;i<m;i++){
         cin>>f;
         if(f==1){
         cin>>a;
         cout<<dps[a];
         }
         if(f==2){
         cin>>a>>b;
         update(a,b);
         cout<<max(dp[point],dps[point])<<endl;
         }
         if(f==3){
        cin>>a;
        change(point,a);
        point=a;
        cout<<dp[a]<<endl;
         }
         if(f=4){
        cin>>a>>b>>c>>d;
        int fat=b,son=a,fat1=c;
        if(fa[b]==a){
          fa[b]=-1;
          swap(fat,son);
        }else{
          fa[a]=-1;
        }
        for(size_t t=0;t<adj[a].size();t++){
          if(adj[a][t]==b)adj[a].erase(adj[a].begin()+t);
        }
        for(size_t t=0;t<adj[b].size();t++){
          if(adj[b][t]==a)adj[b].erase(adj[b].begin()+t);
        }
        adj[c].push_back(d);
        adj[d].push_back(c);
        if(fa[c]==-1){fa[c]=d;
        fat1=d;
        }
        if(fa[d]==-1)fa[d]=c;
        if(adj[fat].size()==1&&fa[fat]!=fat){dp[fat]=a[fat];
        dps[fat]==-1;}
      else{
        for(int i:adj[fat]){
          if(fa[fat]==i)continue;
          update(i,a[i]);
          break;
        }//这里可能需要额外讨论根节点情况
        }
        dp[son]-=a[son];
        ll val=a[son];
        a[son]=0;
        update(son,val);
        cout<<max(dps[point],dp[point])<<endl;
        
         }
     }
     return 0;
}