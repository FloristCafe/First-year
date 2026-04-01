#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n,a,b;
    cin>>n>>a>>b;
    int sum=0;
    int x1,x2,y1,y2;
    for(int i=0;i<n;i++){
      cin>>x1>>y1>>x2>>y2;
      if(x1>=a||y1>=b||y2<=0||x2<=0)continue;
       sum+=(min(a,x2)-max(x1,0))*(min(b,y2)-max(y1,0));
    }
    cout<<sum<<endl;
    return 0;
}