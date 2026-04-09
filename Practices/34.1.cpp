#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n,m,p,q;
    int a[p][q];
    for(int i=0;i<p;i++){
       for(int j=0;j<q;j++){
        cin>>a[i][j];
       }
    }
    for(int i=0;i<p;i++){
        int first=0
        for(int j=0;j<q;j++){
            if(first)cout<<" ";
            cout<<a[i][j];
            first=1;
        }
           cout<<endl;
     }
    return 0;
}