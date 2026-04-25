#include<iostream>
#include<vector>

using namespace std;
vector<int>a(103);
vector<int>b(108);
    int n;
bool dfs(int step){
    if(step==n){
     if((a[n-2]+a[n-1])/2==b[n-1])return true;
     return false;
    }
    int min_val=3*b[step-1]-a[step-2]-a[step-1];
        int max_val=2+3*b[step-1]-a[step-2]-a[step-1];
     if(min_val<1)min_val=1;
     for(int val=min_val;val<=max_val;val++){
        a[step]=val;
        if(dfs(step+1)){
            return true;
        }
     }
     return false;
    }
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    int max1=2*b[0]+1;
    for(int i=1;i<=max1;i++){
        int min2=max(1,2*b[0]-i);
        int max2=max1-i;
        for(int j=min2;j<=max2;j++){
            a[0]=i;
            a[1]=j;
            if(dfs(2)){
                int first=1;
                for(int c=0;c<n;c++){
                    if(!first)cout<<" ";
                    cout<<a[c];
                    first=0;
                }
                cout<<"\n";
                return 0;
            }
        }
    }
    return 0;

}