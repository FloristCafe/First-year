#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<map>
#define INF 0x3f3f3f3f
using namespace std;
struct node{
    int l;
    int r;
    int cur_pos;
};
struct inf{
   int x=0;
   int e=0;
};
set<pair<int,int>>dom;
map<int,inf>cap;
int main(){
   dom.insert({0,INF});
   int n,q;
   cin>>n>>q;
   vector<node>tree[n+1];
   for(int i=0;i<q;i++){
    string order;
    cin>>order;
    if(order=="new"){
        int p,L;
        cin>>p>>L;
        pair<int,int> pos;
        int min=INF;
  for(pair<int,int>ss:dom){
   if(ss.second==INF&&min==INF){
       pos=ss;
   }
     if(min+ss.first>ss.second&&ss.second-ss.first+1>=L){
      pos=ss;
        min=ss.second-ss.first+1;
     }
  }
  dom.erase({pos.first,pos.second});
  if(pos.first+L<=pos.second)dom.insert({pos.first+L,pos.second});
  tree[p].push_back({pos.first,pos.first+L-1,0});
  cout<<pos.first<<endl;

    }
    if(order=="send"){
      int sum=0;
    int p;
    cin>>p;
    for(node&ss:tree[p]){
       int pos1=ss.l+ss.cur_pos;
       if(pos1>ss.r){
         ss.cur_pos=1;
         pos1=ss.l;
         cap[pos1].x=1;
       }else{
         ss.cur_pos++;
       }
       sum+=pos1;
    }
    cout<<sum<<endl;
    }
    if(order=="delete"){
   int p,ii;
   cin>>p>>ii;
   node pos1=tree[p][ii-1];
   tree[p].erase(tree[p].begin()+ii-1);
   int l1=pos1.l;
   int r1=pos1.r;
   dom.insert({l1,r1});
   auto pos2=dom.find({l1,r1});
   pos2++;
   int l2=pos2->first;
   int r2=pos2->second;
   if(l2==r1){
      dom.erase({l1,r1});
      dom.erase({l1,r1});
      dom.insert({l1,r2});
   }
    }
   }
   return 0;
}
