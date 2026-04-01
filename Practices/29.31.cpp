#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// 💥 高维数据引擎：
// has_attr[k]：存有属性 k 的所有用户 DN，绝对升序且去重
map<int, vector<int>> has_attr;
// exact_match[k][v]：存有属性 k 且值为 v 的所有用户 DN，绝对升序且去重
map<int, map<int, vector<int>>> exact_match;

// ---------------------------------------------------------
// 绝对线性的集合合并引擎 (抛弃你那 O(N^2) 的 for 循环查找)
// ---------------------------------------------------------
vector<int> merge_and(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
    return res;
}

vector<int> merge_or(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
    return res;
}

// ---------------------------------------------------------
// 原子表达式坍缩 (解析最底层的数字和符号)
// ---------------------------------------------------------
vector<int> parse_base(const string& s, int& pos) {
    int attr = 0;
    // 💥 极其优雅的十进制进位，彻底干掉你那个滑稽的 guess 数组
    while (pos < s.length() && isdigit(s[pos])) {
        attr = attr * 10 + (s[pos] - '0');
        pos++;
    }
    
    char op = s[pos++]; // 提取操作符 ':' 或 '~'
    
    int val = 0;
    while (pos < s.length() && isdigit(s[pos])) {
        val = val * 10 + (s[pos] - '0');
        pos++;
    }

    if (op == ':') {
        if (exact_match.count(attr) && exact_match[attr].count(val)) {
            return exact_match[attr][val];
        } else {
            return {};
        }
    } else { // op == '~'
        if (has_attr.count(attr)) {
            vector<int> res;
            const vector<int>& all_has = has_attr[attr];
            vector<int> exclude;
            if (exact_match.count(attr) && exact_match[attr].count(val)) {
                exclude = exact_match[attr][val];
            }
            // 💥 物理剔除：用拥有该属性的所有人，减去属性值恰好相等的人
            set_difference(all_has.begin(), all_has.end(), exclude.begin(), exclude.end(), back_inserter(res));
            return res;
        } else {
            return {};
        }
    }
}

// ---------------------------------------------------------
// 终极递归解析引擎 (核心物理法则：隐式抽象语法树)
// 💥 注意：pos 必须是引用传递，这样递归深入消耗了字符，上层都会同步知晓！
// ---------------------------------------------------------
vector<int> parse_expr(const string& s, int& pos) {
    if (s[pos] == '&' || s[pos] == '|') {
        char op = s[pos++]; // 提取逻辑运算符
        
        pos++; // 跳过左括号 '('
        vector<int> left_res = parse_expr(s, pos); // 💥 递归向下坍缩左子树！
        pos++; // 跳过右括号 ')'
        
        pos++; // 跳过左括号 '('
        vector<int> right_res = parse_expr(s, pos); // 💥 递归向下坍缩右子树！
        pos++; // 跳过右括号 ')'
        
        if (op == '&') return merge_and(left_res, right_res);
        else return merge_or(left_res, right_res);
    } else {
        // 如果不是 & 和 |，那必然是原子表达式 (数字开头)
        return parse_base(s, pos);
    }
}

// 结果输出
void print_ans(const vector<int>& ans) {
    if (ans.empty()) {
        cout << "\n";
        return;
    }
    for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i] << (i == ans.size() - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (!(cin >> n)) return 0;

    // 载入基站数据
    for (int i = 0; i < n; i++) {
        int dn, cnt;
        cin >> dn >> cnt;
        for (int j = 0; j < cnt; j++) {
            int attr, val;
            cin >> attr >> val;
            has_attr[attr].push_back(dn);
            exact_match[attr][val].push_back(dn);
        }
    }

    // 💥 物理重构：将所有用户数据强行排序并去重，为 O(N) 的集合运算打下绝对基石
    for (auto& pair : has_attr) {
        sort(pair.second.begin(), pair.second.end());
        pair.second.erase(unique(pair.second.begin(), pair.second.end()), pair.second.end());
    }
    for (auto& pair1 : exact_match) {
        for (auto& pair2 : pair1.second) {
            sort(pair2.second.begin(), pair2.second.end());
            pair2.second.erase(unique(pair2.second.begin(), pair2.second.end()), pair2.second.end());
        }
    }

    int m;
    cin >> m;
    cin.ignore(); // 💥 吞掉换行符，防止 getline 读入空串

    // 引擎点火
    for (int i = 0; i < m; i++) {
        string expr;
        getline(cin, expr);
        int pos = 0; // 雷达游标初始化
        vector<int> ans = parse_expr(expr, pos); // 一行代码，穿透整棵树
        print_ans(ans);
    }

    return 0;
}