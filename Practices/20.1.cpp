<<<<<<< HEAD
#include<iostream>
#include<vector>
#include<cmath>
#define INF 0x3f3f3f3f
using namespace std;
int main(){
    int n;
    double X,Y;
    cin>>n>>X>>Y;
    int min_1,min_2,min_3;
    double dis1=INF,dis2=INF,dis3=INF;
    for(int i=1;i<=n;i++){
        double x,y;
        cin>>x>>y;
    if(sqrt((x-X)*(x-X)+(y-Y)*(y-Y))<dis3){
        dis3=sqrt((x-X)*(x-X)+(y-Y)*(y-Y));
        min_3=i;
    }
    if(dis3<dis2){
        int mi;
        double mid;
        mi=min_3;
        min_3=min_2;
        min_2=mi;
        mid=dis3;
        dis3=dis2;
        dis2=mid;
    }
    if(dis2<dis1){
    int mi;
        double mid;
        mi=min_1;
        min_1=min_2;
        min_2=mi;
        mid=dis1;
        dis1=dis2;
        dis2=mid;
        
    }
    }
    cout<<min_1<<endl;    cout<<min_2<<endl;    cout<<min_3<<endl;
return 0;
=======
#include<iostream>
#include<vector>
#include<cmath>
#define INF 0x3f3f3f3f
using namespace std;
int main(){
    int n;
    double X,Y;
    cin>>n>>X>>Y;
    int min_1,min_2,min_3;
    double dis1=INF,dis2=INF,dis3=INF;
    for(int i=1;i<=n;i++){
        double x,y;
        cin>>x>>y;
    if(sqrt((x-X)*(x-X)+(y-Y)*(y-Y))<dis3){
        dis3=sqrt((x-X)*(x-X)+(y-Y)*(y-Y));
        min_3=i;
    }
    if(dis3<dis2){
        int mi;
        double mid;
        mi=min_3;
        min_3=min_2;
        min_2=mi;
        mid=dis3;
        dis3=dis2;
        dis2=mid;
    }
    if(dis2<dis1){
    int mi;
        double mid;
        mi=min_1;
        min_1=min_2;
        min_2=mi;
        mid=dis1;
        dis1=dis2;
        dis2=mid;
        
    }
    }
    cout<<min_1<<endl;    cout<<min_2<<endl;    cout<<min_3<<endl;
return 0;
>>>>>>> e3718e7119451d180d0fc9eee75a2b96fa2e0eb4
}