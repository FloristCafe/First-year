#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int x,y;
        string s;
        cin>>x>>y>>s;
        int sum_x=0,sum_y=0;
       for(char cd:s){
          if(cd=='f'){
            sum_y+=1;
            if(y+sum_y>n)sum_y-=1;
          }
                    
          if(cd=='b'){
            sum_y-=1;
            if(y+sum_y<1)sum_y+=1;            
          }          
          if(cd=='r'){
            sum_x+=1;
            if(x+sum_x>n)sum_x-=1;
        }          
          if(cd=='l'){
            sum_x-=1;
            if(x+sum_x<1)sum_x+=1;            
          }
       }
       cout<<x+sum_x<<" "<<y+sum_y<<endl;
    }
    return 0;
}