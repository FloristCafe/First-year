#include<iostream>
#include<string>
#include<vector>
#define ll long long
using namespace std;
vector<ll>b(1005,0);
int main(){
    int n;
    cin>>n;
        ll sum1=0;
    for(int i=0;i<n; i++){
      cin>>b[i];
    sum1+=b[i];
    }

    ll sum2=0;
    int l=0,r=0;
    while(r<n){
        sum2+=b[l];
        while(b[l]==b[r]){
          r++;
        }
        l=r;
    }
    cout<<sum1<<endl;
    cout<<sum2<<endl;
    return 0;
}