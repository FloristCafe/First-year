#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<map>
using namespace std;
struct day{
    int num=0;
    int ber[21]=0;//哪些人属于该组
    int liar=0;
}date[8];
struct student{
    string name;
    string prove[6];
    int yes[6]={0};//表示某句话是否说过
    int truth=0;//判定有无指出
}stu[21];
int check(string &a);//辅助删除多余词汇

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m,n,p;
    string a;
    cin>>m>>n>>p;
    for(int i=1;i<=m;i++){
        cin>>stu[i].name;
    }

string ab;

        for(int i=1;i<=p;i++){
       cin>>a;
       a.pop_back();
       int k;
for(k=1;k<=m;k++){
    if(stu[k].name==a){
        break;
    }
}
    getlines(cin,ab);
    int t=check(ab);
    stu[k].prove[t]=ab;
    stu[k].yes[t]=1;
    if(t==5){
        switch(ab):
        case "Monday":date[1].num++;
        date[1].ber[date[1].num]=i;
        case "Tuesday":date[2].num++;
        date[2].ber[date[2].num]=i;
        case "Wednesday":date[3].num++;
        date[3].ber[date[3].num]=i;
        case "Thursday":date[4].num++;
        date[4].ber[date[4].num]=i;
        case "Friday":date[5].num++;
        date[5].ber[date[5].num]=i;
        case "Saturday":date[6].num++;
        date[6].ber[date[6].num]=i;
        case "Sunday":date[7].num++;
        date[7].ber[date[7].num]=i;
    }
       }//完成语言，人物分类

        }



















        int check(string &a){
            size_t pos;
            pos=a.find("I am guilty.");
            if(pos!=string::npos){
                a="I";
                return 1;
            }
            pos=a.find("I am not guilty.");
            if(pos!=string::npos){
                a="I";
                return 2;
            }
            pos=a.find(" is guilty.");
            if(pos!=string::npos){
                a.erase(a.length()-11);
                return 3;
            }
         pos=a.find(" is not guilty.");
         if(pos!=string::npos){
            a.erase(a.length()-15);
            return 4;
         }
         pos=a.find("Today is ");
         if(pos!=string::npos){
            a.pop_back;
a.erase(0,9);
return 5;
         }
         return 0;
        }

