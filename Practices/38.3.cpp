#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 开启 128 位底层装甲，对抗 94 比特的算力膨胀
typedef unsigned __int128 u128;
typedef uint64_t u64;

// 物理探针：将比特字符串切片并重组为高维整数
u128 parse_bits(const string& s, int start, int len) {
    u128 res = 0;
    for (int i = 0; i < len; i++) {
        res = (res << 1) | (s[start + i] - '0');
    }
    return res;
}

// 空间压缩：抹除所有的冗余占位符
string trim_spaces(string s) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    return s;
}

// ==========================================
// 编解码引擎模块
// ==========================================

// 将 58 位整数解码为 11 位完整字符串
string num_to_full_code(u128 val) {
    string s = "";
    for (int i = 0; i < 11; i++) {
        int rem = val % 38;
        val /= 38;
        char c;
        if (rem == 0) c = ' ';
        else if (rem >= 1 && rem <= 10) c = '0' + (rem - 1);
        else if (rem >= 11 && rem <= 36) c = 'A' + (rem - 11);
        else c = '_';
        s = c + s; // 逆向拼接
    }
    return trim_spaces(s);
}

// 将 11 位完整字符串编码为 58 位整数（用于哈希回溯）
u128 code_to_full_num(string s) {
    while (s.length() < 11) s += ' '; // 物理补齐
    u128 val = 0;
    for (int i = 0; i < 11; i++) {
        val *= 38;
        char c = s[i];
        if (c == ' ') val += 0;
        else if (c >= '0' && c <= '9') val += (c - '0' + 1);
        else if (c >= 'A' && c <= 'Z') val += (c - 'A' + 11);
        else if (c == '_') val += 37;
    }
    return val;
}

// 将 28 位短数字表示解码为短字符串
string short_to_code(u64 val) {
    val -= (1ULL << 25); // 剥离标识位
    int c6 = val % 26; val /= 26;
    int c5 = val % 26; val /= 26;
    int c4 = val % 26; val /= 26;
    int c3 = val % 10; val /= 10;
    int c2 = val % 36; val /= 36;
    int c1 = val % 37;

    string s = "";
    if (c1 == 0) s += ' ';
    else if (c1 <= 10) s += (char)('0' + c1 - 1);
    else s += (char)('A' + c1 - 11);

    if (c2 <= 9) s += (char)('0' + c2);
    else s += (char)('A' + c2 - 10);

    s += (char)('0' + c3);
    s += (char)('A' + c4);
    s += (char)('A' + c5);
    s += (char)('A' + c6);

    return trim_spaces(s);
}

// ==========================================
// 散列雷达与回溯模块
// ==========================================

// 绝对防爆散列计算器
u64 calc_hash(u128 val, int n) {
    u128 multiplier = 47055833459ULL;
    u128 res = val * multiplier;
    // 降维打击：除以 2^(64-n) 在底层等同于位移 >> (64-n)
    res >>= (64 - n);
    u64 mask = (1ULL << n) - 1;
    return (u64)(res & mask);
}

// 历史时空回溯搜索
string lookup_hash(u64 target_hash, int n_bits, const vector<string>& history) {
    // 逆向遍历，绝对保证“最后收到”以及“发送方优先”的严苛规则
    for (int i = (int)history.size() - 1; i >= 0; i--) {
        u128 num = code_to_full_num(history[i]);
        if (calc_hash(num, n_bits) == target_hash) {
            return history[i];
        }
    }
    return "";
}

// ==========================================
// 主控调度中心
// ==========================================

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<string> history;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        if (s[0] == '0') {
            // 简单消息解析引擎
            u64 recv_bits = parse_bits(s, 1, 28);
            u64 send_bits = parse_bits(s, 29, 28);
            u64 pos_bits = parse_bits(s, 57, 15);

            string recv_str, send_str;
            bool recv_exp = false, send_exp = false;
            string raw_recv, raw_send;

            // 接收方溯源
            if (recv_bits >= (1ULL << 25)) {
                raw_recv = short_to_code(recv_bits);
                recv_str = raw_recv;
                recv_exp = true;
            } else {
                string match = lookup_hash(recv_bits, 25, history);
                recv_str = (match == "") ? "###" : "#" + match;
            }

            // 发送方溯源
            if (send_bits >= (1ULL << 25)) {
                raw_send = short_to_code(send_bits);
                send_str = raw_send;
                send_exp = true;
            } else {
                string match = lookup_hash(send_bits, 25, history);
                send_str = (match == "") ? "###" : "#" + match;
            }

            // 屏幕输出
            cout << recv_str << " " << send_str;
            if (pos_bits > 0) cout << " " << pos_bits;
            cout << "\n";

            // 物理缝合历史记录：必须先压入接收方，再压入发送方
            if (recv_exp) history.push_back(raw_recv);
            if (send_exp) history.push_back(raw_send);

        } else {
            // 复杂消息解析引擎
            u128 full_bits = parse_bits(s, 1, 58);
            u64 hash_bits = parse_bits(s, 59, 12);
            int flag = s[71] - '0';

            string full_code = num_to_full_code(full_bits);
            string match = lookup_hash(hash_bits, 12, history);
            string hash_str = (match == "") ? "###" : "#" + match;

            if (flag == 0) {
                // full 是发送方，hash 是接收方
                cout << hash_str << " " << full_code << "\n";
            } else {
                // full 是接收方，hash 是发送方
                cout << full_code << " " << hash_str << "\n";
            }

            // 复杂消息中必定且仅有一个显式代号，直接压入历史
            history.push_back(full_code);
        }
    }

    return 0;
}