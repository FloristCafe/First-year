<<<<<<< HEAD
#include<iostream>
#include<vector>

using namespace std;
int main(){
    int n,k,t,x_l,y_d,x_r,y_u;
    int count_1=0,count_2=0;
    cin>>n>>k>>t>>x_l>>y_d>>x_r>>y_u;
    for(int i=0;i<n;i++){
        int real=0;
        int decide=0;
        int cou=0;
    for(int j=0;j<t;j++){
      int x,y;
      cin>>x>>y;
      if(x<=x_r&&x>=x_l&&y<=y_u&&y>=y_d){
        real=1;
        cou++;
      }else{
         cou=0;
      }
      if(cou==k)decide=1;
    }
    if(real==1)count_1++;
    if(decide==1)count_2++;

    }
    cout<<count_1<<endl<<count_2<<endl;
    return 0;
=======
#include<iostream>
#include<vector>

using namespace std;
int main(){
    int n,k,t,x_l,y_d,x_r,y_u;
    int count_1=0,count_2=0;
    cin>>n>>k>>t>>x_l>>y_d>>x_r>>y_u;
    for(int i=0;i<n;i++){
        int real=0;
        int decide=0;
        int cou=0;
    for(int j=0;j<t;j++){
      int x,y;
      cin>>x>>y;
      if(x<=x_r&&x>=x_l&&y<=y_u&&y>=y_d){
        real=1;
        cou++;
      }else{
         cou=0;
      }
      if(cou==k)decide=1;
    }
    if(real==1)count_1++;
    if(decide==1)count_2++;

    }
    cout<<count_1<<endl<<count_2<<endl;
    return 0;
>>>>>>> e3718e7119451d180d0fc9eee75a2b96fa2e0eb4
}