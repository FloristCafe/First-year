#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

// 绝对的 I/O 消毒：剔除 Windows 环境带来的 \r 幽灵字符
void trim_cr(string& s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}

// 物理实体：补丁块
struct Block {
    long long NN, MM, nn, mm;
    vector<string> orig_frag;
    vector<string> new_frag;
};

// 严苛的补丁头正则解析引擎 (@@ -NN,MM +nn,mm @@)
bool parse_header(const string& s, long long& NN, long long& MM, long long& nn, long long& mm) {
    if (s.size() < 16 || s.substr(0, 4) != "@@ -") return false;
    size_t pos = 4;
    
    auto parse_num = [&](long long& val) {
        if (pos >= s.size() || s[pos] < '1' || s[pos] > '9') return false;
        val = 0;
        while (pos < s.size() && isdigit(s[pos])) {
            val = val * 10 + (s[pos] - '0');
            pos++;
        }
        return true;
    };
    
    if (!parse_num(NN)) return false;
    if (pos >= s.size() || s[pos] != ',') return false; pos++;
    if (!parse_num(MM)) return false;
    if (pos + 2 >= s.size() || s.substr(pos, 2) != " +") return false; pos += 2;
    if (!parse_num(nn)) return false;
    if (pos >= s.size() || s[pos] != ',') return false; pos++;
    if (!parse_num(mm)) return false;
    if (pos + 3 > s.size() || s.substr(pos, 3) != " @@") return false; pos += 3;
    if (pos != s.size()) return false;
    return true;
}

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    if (!(cin >> n)) return 0;
    string dummy;
    getline(cin, dummy);
    
    vector<string> original_file(n);
    for (long long i = 0; i < n; ++i) {
        getline(cin, original_file[i]);
        trim_cr(original_file[i]);
    }
    
    // 剔除 # 开头的注释干扰
    vector<string> patch_lines;
    string line;
    while (getline(cin, line)) {
        trim_cr(line);
        if (!line.empty() && line[0] == '#') continue;
        patch_lines.push_back(line);
    }
    
    // 将游离的文本切分为绝对独立的补丁块
    vector<vector<string>> raw_blocks;
    vector<string> curr_block;
    bool in_block = false;
    for (const string& l : patch_lines) {
        if (!l.empty() && l[0] == '@') {
            if (in_block) {
                raw_blocks.push_back(curr_block);
                curr_block.clear();
            }
            in_block = true;
        }
        if (in_block) curr_block.push_back(l);
    }
    if (in_block) raw_blocks.push_back(curr_block);
    
    if (raw_blocks.empty()) {
        cout << "Patch is damaged.\n";
        return 0;
    }
    
    // 💥 Phase 1: 格式与合法性硬核校验
    vector<Block> blocks;
    long long prev_NN = -1, prev_MM = -1;
    for (const auto& blk_lines : raw_blocks) {
        Block b;
        if (!parse_header(blk_lines[0], b.NN, b.MM, b.nn, b.mm)) {
            cout << "Patch is damaged.\n"; return 0;
        }
        if (prev_NN != -1 && b.NN < prev_NN + prev_MM) {
            cout << "Patch is damaged.\n"; return 0;
        }
        prev_NN = b.NN; prev_MM = b.MM;
        
        for (size_t i = 1; i < blk_lines.size(); ++i) {
            const string& l = blk_lines[i];
            if (l.empty() || (l[0] != '-' && l[0] != '+' && l[0] != ' ')) {
                cout << "Patch is damaged.\n"; return 0;
            }
            string content = l.substr(1);
            if (l[0] == '-') b.orig_frag.push_back(content);
            else if (l[0] == '+') b.new_frag.push_back(content);
            else {
                b.orig_frag.push_back(content);
                b.new_frag.push_back(content);
            }
        }
        if ((long long)b.orig_frag.size() != b.MM || (long long)b.new_frag.size() != b.mm) {
            cout << "Patch is damaged.\n"; return 0;
        }
        blocks.push_back(b);
    }
    
    // 💥 Phase 2: 纯粹暴力的绝对坐标定位雷达
    vector<long long> matched_idx(blocks.size());
    for (size_t i = 0; i < blocks.size(); ++i) {
        Block& b = blocks[i];
        
        // 生成绝对正确的偏好侦测序列：0, -1, 1, -2, 2...
        vector<long long> deltas;
        deltas.push_back(0);
        for (long long d = 1; d < b.MM; ++d) {
            deltas.push_back(-d);
            deltas.push_back(d);
        }
        
        bool found = false;
        for (long long delta : deltas) {
            long long idx = b.NN + delta - 1; // 转换为 0-based 数组索引
            
            // 物理边界拦截
            if (idx < 0 || idx + b.MM > n) continue;
            // 防止与上一个块的绝对坐标发生干涉 (重叠拦截)
            if (i > 0 && idx < matched_idx[i - 1] + blocks[i - 1].MM) continue;
            
            // 💥 纯净暴力比对：逐行核对字符串是否完全一致
            bool real_match = true;
            for (long long j = 0; j < b.MM; ++j) {
                if (original_file[idx + j] != b.orig_frag[j]) { 
                    real_match = false; 
                    break; 
                }
            }
            
            if (real_match) {
                matched_idx[i] = idx;
                // 宇宙共振：将当前的 delta 叠加到此后的所有块上
                for (size_t j = i; j < blocks.size(); ++j) {
                    blocks[j].NN += delta;
                }
                found = true;
                break;
            }
        }
        
        if (!found) { 
            cout << "Patch is damaged.\n"; 
            return 0; 
        }
    }
    
    // 💥 Phase 3: 多维坐标坍缩，生成最终文件
    long long curr_orig_idx = 0;
    for (size_t i = 0; i < blocks.size(); ++i) {
        long long match_idx = matched_idx[i];
        // 压入未修改的原文件切片
        for (long long j = curr_orig_idx; j < match_idx; ++j) {
            cout << original_file[j] << "\n";
        }
        // 压入修改后的新切片
        for (const string& s : blocks[i].new_frag) {
            cout << s << "\n";
        }
        curr_orig_idx = match_idx + blocks[i].MM;
    }
    // 压入最后的尾部切片
    for (long long j = curr_orig_idx; j < n; ++j) {
        cout << original_file[j] << "\n";
    }
    
    return 0;
}