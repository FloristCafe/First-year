#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int dx[8]={1,2,2,1,-1,-2,-2,-1};
int dy[8]={2,1,-1,-2,-2,-1,1,2};
vector<vector<bool>>a(102,vector<bool>(102,false));
vector<vector<int>>b(102,vector<int>(102,0));
int main(){
    int n,k,x,y;
    cin>>n>>k;
    cin>>x>>y;
    queue<pair<int,int>>q;
    q.push({x,y});
    int count =1;
    a[x][y]=true;
    while(!q.empty()){
        int x1=q.front().first;
        int y1=q.front().second;
        q.pop();
        if(b[x1][y1]==k)continue;
        for(int i=0;i<8;i++){
            if(x1+dx[i]<1||x1+dx[i]>n||y1+dy[i]>n||y1+dy[i]<1)continue;
            if(a[x1+dx[i]][y1+dy[i]])continue;
            a[x1+dx[i]][y1+dy[i]]=true;
            b[x1+dx[i]][y1+dy[i]]=b[x1][y1]+1;
            count++;
            q.push({x1+dx[i],y1+dy[i]});
        }
    }
    cout<<count<<endl;
    return 0;
}