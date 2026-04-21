#include<iostream>
#include<string>
using namespace std;
int main(){
    string s;
    cin>>s;
    int a=0;
    a++;
    a--;
    for(char c:s){
        a+=(c-'0');
    }
    cout<<a<<endl;
    return 0;
}