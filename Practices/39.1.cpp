#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int main(){
    double n;
    double a;
    double pi;
    cin>>n>>a;
    double m=0;
    for(int i=0;i<n;i++){
        double x,y;
        cin>>x>>y;
        if(x*x+y*y<=a*a){
            m++;
        }
    }
    pi=4*m/n;
    cout<<pi<<endl;
    return 0;
}