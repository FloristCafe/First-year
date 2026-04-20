#include<iostream>
#include<vector>
#include<map>
 using namespace std;
 int main(){
int n,m,L;
cin>>n>>m>>L;
map<int,int>as;
for(int i=0;i<L;i++){
    as[i]=0;
}
for(int i=0;i<m*n;i++){
    int a;
    cin>>a;
    as[a]++;
}
int first=1;
for(int i=0;i<L;i++){
    if(!first)cout<<" ";
    cout<<as[i];
    first=0;
}
cout<<endl;
return 0;
 }