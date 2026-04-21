<<<<<<< HEAD
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
=======
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
>>>>>>> e3718e7119451d180d0fc9eee75a2b96fa2e0eb4
}