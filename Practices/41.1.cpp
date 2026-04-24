#include<iostream>
#include<vector>

using namespace std;
int chec(int n){
    int l=0;
    int r=0;
   int n1=n;
    while(n1>0){
        if(n1%2==0)l++;
        if(n1%2==1)r++;
        n1/=2;
    }
    if(l==r)return 1;
    return 0;
}
int main(){
   int n;
   cin>>n;
   int cur=0;
   for(int i=0;i<n;i++){
    int a;
    cin>>a;
    if(chec(a))cur++;
   }
   cout<<cur<<endl;
   return 0;
}