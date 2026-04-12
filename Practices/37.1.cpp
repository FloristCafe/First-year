#include<iostream>
#include<vector>
using namespace std;
int main(){
    int b,c,l,r;
    cin>>b>>c>>l>>r;
    int x_l=(l+1)/2;
    x_l*=2;
    int x_r=r/2;
    x_r*=2;
    int len=(x_r-x_l)/2+1;
    int c1=(len-1)*len/2;
    int pri=(x_l*x_l+b*x_l+c)*len;
    pri+=4*c1*x_l+2*c1*b+(len-1)*len*(2*len-1)*2/3;
    cout<<pri*2<<endl;
    return 0;
}