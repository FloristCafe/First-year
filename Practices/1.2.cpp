#include<iostream>
#include<vector>
using namespace std;
int a[32][32];
int b[32][32];
int ts[32][32]={0};

int main(){
    int m,n;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>a[i][j];
            b[j][i]=a[i][j];
        }
    }
    for(int i=0;i<n;i++){
        int l=0,r=0;
        while(r<m){
            while(a[i][l]==a[i][r]&&r<m){
                r++;
            }
            if((r-l)>=3){
                for(int t=l;t<r;t++){
            ts[i][t]=1;
                }
            }
            l=r;
        }
    }
        for(int i=0;i<m;i++){
        int l=0,r=0;
        while(r<n){
            while(b[i][l]==b[i][r]&&r<n){
                r++;
            }
            if((r-l)>=3){
                for(int t=l;t<r;t++){
            ts[t][i]=1;
                }
            }
            l=r;
        }
    }
    for(int i=0;i<n;i++){
        int first=1;
        for(int j=0;j<m;j++){
            if(!first)cout<<" ";
            if(ts[i][j]==1){
                cout<<"0";
            }else{
                cout<<a[i][j];
            }
            first=0;
        }
        cout<<endl;
    }
}