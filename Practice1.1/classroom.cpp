#include<iostream>
#include<cstring>
#include<cstdio> 
using namespace std;
int n,m;
int diff[1000011],need[1000011],rest[1000011],r[1000011],l[1000011],d[1000011];
bool isok(int x)
{
    memset(diff,0,sizeof(diff));//清零状态
    for(int i=1;i<=x;i++)
    {
        diff[l[i]]+=d[i];
        diff[r[i]+1]-=d[i]; 
    }
    for(int i=1;i<=n;i++)
    {
        need[i]=need[i-1]+diff[i];//这里构造diff保证了need数组的正确性，diff数组只是一个中间产物，真正的需求量是need数组
        //使得上一次的isok（）不会造成影响
        if(need[i]>rest[i])return 0;
    }
    return 1;
} 
int main()
{
    
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&rest[i]);
    for(int i=1;i<=m;i++)scanf("%d%d%d",&d[i],&l[i],&r[i]);
    int begin=1,end=m; 
    if(isok(m)){cout<<"0";return 0;}
    while(begin<end)
    {
        int mid=(begin+end)/2;
        if(isok(mid))begin=mid+1;
        else end=mid;
    }
    cout<<"-1"<<endl<<begin;
}
