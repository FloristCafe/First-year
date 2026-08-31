#include<iostream>
#include<vector>

using namespace std;
int main(){
    int b,c,l,r;
    cin>>b>>c>>l>>r;
    int sum=0;
    int l1=(l+1)/2-1;
    int r1=(r-1)/2;
    sum+=r1*(r1+1)*(2*r1+1)/6+(l1+1)*l1*(2*l1+1);
    sum*=4;
    sum+=(r1-l1)*(r1+l1+1)*b;
    sum+=c*(r1-l1);
    sum*=2;
    cout<<sum<<endl;
    return 0;
}
