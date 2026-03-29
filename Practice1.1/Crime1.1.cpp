#include<bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
//xi huan yue zheng ling zen mo ni le
//0412 0412 0412 a ling sheng ri kuai le!
int m,n,p,guilty=-1;
int vis[105];
string name[105];
pair<int,string> sen[105];
string weekday[]={
	"Today is Monday.",
	"Today is Tuesday.",
	"Today is Wednesday.",
	"Today is Thursday.",
	"Today is Friday.",
	"Today is Saturday.",
	"Today is Sunday."
}; 
int getid(string s){//为名字编号 
	for(int i=0;i<m;i++){
		if(s==name[i]){
			return i;
		}
	}
	return -1;
}
//真话返回0 假话返回1 无意义的话返回-1 
int judge(int day,int gui,int now,string s){
	//day:假设的天数
	//gui：假设的罪犯
	//now:现在需要鉴定的人
	//s:now说的需鉴定的话 
	//需要分成五种情况讨论。 
	if(s=="I am guilty."){
		return gui!=now; //如果此人就是假设罪犯，他说的是真话 
	}
	if(s=="I am not guilty."){
		return gui==now; //如果此人就不是假设罪犯，他说的是真话 
	}
	for(int i=0;i<m;i++){
		if(name[i]+" is guilty."==s){
			return i!=gui; //如果他指认的确实是假设罪犯，他说的是真话 
		}
	}
	for(int i=0;i<m;i++){
		if(name[i]+" is not guilty."==s){
			return i==gui; 	//如果他洗白的确实不是假设罪犯，他说的就是真话 
		}
	}
	for(int i=0;i<7;i++){
		if(weekday[i]==s){//如果此人提供的日期就是假设日期，他说的就是真话 
			return day!=i;
		}
	}
	return -1;//剩下的都是无意义的话了。 
}
bool check(int day,int man){
	memset(vis,-1,sizeof vis);
	for(int i=0;i<p;i++){
		pair<int,string>sente=sen[i];
		int t=judge(day,man,sente.first,sente.second);
	//	cout<<t<<endl;
		int q=sente.first;
		if(t==0){//这句话是真话 
			if(vis[q]==-1){
				vis[q]=0;//把这句话标记一下 
			}else if(vis[q]==1){
				return 0;//如果这句话之前被证明过是真的，现在被推翻了，则假设不成立 
			}
		}else if(t==1){
			if(vis[q]==-1){
				vis[q]=1;
			}else if(vis[q]==0){
				return 0;
			}
		}
	}
	int cntf=0,cnto=0;//cntf:说假话的人数 cnto：说无意义话的人数 
	for(int i=0;i<m;i++){
		if(vis[i]==1)cntf++;
		else if(vis[i]==-1)cnto++;
	}
	//注意到，有的无意义话也可以是假话。 
	return cntf<=n&&cntf+cnto>=n;
}

main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>m>>n>>p;//输入人数，始终说谎的人数，证言数量 
	for(int i=0;i<m;i++){
		cin>>name[i];
	}
	for(int i=0;i<p;i++){
		string nam,say;
		cin>>nam;
		nam.erase(nam.end()-1);//删除人名和冒号间的空格 
		getline(cin,say);//注意到行末有一个空格。需要用getline读入。 
		say.erase(say.end()-1);//删除冒号 
		say.erase(say.begin());//删除行末空格 
		sen[i]=make_pair(getid(nam),say); //将名字编号和说的话打包。 
	}
	int cnt;//用于计算成立的假设数量 
	for(int day=0;day<7;day++){//枚举假设的时间 
		cnt=0;
		for(int i=0;i<m;i++){//枚举假设的罪犯编号 
			if(check(day,i)){ 
				cnt++;//若该假设成立，则成立数量+1，猜想罪犯为i 
				guilty=i;
			}
		}
		if(cnt>1){//成立方案不止一种，则不止一个人可能成为罪犯	
			cout<<"Cannot Determine";
			return 0;
		}
	}
	if(guilty==-1){//经过了所有假设后，依然找不到罪犯 
		cout<<"Impossible";
	}else{
		cout<<name[guilty];//输出编号对应的罪犯 
	}
	return 0;
}

