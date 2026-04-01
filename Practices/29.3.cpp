#include<iostream>
#include<vector>
#include<map>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
struct node{
    map<int,int>as;
}cha[2505];//表示属性
int guess[6]={1,10,100,1000,10000,100000};
vector<int> push(string s){

  vector<int>pp;
    int k=0;
    int num=0;
    while(isdigit(s[k])){
        k++;
    }
    for(int i=0;i<k;i++){
        num+=guess[k-i-1]*(s[i]-'0');
    }
    int t=k+1;
    int num1=0;
    while(isdigit(s[t])){
        t++;
    }
    for(int i=k+1;i<t;i++){
        num1+=guess[t-i-1]*(s[i]-'0');
    }
if(s[k]==':'){

    for( const auto& cd:cha[num].as){
        if(cd.second==num1){
pp.push_back(cd.first);
        }
    }
    return pp;
}else{
    for(const auto& cd:cha[num].as){
        if(cd.second!=num1){
pp.push_back(cd.first);
        }
    }
    return pp;

}
}
void printt(vector<int>ss){
    int fir=0;
    for(auto i:ss){
        if(fir)cout<<" ";
        cout<<i;
        fir=1;
    }
    cout<<endl;
    return ;
}


int main(){
    int m,n;
    cin>>n;
    int a,b;
    for(int i=1;i<=n;i++){
    cin>>a;
    cin>>b;
    int p,q;
    for(int k=0;k<b;k++){
      cin>>p>>q;
      cha[p].as[a]=q;
    }
    }
    cin>>m;
    cin.ignore();
    string s1,s2,s3;
    for(int j=0;j<m;j++){
getline(cin,s1);
if(isdigit(s1[0])){
    vector<int> sq=push(s1);
    sort(sq.begin(),sq.end());
    printt(sq);
}
else{
    size_t pos2=s1.find(')');
    string s2=s1.substr(2,pos2);
    string s3=s1.substr(pos2+2);
    size_t pos1=s3.find(')');
    s3=s3.substr(0,pos1);
    vector<int>sp=push(s2);
    vector<int>sq=push(s3);
    if(s1[0]=='&'){
        vector<int>st;
    for(auto cd:sq){
        if(find(sp.begin(),sp.end(),cd)!=sp.end())st.push_back(cd);
        
    }
    sort(st.begin(),st.end());
    printt(st);
    }else{
        vector<int>st=sq;
        for(auto cd:sp){
            if(find(sq.begin(),sq.end(),cd)==sq.end()){
                st.push_back(cd);
            }
        }
        sort(st.begin(),st.end());
        printt(st);
    }
}

    }
    return 0;
}