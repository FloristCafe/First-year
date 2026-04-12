#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

const long long MOD = 1000000007;

// 物理切片：词法单元
struct Token {
    bool is_var;
    string val;
};

// 状态机核心：变量实体
struct Var {
    int type; // 0: 未初始化, 1: 直接赋值 (物理焊死), 2: 间接赋值 (动态追踪)
    long long fixed_len;   // 如果是 type 1，物理存留的绝对长度
    vector<Token> tokens;  // 如果是 type 2，存留的抽象语法树 (AST)
    
    Var() : type(0), fixed_len(0) {}
};

// 宇宙变量环境
unordered_map<string, Var> env;//去除排序，减小时耗

// 核心雷达：动态计算变量的瞬时长度
// 传入 local_memo 保证单次求值中绝对不会发生重复计算造成的指数爆炸
long long get_len(const string& name, unordered_map<string, long long>& local_memo) {
    // 物理防爆：已经算过的直接提取
    if (local_memo.count(name)) return local_memo[name];

    // 状态 0：未初始化的变量长度绝对为 0
    if (env.count(name) == 0 || env[name].type == 0) {
        return local_memo[name] = 0;
    }

    // 状态 1：直接赋值的变量，提取物理焊死的快照长度
    if (env[name].type == 1) {
        return local_memo[name] = env[name].fixed_len;
    }

    // 状态 2：间接赋值的变量，沿着 AST 动态向下坍缩计算
    long long sum = 0;
    for (const auto& tok : env[name].tokens) {
        if (tok.is_var) {
            sum = (sum + get_len(tok.val, local_memo)) % MOD;
        } else {
            sum = (sum + tok.val.length()) % MOD;
        }
    }
    
    return local_memo[name] = sum;
}

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    
    string line;
    getline(cin, line); // 吸收掉 n 后面的换行符

    while (n--) {
        getline(cin, line);
        if (line.empty()) continue;

        // 💥 C++ 架构师的终极切片工具：stringstream
        stringstream ss(line);
        int op;
        string var_name;
        ss >> op >> var_name;

        if (op == 1) {
            // 指令 1：立刻求值，物理焊死
            string tok_str;
            long long total_len = 0;
            unordered_map<string, long long> local_memo; // 本次求值的局部记忆场
            
            while (ss >> tok_str) {
                if (tok_str[0] == '$') {
                    string v = tok_str.substr(1);
                    total_len = (total_len + get_len(v, local_memo)) % MOD;
                } else {
                    total_len = (total_len + tok_str.length()) % MOD;
                }
            }
            // 改变状态机：锁定为类型 1
            env[var_name].type = 1;
            env[var_name].fixed_len = total_len;
            env[var_name].tokens.clear();

        } else if (op == 2) {
            // 指令 2：剥离实体，装配 AST
            env[var_name].type = 2;
            env[var_name].fixed_len = 0;
            env[var_name].tokens.clear();
            
            string tok_str;
            while (ss >> tok_str) {
                if (tok_str[0] == '$') {
                    env[var_name].tokens.push_back({true, tok_str.substr(1)});
                } else {
                    env[var_name].tokens.push_back({false, tok_str});
                }
            }

        } else if (op == 3) {
            // 指令 3：呼叫雷达，扫描瞬时长度
            unordered_map<string, long long> local_memo;
            cout << get_len(var_name, local_memo) << "\n";
        }
    }

    return 0;
}
