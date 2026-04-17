#include<iostream>
#include<set>
#include<vector>
#include<map>
#include<iterator>
#include<algorithm>
using namespace std;
struct point{
    int l;
    int r;
    bool operator<(const point &other)const{
        return l<other.l;
    }
};
map<point,int>all;
set<point>wd[100005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m>>p;
    all[{1,n}]=0;
    int a;
    for(int i=0;i<q;i++){
        cin>>a;
        if(a==1){
       int l,r,x;
       cin>>l>>r>>x;
       map<point,int>cur_all=all;
       int L=0,R=0;
    for(auto it=cur_all.begin();it!=cur_all.end();it++){
        if(it->first.r<l)continue;
        if(it->first.l>r)continue;
        if(it->first.l<l&&it->first.r>=l){
            all[{it->first.l,l-1}]=it->second;
            wd[it->second].insert({it->first.l,l-1});
        }
        if(it->first.r>r&&it->first.l<=r){
           all[{r+1,it->first.r}]=it->second;
           wd[it->second].insert({it->first.l,l-1});
        }
        wd[it->second].erase({it->first.l,it->first.r});
        all.erase({it->first.l,it->first.r});
    
    }
    all[{l,r}]=x;
    wd[x].insert({l,r});
        }
        if(a==2){
int x,w;
cin>>x>>w;
if(w==0){
    wd[x].clear();
continue;
}
set<point>cur_set;
    set_union(
        wd[x].begin(), wd[x].end(),
        wd[w].begin(), wd[w].end(),
        inserter(cur_set, cur_set.begin())
    );
    wd[w]=cur_set;
    for(point ii:wd[x]){
        all[{ii.l,ii.r}]=w;
    }
    wd[x].clear();
        }
        if(a==3){
    
        }
        if(a==4){

        }
        if(a==5){

        }
    }
}