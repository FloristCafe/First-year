#include<cstdio>
using namespace std;

const int N=1e6+5;
int n,k,a[N];
int ans1[N],ans2[N];

int q[N],head,tail;
void Calc(int res[]) //指针传参，答案计入 res 数组
{
	head=1,tail=0; //清空队列
	for(int i=1;i<=n;i++) //枚举窗口右端
	{
	  while(head<=tail && i-q[head]+1>k) q[head++]=0; //弹出已经离开窗口的元素
	  while(head<=tail && a[q[tail]]>a[i]) q[tail--]=0; //从队尾踢掉之前所有比当前元素大的数
	  q[++tail]=i; //当前元素自己加入队尾
	  if(i>=k) res[i-k+1]=q[head]; //完成以上操作后，队头即为最小值
	}
	return;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	
	Calc(ans1); //计算滑动窗口最小值位置，答案计入 ans1
	for(int i=1;i<=n-k+1;i++)
		printf("%d ",a[ans1[i]]);
	putchar('\n');
	
	for(int i=1;i<=n;i++)
		a[i]=-a[i]; //所有元素取相反数
	Calc(ans2); //计算此时的滑动窗口最小值位置，答案计入 ans2
	for(int i=1;i<=n-k+1;i++)
		printf("%d ",-a[ans2[i]]); //再取一遍相反数即为最大值
	return 0;
}
//条件：进出
//最重要：限制的范围内的最值