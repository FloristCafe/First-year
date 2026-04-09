#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<vector>
#include<set>
#include<cctype>

#define ll long long
#define P 998244353 
using namespace std;

int n, m;

// 💥 修复：绝对正确的快速幂求逆元引擎
ll pows(ll a, ll b) {
    ll res = 1;
    a %= P;
    while(b > 0) {
        if(b & 1) res = (res * a) % P; // 💥 必须是位运算 &
        a = (a * a) % P;
        b >>= 1;
    }
    return res;
}

void ope(const vector<string>& s) {
    // 💥 修复：动态分配内存，拒绝 VLA
    vector<map<string, ll>> count(m);
    map<string, int> id;
    
    // 阶段一：词法解剖
    for(int i = 0; i < m; i++) {
        string s1 = "";
        ll counts = 0; 
        
        int len = s[i].length();
        int ptr = 0;
        
        while(ptr < len) {
            s1 = "";
            while(ptr < len && isalpha(s[i][ptr])) {
                s1 += s[i][ptr];
                ptr++;
            }
            
            counts = 0;
            while(ptr < len && isdigit(s[i][ptr])) {
                counts = counts * 10 + (s[i][ptr] - '0');
                ptr++;
            }
            
            // 💥 修复：氧气漏洞，缺省系数绝对为 1
            if(counts == 0) counts = 1; 
            
            count[i][s1] += counts; // 用 += 应对同一元素多次出现
            if(id.find(s1) == id.end()) {
                id[s1] = id.size();
            }
        }
    }
    
    // 阶段二：矩阵物理装配
    int rows = id.size(); // 元素种类 (行)
    int cols = m;         // 物质种类 (列)
    
    // A[行][列] = 元素在各个物质中的数量
    vector<vector<ll>> a(rows, vector<ll>(cols, 0));
    
    for(int j = 0; j < cols; j++) {
        for(auto const& [elem, cnt] : count[j]) {
            a[id[elem]][j] = cnt % P;
        }
    }
    
    // 阶段三：极简模空间高斯消元求秩
    int rank = 0;
    for(int c = 0; c < cols && rank < rows; c++) {
        // 1. 寻找绝对主元
        int pivot = rank;
        while(pivot < rows && a[pivot][c] == 0) pivot++;
        
        // 💥 修复：如果是自由变量，直接跳过当前列，不需要任何扭曲的列交换！
        if(pivot == rows) continue; 
        
        // 2. 行交换
        if(pivot != rank) {
            swap(a[rank], a[pivot]);
        }
        
        // 3. 逆元降维
        ll inv_val = pows(a[rank][c], P - 2); 
        for(int j = c; j < cols; j++) {
            a[rank][j] = (a[rank][j] * inv_val) % P;
        }
        
        // 4. 绝对消除
        for(int i = rank + 1; i < rows; i++) {
            if(a[i][c] != 0) {
                ll factor = a[i][c];
                for(int j = c; j < cols; j++) {
                    // 💥 修复：负数取模防爆盾
                    a[i][j] = (a[i][j] - factor * a[rank][j]) % P;
                    if(a[i][j] < 0) a[i][j] += P; 
                }
            }
        }
        rank++; // 能量确立
    }
    
    // 最终裁决
    if(rank < cols) {
        cout << "Y\n";
    } else {
        cout << "N\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if(cin >> n) {
        while(n--) {
           cin >> m;
           vector<string> s(m);
           for(int i = 0; i < m; i++) {
               cin >> s[i];
           }
           ope(s);
        }
    }
    return 0;
}