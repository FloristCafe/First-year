#include<iostream>
#include<vector>

using namespace std;
vector<int>a(10001);
vector<int>res(10001);
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n; i++){
   cin>>a[i];
    }

    for(int i=1;i<n-1;i++){
        res[i]=(a[i-1]+a[i]+a[i+1])/3;
        
    }
    res[0]=(a[1]+a[0])/2;
    res[n-1]=(a[n-1]+a[n-2])/2;
    int first=1;
    for(int i=0;i<n;i++){
        if(!first)cout<<" ";
        cout<<a[i];
        first=0;
    }
    cout<<endl;
    return 0;

}