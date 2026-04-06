#include <iostream>
#include <string>
#include <stack> // 💥 绝对纪律：必须用栈！
#include <vector>
#include <cctype>

using namespace std;

const long long MOD = 1e9 + 7;

// 绝对防爆：C++ 负数取模修正
long long safe_mod(long long x) {
    return (x % MOD + MOD) % MOD;
}

// 基于你的原生逻辑重构的引擎
long long ope(string s, const vector<long long>& a) {
    stack<long long> st; // 💥 拔掉 queue，换上 stack！
    size_t t = 0;  
    
    while(t < s.size()) { // 你的 t 循环控制极其脆弱，不要用 < s.size()-1
        if(s[t] == ' ') { 
            t++; 
            continue; 
        } else if(s[t] == 'x') {
            t++;
            int t1 = t;
            while(t < s.size() && isdigit(s[t])) {
                t++;
            }
            // 💥 致命修复：substr 的第二个参数是“长度”，必须是 t - t1！
            string s1 = s.substr(t1, t - t1); 
            int num = stoi(s1);
            st.push(a[num]); // 把变量的值压入栈
        } else if(isdigit(s[t])) {
            int t1 = t;
            while(t < s.size() && isdigit(s[t])) {
                t++;
            }
            // 💥 致命修复：同样是长度 t - t1
            string s1 = s.substr(t1, t - t1); 
            // 常数也必须取模
            long long num = safe_mod(stoll(s1)); 
            st.push(num);    
        } else if(s[t] == '*' || s[t] == '+' || s[t] == '-') {
            // 💥 栈的绝对法则：先弹出来的是右操作数，后弹出来的是左操作数！
            long long cc = st.top(); st.pop(); // 右边的数字
            long long bb = st.top(); st.pop(); // 左边的数字
            
            long long re = 0;
            if(s[t] == '*') re = safe_mod(bb * cc);
            if(s[t] == '-') re = safe_mod(bb - cc); // 减法顺序极其重要！
            if(s[t] == '+') re = safe_mod(bb + cc);
            
            st.push(re); // 算完的结果重新压回栈顶
            t++;
        } else {
            t++;
        }
    }
    // 最后的终极坍缩结果，必然是栈里唯一剩下的那个数字
    return st.top(); 
}