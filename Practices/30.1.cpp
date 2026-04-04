#include <iostream>
#include <map>
#include <vector>
#include <string> // 引入 string
using namespace std;

// 使用 string 来存储局面状态
map<string, int> ks;

int main() {
    int n;
    char s;
    cin >> n;
    string current_state = ""; // 用来临时拼接当前局面的字符串

    for (int t = 0; t < n; t++) {
        current_state = ""; // 清空，准备读取新的一局
        
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) { // 【修正1】这里原来是 i<8
                cin >> s;
                current_state += s; // 拼接成 64 位的字符串
            }
        }
        
        // 直接用字符串作为键查询
        ks[current_state]++;
        cout << ks[current_state] << endl;
    }
    return 0;
}