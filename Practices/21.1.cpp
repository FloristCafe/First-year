#include<iostream>
#include<vector>

using namespace std;
int main(){
    int n;
    cin>>n;
    int sum=0;
    for(int i=0;i<n;i++){
        int w,s;
        cin>>w>>s;
        sum+=w*s;
    }
    cout<<max(0,sum)<<endl;

}