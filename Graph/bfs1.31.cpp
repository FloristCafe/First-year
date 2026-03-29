#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int a[1010][1010];
int dis[1010][1010];
bool visited[1010][1010]={false};
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    queue<pair<int,int>>q;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int k=1;k<=m;k++){
            cin>>a[i][k];
            dis[i][k]=-1;
        }
    }
    q.push({1,1});
    dis[1][1]=0;
    visited[1][1]=true;
    while(!q.empty()){
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        
       for(int i=0;i<4;i++){
        int nx=x+dx[i];
        int ny=y+dy[i];
         if(nx<=0||ny<=0||nx>=n+1||ny>=m+1)continue;
         if(visited[nx][ny])continue;
         if(a[nx][ny])continue;

         dis[nx][ny]=dis[x][y]+1;
         visited[nx][ny]=true;
         q.push({nx,ny});
       }
    }

    cout<<dis[n][m];
    return 0;
}