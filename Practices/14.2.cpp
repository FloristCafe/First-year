#include<iostream>
#include<vector>

using namespace std;
int main(){
    int n;
    cin>>n;
    vector<vector<pair<int,int>>>a(2,vector<pair<int,int>>(n));
    for(int i=0;i<n;i++){
        int l,r;
        cin>>l>>r;
        a[0][i]={l,r};
    }
    
    for(int i=0;i<n;i++){
        int l,r;
        cin>>l>>r;
        a[1][i]={l,r};
    }
    int sum=0;
    int now=0;
    int pos[2]={0};
    
    while(1){
      int l1,l2,r1,r2;
      l1=a[now][pos[now]].first;
      r1=a[now][pos[now]].second;
      l2=a[now^1][pos[now^1]].first;
      r2=a[now^1][pos[now^1]].second;
      if(l2<l1){
        now=now^1;
      l1=a[now][pos[now]].first;
      r1=a[now][pos[now]].second;
      l2=a[now^1][pos[now^1]].first;
      r2=a[now^1][pos[now^1]].second;
      }
      if(r1<=l2){
        pos[now]++;
        if(pos[now]>=n)break;
        continue;
      }
     
      if(r2>r1){
       sum+=r1-l2;
       pos[now]++;
       now=now^1;
       if(pos[now^1]>=n)break;
     } else{
       sum+=r2-l2;
       pos[now^1]++;
       if(pos[now^1]>=n)break;
     }
    }
    cout<<sum<<endl;
    return 0;
}