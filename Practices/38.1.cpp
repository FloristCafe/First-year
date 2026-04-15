#include<iostream>
#include<vector>
using namespace std;
int main(){
    int k;
    cin>>k;
    double a,b,c;
    for(int i=0;i<k;i++){
         cin>>a>>b>>c;
         double z=(c-a)/b;
         z*=10;
         int num_01=1;
         while(z>=1){
            z-=1;
            num_01+=1;
         }
         z*=10;
         int num_02=1;
         while(z>=1){
            z-=1;
            num_02+=1;
         }
         cout<<num_01<<" "<<num_02<<endl;
         
    }
    return 0;
}