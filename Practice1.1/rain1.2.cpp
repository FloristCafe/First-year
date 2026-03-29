#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct cell{
    int h;
    int x;
    int y;

    bool operator<(const cell &other)const{
        return h>other.h;//h越小越优先
    }
};
class Solution{
    public:
    int traprain(vector<vector<int>>&heightmap){
        int n =heightmap.size();
        if(n==0)return 0;
        int m=heightmap[0].size();
        if(m==0)return 0;
        priority_queue<cell>pq;
        vector<vector<bool>>visited(n,vector<bool>(m,false));
        
        for(int j=0;j<=n-1;j++){
            pq.push({heightmap[j][0],j,0});
            visited[j][0]=true;
            pq.push({heightmap[j][m-1],j,m-1});
            visited[j][m-1]=true;      
        }
        for(int j=1;j<m-1;j++){
            visited[0][j]=true;
            visited[n-1][j]=true;
            pq.push({heightmap[0][j],0,j});
            pq.push({heightmap[n-1][j],n-1,j});
        }
        int sum=0;
        int dx[4]={1,-1,0,0};
        int dy[4]={0,0,-1,1};
        while(!pq.empty()){
            int h1=pq.top().h;
            int x1=pq.top().x;
            int y1=pq.top().y;
            pq.pop();
         
            for(int i=0;i<4;i++){
                int xx=x1+dx[i];
                int yy=y1+dy[i];
                if(xx<0||xx>n-1)continue;
                if(yy<0||yy>m-1)continue;
                
                if(visited[xx][yy])continue;
                visited[xx][yy]=true;
                if(heightmap[xx][yy]<=h1)
                    sum+=h1-heightmap[xx][yy];


                    pq.push({max(h1,heightmap[xx][yy]),xx,yy});
            }
        }
        return sum;


    }
};