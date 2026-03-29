#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    int n, q;
    // 1. 读取行数并排雷：吞掉换行符，防止接下来的 getline 读到空行
    if (!(cin >> n >> q)) return 0;
    cin.ignore(); 

    map<string, map<string, string>> config;
    string current_section = "global";

    // --- 引擎解析段 ---
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line); // 2. 绝对法则：必须整行读取！
        
        if (line.empty() || line[0] == '#') continue; // 过滤空行与注释

        if (line[0] == '[' && line.back() == ']') {
            // 3. 极速状态切换：直接截取中间的名字
            current_section = line.substr(1, line.size() - 2);
        } else {
            // 4. 冷血切割：寻找第一个等号
            size_t pos = line.find('=');
            if (pos != string::npos) {
                // substr(起始位置, 长度)。如果没有填长度，默认截取到末尾！
                string key = line.substr(0, pos);
                string val = line.substr(pos + 1); 
                config[current_section][key] = val; // 5. 自动覆盖，极其优雅
            }
        }
    }

    // --- 查询响应段 ---
    for (int i = 0; i < q; i++) {
        string query;
        cin >> query; // 查询语句没有空格，可以用 cin
        
        size_t pos = query.find(':');
        if (pos != string::npos) {
            string sec = query.substr(0, pos);
            string key = query.substr(pos + 1);
            
            // 6. 防爆查询：必须先检查段落是否存在，再检查键是否存在
            if (config.count(sec) && config[sec].count(key)) {
                cout << config[sec][key] << "\n";
            } else {
                cout << "404\n";
            }
        } else {
            cout << "404\n";
        }
    }
    return 0;
}