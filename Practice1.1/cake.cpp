
#include<bits/stdc++.h>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<stdio.h>
#include<cmath>
#include<deque>
#define debug cout<<"ok"<<endl
typedef long long ll;
const int maxn=1e7+10;
const int mod=1e9+7;
using namespace std;
int ans=-233333333,n,m,a,sum[maxn];
deque<int>q;//存下标
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        sum[i]=sum[i-1]+a;//前缀和
    }
    q.push_back(0);//赋初值
    for(int i=1;i<=n;i++)
    {
        while(q.front()+m<i)
            q.pop_front();//越界就pop
        ans=max(ans,sum[i]-sum[q.front()]);
        while(!q.empty()&&sum[q.back()]>=sum[i])//递减就pop
            q.pop_back();
        q.push_back(i);//一个循环内，窗口滑动来摸索最小值
        //队列中的都是用来被减去的，维持较小性
        //被踢出：比i辈分大，功能性却不如i
    }
    printf("%d\n",ans);
    return 0;
}

