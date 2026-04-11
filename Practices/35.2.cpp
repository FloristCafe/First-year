#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 物理映射合并引擎：执行 B 映射，再执行 A 映射，合成最终映射 C
vector<char> combine_map(const vector<char>& A, const vector<char>& B) {
    vector<char> C(256);
    // ASCII 字符集全覆盖，绝对不越界
    for (int i = 0; i < 256; i++) {
        C[i] = A[B[i]]; 
    }
    return C;
}

// 💥 终极黑科技：映射快速幂 (O(log K) 的维度跃迁)
vector<char> quick_pow_map(vector<char> base, long long k) {
    vector<char> res(256);
    for (int i = 0; i < 256; i++) res[i] = i; // 初始化为绝对的单位映射 (自己变自己)
    
    while (k > 0) {
        if (k & 1) res = combine_map(base, res);
        base = combine_map(base, base);//二次映射-->c[i]=a[a[i]]
        k >>= 1;
    }
    return res;
}

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string raw_s;
    getline(cin, raw_s);
    // 极其严苛的 I/O 消毒：剔除 Windows 换行符，安全提取 # 内部的字符串
    if (!raw_s.empty() && raw_s.back() == '\r') raw_s.pop_back();
    string s = raw_s.substr(1, raw_s.length() - 2);

    int n;
    if (!(cin >> n)) return 0;
    string dummy;
    getline(cin, dummy); // 吞噬 cin>>n 留下的回车

    // 初始化基础法则：所有字符保持不变
    vector<char> base_map(256);
    for (int i = 0; i < 256; i++) base_map[i] = i;

    // 装载出题人的替换法则
    for (int i = 0; i < n; i++) {
        string rule;
        getline(cin, rule);
        if (!rule.empty() && rule.back() == '\r') rule.pop_back();
        // 直接根据下标解剖 #x y# (因为题目限定规则必定是这个格式，哪怕是空格)
        char x = rule[1];
        char y = rule[2];
        base_map[x] = y;
    }

    int m;
    cin >> m;
    
    // 接受指挥部的动态高频查询
    for (int i = 0; i < m; i++) {
        long long k;
        cin >> k;
        
        // 💥 O(log K) 极速求出 63 个字符在演化 K 代后的最终归宿
        vector<char> final_map = quick_pow_map(base_map, k);
        //开始字符串执行 1 次遍历，瞬间完成全量转化！
        cout << "#";
        for (char c : s) {
            cout << final_map[c];
        }
        cout << "#\n";
    }

    return 0;
}