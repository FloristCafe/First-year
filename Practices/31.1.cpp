#include<iostream>
#include<vector>
using namespace std;
int sumx[1000]={0};
int sumy[1000]={0};
int main(){
    int n,m;
    cin>>n>>m;
    int dx,dy;
    for(int i=1;i<=n;i++){
        cin>>dx>>dy;
        sumx[i]=sumx[i-1]+dx;
        sumy[i]=sumy[i-1]+dy;
    }
    for(int i=0;i<m;i++){
        cin>>dx>>dy;
        cout<<dx+sumx[n]<<" "<<dy+sumy[n]<<endl;
    }
    return 0;
}