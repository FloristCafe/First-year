#include<iostream>
#include<vector>
using namespace std;

long long tree[500010] = {0}; // 这就是那棵维护差分的树！不要叫它 a！
long long orig[500010] = {0}; // 用来存放原始数组
int n, m;

int lowbit(int x){
    return x & (-x);
}

// 极其冷血的向上汇报：给差分数组的第 x 个位置，增加增量 k
void add(int x, long long k){
    while(x <= n){
        tree[x] += k;
        x += lowbit(x);
    }
}

// 极其冷血的向下剥离：求差分数组的前 x 项和 (即原数组此时的单点真实值)
long long query(int x){
    long long sum = 0; // 绝对不能忘的初始化！
    while(x > 0){
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    
    // 1. 绝对的 1 号起点防线
    for(int i = 1; i <= n; i++){
        cin >> orig[i];
        // 初始化差分树：第 i 个位置的初始差分值，就是 orig[i] - orig[i-1]
        add(i, orig[i] - orig[i-1]); 
    }
    
    int opt, L, R;
    long long k; // 增量可能是大数
    int target;
    
    for(int i = 0; i < m; i++){
        cin >> opt;
        if(opt == 1){
            // 操作 1：区间修改
            cin >> L >> R >> k;
            add(L, k);           // 左边界突然拔高 k
            add(R + 1, -k);      // 右边界外瞬间跌落 k
        } else {
            // 操作 2：单点查询
            cin >> target;
            // 差分数组的前缀和，在代数上绝对等于该点的真实值！
            cout << query(target) << "\n"; 
        }
    }
    return 0;
}
