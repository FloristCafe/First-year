#include<iostream>
#include<vector>
#define INF 0x3f3f3f3f
using namespace std;
vector<int>a(202);
int main(){
    int n,N;
    cin>>n>>N;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    a[0]=0;
    a[n+1]=INF;
    long long sum=0;
    for(int i=1;i<=n+1;i++){
        if(a[i-1]>N)break;
        sum+=(i-1)*(min(a[i],N)-a[i-1]);
        cout<<sum<<endl;
    }
    cout<<sum<<endl;
    return 0;

}