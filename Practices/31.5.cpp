#include<iostream>
#include<queue>
#include<map>
#include<vector>
#define INF 0x3f3f3f3f
using namespace std;
int m,n;
struct node{
    int pos;
    int w;//收益
    int b;//损失
};
struct path{
     int max1;
     int max2;
     int all;
};
vector<node>adj[100005];
bool visited[100005]={false};
int fa[100005];
path dp[100005];
pair<int,int>xx[100005];
path query(int a){
    path t;
    t.max1=0;
    t.max2=0;    
    t.all=0;
    if(adj[a].size()<=1&&fa[a]!=a){
        return t;
    }
    for(auto cd:adj[a]){
        if(cd.pos==fa[a])continue;
        path t1=query(cd.pos);
        t.all=max(t.all,t1.all);
        if(t1.max1+cd.b-cd.w>t.max1){
           t.max2=t.max1;
           t.max1=t1.max1+cd.b-cd.w;
        }else if(t1.max1+cd.b-cd.w>t.max2){
            t.max2=t1.max1+cd.b-cd.w;
        }
        
    } 
    t.all=max(t.all,t.max1+t.max2);
    dp[a]=t;
    return t;   
}
void update(int x,int y){
    int as=xx[x].first;
    if(fa[as]!=xx[x].second){
        as=xx[x].second;
    }
    for(auto &cd:adj[fa[as]]){
        if(cd.pos==as){
            cd.w=y;
        }
    }
    queue<int >q;
    q.push(as);
    while(!q.empty()){
        int a1=q.front();
        q.pop();
        int b1=fa[a1];
        dp[b1].all=0;
        dp[b1].max1=0;
        dp[b1].max2=0;
        for(auto &cd:adj[b1]){
        if(cd.pos==fa[b1])continue;
        dp[b1].all=max(dp[b1].all,dp[cd.pos].all);
        if(dp[cd.pos].max1+cd.b-cd.w>dp[b1].max1){
           dp[b1].max2=dp[b1].max1;
           dp[b1].max1=dp[cd.pos].max1+cd.b-cd.w;
        }else if(dp[cd.pos].max1+cd.b-cd.w>dp[b1].max2){
            dp[b1].max2=dp[cd.pos].max1+cd.b-cd.w;
        }
                
        }
        dp[b1].all=max(dp[b1].all,dp[b1].max1+dp[b1].max2);
        if(fa[b1]!=b1)q.push(b1);
    }
return ;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n-1;i++){
        int u,v,w,b;
        cin>>u>>v>>w>>b;
        adj[u].push_back({v,w,b});
        adj[v].push_back({u,w,b});
        xx[i]={u,v};
    }
    //dfs寻找路径
    visited[1]=true;
    queue<int>q;
    q.push(1);
    fa[1]=1;
    while(!q.empty()){
        int a=q.front();
        q.pop();
        for(auto cd:adj[a]){
            if(!visited[cd.pos]){
                visited[cd.pos]=true;
                fa[cd.pos]=a;
                q.push(cd.pos);
            }
        }
    }
    query(1);
    cout<<dp[1].all<<endl;
    int x,y;
    for(int j=0;j<m;j++){
        cin>>x>>y;
        update(x,y);
        cout<<dp[1].all<<endl;     
    }
    return 0; 
}