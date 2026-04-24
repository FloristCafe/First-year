#include<iostream>
#include<vector>
#include<set>
#define INF 0x3f3f3f3f
#define N 65538
using namespace std;
vector<vector<int>>a(202,vector<int>(202));
pair<int,int> check1(int i,int j){
    pair<int,int> s1={0,0};
    int l=-INF,r=INF;
    int min1=INF;
    for(int t=0;t<9;t++){
        min1=min(min1,a[i][j+t]);
    }
    r=min(min1,r);
    int min2=INF,max2=-INF;
    for(int t=0;t<9;t++){
        if(t==0||t==3||t==6||t==8){min2=min(min2,a[i+1][j+t]);}
        else{
            max2=max(max2,a[i+1][j+t]);
        }
    }
    r=min(r,min2);
    l=max(l,max2);
    if(l>r) return s1;

        int min3=INF,max3=-INF;
    for(int t=0;t<9;t++){
        if(t==0||t==3||t==4||t==5||t==6||t==7){min3=min(min3,a[i+2][j+t]);}
        else{
            max3=max(max3,a[i+2][j+t]);
        }
    }
    r=min(r,min3);
    l=max(l,max3);
    if(l>r) return s1;
    int min4=INF,max4=-INF;
    for(int t=0;t<9;t++){
        if(t==0||t==5||t==6){min4=min(min4,a[i+3][j+t]);}
        else{
            max4=max(max4,a[i+3][j+t]);
        }
    }
    r=min(r,min4);
    l=max(l,max4);
    if(l>r) return s1;
    int min5=INF,max5=-INF;
    for(int t=0;t<9;t++){
        if(t<=6){min5=min(min5,a[i+4][j+t]);}
        else{
            max5=max(max5,a[i+4][j+t]);
        }
    }
    r=min(r,min5);
    l=max(l,max5);
    if(l>r) return s1;
     s1.first=l;
     s1.second=r;
     return s1;

}
int main(){
    int n,L;
    cin>>n>>L;
    set<int>now;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
    }

    for(int i=0;i<=n-4;i++){
    for(int j=0;j<=n-9;j++){
     pair<int,int>ss=check1(i,j);
     for(int l=ss.first+1;l<=ss.second;l++){
        now.insert(l);
     }
    }

    }

    for(int k:now){
        cout<<k<<endl;
    }
    return 0;

}