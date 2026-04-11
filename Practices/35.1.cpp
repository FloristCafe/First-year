#include<iostream>
#include<vector>
#include<cctype>
#include<string>
#include<map>
using namespace std;
int check(string s){
    map<char,int>ma;
    int a[4]={0};
   for(char c:s){
    if((c<='Z'&&c>='A')||(c<='z'&&c>='a'))a[0]=1;
    if(c<='9'&&c>='0')a[1]=1;
    if(c=='*'||c=='#')a[2]=1;
    ma[c]=0;
   }
   if(a[0]==0||a[1]==0||a[2]==0)return 0;
   for(char c:s){
    ma[c]++;
      if(ma[c]>2)return 1;
   }
   return 2;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    string s;
    for(int i=0;i<n;i++){
   cin>>s;
    cout<<check(s)<<endl;
    }
    return 0;
}