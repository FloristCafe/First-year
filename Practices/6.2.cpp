#include<iostream>
#include<vector>

using namespace std;
int a[32][32];
int t[32][32];
int main(){
   int n,m;
   cin>>n>>m;
   for(int i=0;i<n;i++){
     for(int j=0;j<m;j++){
        cin>>a[i][j];
     }
   }
   for(int i=0;i<n;i++){
    int l=0,r=0;
    while(r<m){
        while(a[i][r]==a[i][l]&&r<m){
            r++;
        }
        if(r-l>=3){
    for(int j=l;j<r;j++){
        t[i][j]=1;
    }
        }
        l=r;
    }

    }
   for(int i=0;i<m;i++){
    int l=0,r=0;
    while(r<n){
        while(a[r][i]==a[l][i]&&r<m){
            r++;
        }
        if(r-l>=3){
    for(int j=l;j<r;j++){
        t[j][i]=1;
    }
        }
        l=r;
    }

    }
    for(int i=0;i<n;i++){
        int first=1;
        for(int j=0;j<m;j++){
            if(!first)cout<<" ";
            if(t[i][j]){
                cout<<"0";
            }else{
                cout<<a[i][j];
            }
            first=0;
        }
        cout<<endl;
    }
    return 0;
    
    }
   
