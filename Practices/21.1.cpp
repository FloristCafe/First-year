<<<<<<< HEAD
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

=======
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

>>>>>>> e3718e7119451d180d0fc9eee75a2b96fa2e0eb4
}