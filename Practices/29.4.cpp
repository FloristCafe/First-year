#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

// 💥 物理区间节点
struct Node {
    string l, r;
    mutable int id; // mutable 允许在 set 迭代器中直接修改，但本题直接推平更稳
    bool operator<(const Node& o) const {
        return l < o.l;
    }
};

set<Node> odt;

// --- 物理降维：剥离格式外衣 ---
string strip(const string& s) {
    string res;
    for (char c : s) if (c != ':') res.push_back(c);
    return res;
}

// --- 十六进制进位引擎 ---
string add_one(string s) {
    bool overflow = true;
    for (int i = (int)s.length() - 1; i >= 0; i--) {
        if (s[i] == 'f') {
            s[i] = '0';
        } else {
            if (s[i] == '9') s[i] = 'a';
            else s[i]++;
            overflow = false;
            break;
        }
    }
    if (overflow) return "OVERFLOW"; // 绝对防爆：触碰物理天花板
    return s;
}

// --- 十六进制退位引擎 ---
string sub_one(string s) {
    for (int i = (int)s.length() - 1; i >= 0; i--) {
        if (s[i] == '0') {
            s[i] = 'f';
        } else {
            if (s[i] == 'a') s[i] = '9';
            else s[i]--;
            break;
        }
    }
    return s;
}

// 💥 核心物理撕裂操作
auto split(const string& pos) {
    if (pos == "OVERFLOW") return odt.end();
    auto it = odt.lower_bound({pos, "", 0});
    // 如果完美命中左边界，直接返回，无需撕裂
    if (it != odt.end() && it->l == pos) return it;
    
    it--; // 回退到包含该坐标的区间
    string l = it->l, r = it->r;
    int id = it->id;
    
    // 物理铲除旧区间，植入分裂后的两个新区间
    odt.erase(it);
    odt.insert({l, sub_one(pos), id});
    return odt.insert({pos, r, id}).first;
}

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    // 宇宙的初始状态：全空
    string min_ip = string(n / 4, '0');
    string max_ip = string(n / 4, 'f');
    odt.insert({min_ip, max_ip, 0});

    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int id;
            string l_str, r_str;
            cin >> id >> l_str >> r_str;
            string L = strip(l_str);
            string R = strip(r_str);

            // 💥 绝对法则：必须先分裂右边界，再分裂左边界！防止迭代器在物理重建中失效！
            auto itr = split(add_one(R));
            auto itl = split(L);

            bool has_other = false;
            bool has_self = false;
            bool has_unassigned = false;

            // 扫描雷达
            for (auto it = itl; it != itr; ++it) {
                if (it->id == 0) has_unassigned = true;
                else if (it->id == id) has_self = true;
                else has_other = true;
            }

            // 指挥部的残酷判定逻辑
            if (has_other) {
                cout << "NO\n";
            } else {
                if (has_self && !has_unassigned) {
                    cout << "NO\n"; // 全部都是自己的，毫无意义的扩张
                } else {
                    cout << "YES\n";
                    // 暴力推平：铲除旧势力，烙上新 ID
                    odt.erase(itl, itr);
                    odt.insert({L, R, id});
                }
            }
        } else if (op == 2) {
            string s_str;
            cin >> s_str;
            string s = strip(s_str);

            auto it = odt.lower_bound({s, "", 0});
            if (it == odt.end() || it->l > s) it--;
            cout << it->id << "\n";
            
        } else if (op == 3) {
            string l_str, r_str;
            cin >> l_str >> r_str;
            string L = strip(l_str);
            string R = strip(r_str);

            auto itr = split(add_one(R));
            auto itl = split(L);

            int owner = -1;
            bool valid = true;

            for (auto it = itl; it != itr; ++it) {
                if (it->id == 0) {
                    valid = false;
                    break; // 发现真空地带，防线崩塌
                }
                if (owner == -1) {
                    owner = it->id;
                } else if (owner != it->id) {
                    valid = false;
                    break; // 发现异星势力，防线崩塌
                }
            }

            if (valid && owner != -1) cout << owner << "\n";
            else cout << "0\n";
        }
    }

    return 0;
}