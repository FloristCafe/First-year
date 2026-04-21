#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct node{
    int y;
    int res;
    bool operator<(const node & other){
        return y<other.y; 
    };
};
int main(){
    int m;
    cin>>m;
    vector<node> tree(m);
    int l=m-1;
    int pos1=m-1;
    int cur_max=0;
    int cur_l=0,cur_r=0;
    for(int i=0;i<m;i++){
        int y,res;
        cin>>y>>res;

        tree[i]={y,res};
        if(y==0){
        cur_l++;
        }
    }
    sort(tree.begin(),tree.end());
    while(l>=0){
        if(tree[l].res==0){
        cur_l--;
        }else{
       cur_r++;
        }
        if(l==0){
        if(cur_l+cur_r>cur_max){
            cur_max=cur_l+cur_r;
            pos1=l;
                
        }
        break;
        }
        if(tree[l-1].y!=tree[l].y){
       if(cur_l+cur_r>cur_max){
            cur_max=cur_l+cur_r;
            pos1=l;
        }
        }
        l--;
    }
    cout<<tree[pos1].y<<endl;
    return 0;
}