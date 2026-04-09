#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

// 物理实体：离散化的单词序列
struct Word {
    vector<string> tokens;
    long long freq; // 绝对防爆：频率可能达到 10^10，必须使用 long long
};

// 状态机核心：多维偏序规则装甲
struct PairRule {
    string s1, s2;
    long long freq;
    
    // 💥 极其严密的 4 维降维判定法则
    bool operator<(const PairRule& other) const {
        // 规则 1：出现频率最高优先
        if (freq != other.freq) return freq > other.freq; 
        
        int len1 = s1.length() + s2.length();
        int len2 = other.s1.length() + other.s2.length();
        // 规则 2：拼接后字符串长度最短优先
        if (len1 != len2) return len1 < len2; 
        
        // 规则 3：前一个词汇长度最短优先
        if (s1.length() != other.s1.length()) return s1.length() < other.s1.length(); 
        
        // 规则 4：拼接后字典序最小优先
        string str1 = s1 + s2;
        string str2 = other.s1 + other.s2;
        return str1 < str2; 
    }
};

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<Word> words(n);
    set<char> init_chars; // 利用 set 的天然红黑树特性，自动去重并按字典序排序
    
    // 阶段一：数据注入与原子级解剖
    for (int i = 0; i < n; i++) {
        string s;
        long long f;
        cin >> s >> f;
        words[i].freq = f;
        for (char c : s) {
            init_chars.insert(c);
            // 将字符串强行打碎为单字母 Token 数组
            words[i].tokens.push_back(string(1, c)); 
        }
    }
    
    vector<string> vocab;
    
    // 阶段二：冷启动（装载初始单字符词汇表）
    for (char c : init_chars) {
        if (vocab.size() == m) break; // 绝对拦截：初始字符也可能超额
        vocab.push_back(string(1, c));
    }
    
    // 阶段三：BPE 核心聚合引擎启动
    while (vocab.size() < m) {
        map<pair<string, string>, long long> pair_counts;
        bool can_merge = false;
        
        // 1. 全局雷达扫描，统计所有相邻 Token 对的能量聚合度
        for (const auto& w : words) {
            if (w.tokens.size() < 2) continue;
            for (size_t i = 0; i < w.tokens.size() - 1; i++) {
                pair_counts[{w.tokens[i], w.tokens[i+1]}] += w.freq;
                can_merge = true;
            }
        }
        
        // 如果全宇宙的所有单词都已经被坍缩成了一个 Token，提前终止
        if (!can_merge) break; 
        
        // 2. 寻找绝对最优融合规则
        PairRule best_rule = {"", "", -1};
        bool first = true;
        
        for (auto const& [p, f] : pair_counts) {
            PairRule current = {p.first, p.second, f};
            if (first || current < best_rule) {
                best_rule = current;
                first = false;
            }
        }
        
        // 3. 将新物质注入词汇表
        vocab.push_back(best_rule.s1 + best_rule.s2);
        if (vocab.size() == m) break;
        
        // 4. 全局坍缩：执行物理融合
        for (auto& w : words) {
            vector<string> new_tokens;
            for (size_t i = 0; i < w.tokens.size(); i++) {
                // 💥 避开 <a, a> 陷阱：必须检查 i+1 不越界，并且精确匹配 s1 和 s2
                if (i < w.tokens.size() - 1 && w.tokens[i] == best_rule.s1 && w.tokens[i+1] == best_rule.s2) {
                    new_tokens.push_back(best_rule.s1 + best_rule.s2);
                    i++; // 💥 强制跃迁：跳过被吃掉的右半部分，绝对防止自我吞噬！
                } else {
                    new_tokens.push_back(w.tokens[i]);
                }
            }
            // 物理指针移交
            w.tokens = new_tokens; 
        }
    }
    
    // 最终裁决输出
    for (const string& v : vocab) {
        cout << v << "\n";
    }
    
    return 0;
}