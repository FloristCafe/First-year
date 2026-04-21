#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<unordered_map>
#include<cmath>
#define P 1000000007
#define ll long long
using namespace std;
vector<int>a(1005);
map<pair<int,int>,ll>dp;
map<pair<int,int>,set<int>>pq;
vector<int>p(1005);
bool check_p[100000]={false};
bool checker[100000]={false};
int cap=2;
void getp(void){
    check_p[2]=false;
    check_p[3]=false;
    p[0]=2;
    p[1]=3;
    for(int i<=2;i<250;i++){
        if(check_p[i]=false){
            cap++;
            p[cap]=i;
        }
        for(int j=0;j<cap;j++){
         check_p[p[j]*i]=true;
        }
    }
}
void get(int l,int r);
int main(){
    getp();
    int n;
    cin>>n;
    for(int i=1;i<n;i++){
    cin>>a[i];
    checker[a[i]]=true;
    }
    get(1,n);
    cout<<dp[{1,n}]<<endl;
    return 0;
}
void get(int l,int r){
    if(l==r-1){
        
        vector<int>ss;
        for(int i=0;i<cap;i++){
         if((a[r]-a[l])%p[i]==0){
            if((a[r]-a[l])/p[i]>1){
                ss.push_back(p[i]);
            }else{
                break;
            }
         }
        }
        size_t num=ss.size();
        vector<int>tho(num,1);
        int cur=0;
        int d=r-l;
        while(d>1){
            while(d%ss[i]==0){
                d%=ss[i];
                tho[i]++;
            }
            i++;
        }
        int count=1;
       for(int i=0;i<num;i++){
        count*=tho[i];
       }
       dp[{l,r}]=count;
    }
    for(int i=l+1;i<r;i++){
        get(l,i);
        get(i,r);
        dp[{l,r}]+=dp[{l,i}]*dp[{i,r}];
    }
    int d=r-l;
    vector<int>ss;
    for(int i=0;i<cap;i++){
       if(d%p[i]==0){
        if(d/p[i]>1){
            ss.push_back(p[i]);
        }
       }
    }
    size_t num=ss.size();
    vector<int>count1(num,0);
    vector<int>count2(num,0);
    int i=0;    
    while(d>1){
            while(d%ss[i]==0){
                d%=ss[i];
                count1[i]++;
            }
            i++;
        }
        d=r-l;
        for(size_t j=0;j<num;j++){
          int dd=0;
          while(dd<count1[j]){
            int mid=pow(ss[j],count1[j]-dd);
            int decide=1;
            int l1=l+mid;
            while(l1<r){
                if(checker[l1])decide=0;
            l1+=mid;
            }
            if(decide==0)break;
            dd++;
          }
          count2[j]=dd;
        }
        int counts=1;
        int couns=1;
        for(size_t j=0;j<num;j++){
            counts*=count1[j]+1;
            couns*=count1[j]-count2[j]+1;
        }
        counts-=couns;
     dp[{l,r}]+=counts;
    return ;
}
