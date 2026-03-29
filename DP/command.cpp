#include<iostream>
#include<vector>
//只有直系下属不与长官同时出战
int N;
using namespace std;
vector<int>adj[N];
int h[N];
int dp[N][2];
void dfs(int u) {
    // 1. 基础能量初始化（无论有没有下属，自己出战的底线是自身的战力）
    dp[u][0] = 0;
    dp[u][1] = h[u];

    // 2. 战术深潜与能量折叠（如果没下属，循环自然进不去，完美充当 Base Case）
    for (int v : adj[u]) {
        dfs(v); // 绝对的深潜指令 (注意是圆括号！)
        
        // 💥 绝对物理排斥法则的代数表达：
        // 子方程 B：上司不出战，下属获得自由，在出战和不出战中取最大值叠加
        dp[u][0] += max(dp[v][0], dp[v][1]);
        
        // 子方程 A：上司出战，下属被绝对封锁，只能取不出战的能量
        dp[u][1] += dp[v][0]; 
    }
}
int main(){
    cin>>N;
    bool has_boss[N] = {false}; // 初始状态：所有人都没有上司

// 读取输入时：u 是 v 的直属上司
for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v); // 建立向下的物理指挥线
    has_boss[v] = true;  // 💥 绝对标记：v 已经有上司了！它绝不可能是最高长官！
}

// 寻找启动点
int root = -1;
for (int i = 1; i <= N; i++) {
    if (!has_boss[i]) { // 扫描全军，唯一一个依然没有上司的人
        root = i;
        break; // 找到神明，立刻撤退
    }
}

// 引擎点火！
dfs(root);
cout<<max(dp[root][0],dp[root][1]);
return 0;

}