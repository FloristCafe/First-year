#include<iostream>
#include<vector>
using namespace std;
int x[102]={0};
int count[102]={0};
bool find1[102][102]={false};
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    int l;
    cin>>l;
    for(int j=0;j<l;j++){
        int a;
        cin>>a;
        if(!find1[i][a]){
            find1[i][a]=true;
            x[a]++;
        }
        count[a]++;
    }
    }
    for(int i=1;i<=m;i++){
        cout<<x[i]<<" "<<count[i]<<endl;

    }
    return 0;
}