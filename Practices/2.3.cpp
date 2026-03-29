#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// 物理基建：文档节点结构体
struct Node {
    int line_num;
    string tag;
    string id;
    vector<int> ancestors; // 核心降维：直接存储所有祖先的行号！
};

int main() {
    // 引擎点火：解除 I/O 封印，防御换行符
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    cin.ignore(); // 💥 绝对纪律：吞掉第一行的回车！

    vector<Node> docs;
    vector<int> active_path; // 核心状态机：当前活跃的祖先路径栈

    // ==========================================
    // 第一阶段：文档树解析与状态机统御
    // ==========================================
    for (int i = 1; i <= n; ++i) {
        string line;
        getline(cin, line);

        // 1. 测算层级 (Level)
        int dots = 0;
        while (dots < line.size() && line[dots] == '.') {
            dots++;
        }
        int level = dots / 2; // 每两个点一层

        // 2. 字符串手术刀：分离 Tag 和 ID
        string content = line.substr(dots);
        string tag = "", id = "";
        size_t space_pos = content.find(' ');
        
        if (space_pos != string::npos) {
            tag = content.substr(0, space_pos);
            id = content.substr(space_pos + 1); // 包含 '#'
        } else {
            tag = content;
        }

        // 题目要求：标签大小写不敏感，强行统一转小写
        for (char &c : tag) c = tolower(c);

        // 3. 💥 状态机核心突变：时间轴回滚
        // 如果当前层级小于等于栈的大小，冷血地将历史残影全部切除！
        if (level < active_path.size()) {
            active_path.resize(level); 
        }

        // 4. 封装节点并压入物理存储
        Node node;
        node.line_num = i;
        node.tag = tag;
        node.id = id;
        node.ancestors = active_path; // 继承当前绝对正确的祖先血脉

        docs.push_back(node);
        
        // 自己成为后续节点的潜在祖先
        active_path.push_back(i); 
    }

    // ==========================================
    // 第二阶段：级联查询与游标回溯
    // ==========================================
    for (int i = 0; i < m; ++i) {
        string query_line;
        getline(cin, query_line);

        // 1. 拆解查询词法
        vector<string> selectors;
        stringstream ss(query_line);
        string token;
        while (ss >> token) {
            if (token[0] != '#') {
                for (char &c : token) c = tolower(c); // 标签转小写
            }
            selectors.push_back(token);
        }
        if (selectors.empty()) continue;

        vector<int> results;

        // 2. 暴力降维比对：遍历所有节点
        for (const auto& node : docs) {
            // 目标靶点：必须先匹配最后一个选择器 (C)
            string target = selectors.back();
            bool target_match = (target[0] == '#' && node.id == target) || 
                                (target[0] != '#' && node.tag == target);
            
            if (!target_match) continue; // 靶点都不对，直接下一个

            // 3. 💥 核心绞杀点：双游标回溯匹配祖先 (A B)
            int sel_idx = selectors.size() - 2; // 选择器游标（从右往左）
            int anc_idx = node.ancestors.size() - 1; // 祖先游标（从下往上）

            while (sel_idx >= 0 && anc_idx >= 0) {
                string sel = selectors[sel_idx];
                int anc_line = node.ancestors[anc_idx];
                const Node& anc_node = docs[anc_line - 1]; // 物理映射：行号到下标

                bool match = (sel[0] == '#' && anc_node.id == sel) || 
                             (sel[0] != '#' && anc_node.tag == sel);

                if (match) {
                    sel_idx--; // 匹配成功，选择器要求满足一个，游标左移
                }
                anc_idx--; // 无论是否匹配，祖先游标永远向上回溯
            }

            // 如果选择器游标成功越过 0，说明所有级联条件全部满足！
            if (sel_idx < 0) {
                results.push_back(node.line_num);
            }
        }

        // 3. 输出打印
        for (size_t j = 0; j < results.size(); ++j) {
            cout << results[j] << (j + 1 == results.size() ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}