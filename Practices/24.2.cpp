#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
vector<int>a(100005);
int r;
int time(double x,double y){
    int sum=0;
    int down=ceil(x/r);
   int l=r*down;
   sum+=(l-x)*(down-1);
   int up=floor(y/r);
   int r1=up*r;
   sum+=(y-r1)*up;
   sum+=r*(down+up-1)*(up-down)/2;
   return sum;
}
int main(){
    int n,N;
    cin>>n>>N;
    for(int i=1;i<=n;i++){
      cin>>a[i];
    }
     r=floor(N/(n+1));
    long long sum=0;
    for(int i=0;i<=n;i++){
       int mid=r*i;
       if(mid>a[i]){
         sum-=time(a[i],min(a[i+1],mid));
         sum+=i*(min(mid,a[i+1])-a[i]);
       }
       if(mid<a[i+1]){
     sum+=time(max(mid,a[i]),a[i+1]);
     sum-=(a[i+1]-max(mid,a[i]))*i;
       }
    
    }
    cout<<sum<<endl;
    return 0;
}