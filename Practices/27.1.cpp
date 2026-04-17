#include<iostream>
#include<vector>
#define ll long long
using namespace std;
vector<ll>c(23,1);
vector<ll>b(23,0);
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
       ll a;
       cin>>a;
       c[i]=c[i-1]*a;
    }
    for(int i=n;i>0;i--){
        b[i]=m/c[i-1];
        m%=c[i-1];
    }
    int first=1;
    for(int i=1;i<=n;i++){
       if(!first)cout<<" ";
       cout<<b[i]; 
       first=0;
    }
    cout<<endl;
    return 0;
}