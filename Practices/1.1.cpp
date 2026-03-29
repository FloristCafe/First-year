#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int>a(1005);
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a.begin(),a.begin()+n);
    int count=0;
    int l1=0;
    int r1=0;
    int l2=0;
    int r2=0;
    while(a[l1]==a[r1]){
        r1++;
    }

while(r2<n){
        l2=r1; 
        r2=l2;
    while(a[l2]==a[r2]&&r2<n){
        r2++;
    }
    if(a[l2]-a[l1]==1){
        count+=(r1-l1)*(r2-l2);
    }
    l1=l2;
    r1=r2;
}
cout<<count<<endl;
return 0;
}