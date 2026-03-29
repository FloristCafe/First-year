#include<iostream>
#include<vector>
#include<queue>
const int INF = 0x3f3f3f3f;
using namespace std;
struct node{
    int d;
    int u;
    int k;
    bool operator<(const node &other)const{
        return d>other.d;//d越小越优先
    } 
};
priority_queue<node>pq;
vector<pair<int ,int>>graph[10005];
int dis[10005][15];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,k;
    cin>>n>>m>>k;
for(int i=0;i<=n;i++){
    for(int sd=0;sd<=k;sd++){
        dis[i][sd]=INF;
    }
}
    int s,t;
    cin>>s>>t;

        dis[s][0]=0;//由于不耗票数的飞行也需要dis做大小参照，只对最初始情况赋0
    

    int a,b,c;
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        graph[a].push_back({b,c});
        graph[b].push_back({a,c});
    }
    pq.push({0,s,0});
    while(!pq.empty()){
        int D=pq.top().d;
        int U=pq.top().u;
        int K=pq.top().k;
        pq.pop();

        if(D>dis[U][K])continue;
        for(int i=0;i<graph[U].size();i++){
          int pos=graph[U][i].first;
          int wen=graph[U][i].second;
          if(dis[pos][K]>D+wen){
dis[pos][K]=D+wen;//找近路花钱走
pq.push({dis[pos][K],pos,K});

          }
            if(K<k&&dis[pos][K+1]>D){
            pq.push({D,pos,K+1});//享用特权
            dis[pos][K+1]=D;
          }
        }
    }
int min=INF;
for(int i=0;i<=k;i++){
    if(dis[t][i]<min){
        min=dis[t][i];
    }
}
    cout<<min<<endl;
    return 0;
    


}
