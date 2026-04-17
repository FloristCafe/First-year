#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<double>a(n);
    double sum=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        sum+=a[i];
    }
    double as=(sum)/n;
    double d=0;
    for(int i=0;i<n;i++){
        d+=(a[i]-as)*(a[i]-as)/n;
    }
    d=sqrt(d);
    for(int i=0;i<n;i++){
        cout<<(a[i]-as)/d<<endl;

    }
    return 0;
}