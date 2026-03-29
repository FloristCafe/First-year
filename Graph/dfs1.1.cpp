#include<iostream>
#include<vector>
using namespace std;
vector<int>sides[1000010];
bool visited[1000010]={false};
void side(int n,int m){
     sides[n].push_back(m);
     sides[m].push_back(n);
}
int dfs(int n){
    visited[n]=true;
     for(int i=0;i<sides[n].size();i++){
        int k=sides[n][i];
        if(k==0)continue;
        if(!visited[k]){
            visited[k]=true;
            dfs(k);
        }
     }
     return 0;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    int count=0;
    int a,b;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
    cin>>a>>b;
    side(a,b);
    }
    for(int i=1;i<=n;i++){
        if(!visited[i]){
            dfs(i);
            count++;}

    }
    cout<<count<<endl;
    return 0;
}
