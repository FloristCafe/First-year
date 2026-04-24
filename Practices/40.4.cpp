#include<iostream>
#include<vector>
#define Q 998244353
#define ll long long
using namespace std;
vector<ll>p(10005);
vector<bool>chec(10000010,false);
    int siz=2;
    ll sums(ll p ,ll k){

        ll sum=0
        ll sum1=pow(p,2*k)-1;
        sum1/=p-1;
        sum1*=(2*k+1)*pow(p,k+1);
        sum1%=Q;
       sum+=sum1;
       sum%=Q;
       sum1=2*k*pow(p,2k)-(pow(p,2k)-1)/p-1;
       sum1/=p-1;
       sum-=sum1;
       sum%=Q;
       sum1=(k+1)*pow(p,k+1)-(pow(p,k+1)-1)/(p-1);
       sum1/=p-1;
       sum+=sum1;
       sum%=Q;
       sum1=pow(p,k+1)-1;
       sum1/=p-1;
       sum1*=k;
       sum+=sum1;
       sum%=Q;
       return sum;
    }
void get_p(void){
    p[0]=2;
    p[1]=3;

    for(ll i=2;i<=10000000;i++){
        if(chec[i]==false){
            p[siz]=i;
            siz++;
        }
        for(ll j=0;j<siz;j++){
            if(p[j]*i>10000000)break;
    chec[p[j]*i]=false;
        }
    }
    return ;
}
vector<pair<ll,ll>> extr(ll n){
    
vector<pair<ll,ll>>ss;
    ll n1=n;
     for(int i=0;i<siz;i++){
        if(n1==1)break;
        if(n1%p[i]!=0)continue;
        int time=0;
        while(n1%p[i]==0){
            n1/=p[i];
            time++;
        }
        ss.push_back({p[i],time});

     }
     return ss;
}
int main(){
    ll op,n;
    cin>>op>>n;
    if(op==0){
    ll sum=0;
for(int i=1;i<=n;i++){  
    vector<pair<ll,ll>>ele=extr(i);
    ll sum0=1;
    for(pair<ll,ll>aa:ele){
        sum0*=sums(aa.first,aa.second);
        sum0%=Q;
    }
    sum+=sum0;
    sum%=Q;
}
    }else{
ll sum=0;
for(int i=1;i<=n;i++){
    vector<pair<ll,ll>>ele=extr(i);
    ll sum0=1;
    for(pair<ll,ll>aa:ele){
        sum0*=sumss(aa.first,aa.second);
        sum0%=Q;
    }
    sum+=sum0;
    sum%=Q;
}
    }
}