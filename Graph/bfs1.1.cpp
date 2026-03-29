#include<iostream>
#include<vector>
#include<set>
using namespace std;
vector<int>sides[1000010];
bool visited[1000010]={false};
void side(int n,int m){
     sides[n].push_back(m);
     sides[m].push_back(n);
}
vector<int>line[1000010];

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
    //bfs
    int k=1;
    int decide=0;

    line[0].push_back(1);
    visited[1]=true;
    while(1){
        int gd=line[count].size();
        int chess=0;
     for(int i=0;i<gd;i++){
        int c=line[count][i];
        int pc=0;
         for(int p=0;p<sides[c].size();p++){
            if(!visited[sides[c][p]]){
                visited[sides[c][p]]=true;
             line[count+1].push_back(sides[c][p]);
             pc++;
            }
            if(sides[c][p]==n){
                decide=1;
            }
         }
         if(pc==0)chess++;
     }
     if(chess==gd){
        count=-1;
        break;
     }
     count++;
if(decide){
    break;
}
    }
cout<<count<<endl;


    return 0;
}