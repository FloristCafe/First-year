#include <iostream>
#include <string>
#include <cctype> // tolower 的老巢

using namespace std;

int main() {
    string target, text;
    
    // 1. 读取目标单词
    cin >> target;
    // 全部降维成小写
    for (int i = 0; i < (int)target.size(); i++) target[i] = tolower(target[i]);

    // 【致命防线】：吃掉第一行末尾残留的回车符，否则 getline 会直接读到一个空行！
    cin.ignore(); 

    // 2. 读取一整篇文章（包含空格）
    getline(cin, text);
    // 全部降维成小写
    for (int i = 0; i < (int)text.size(); i++) text[i] = tolower(text[i]);

    // 3. 战术伪装：加空格，强行阻断子串匹配
    target = " " + target + " ";
    text = " " + text + " ";

    // 4. 侦察与清点
    int count = 0;
    auto pos = text.find(target);
    int first_pos = pos; // 记录第一次出现的物理位置

    if (pos == string::npos) {
        cout << -1 << endl;
    } else {
        while (pos != string::npos) {
            count++;
            // 从上一次找到的位置往后挪 1 位，继续向后扫描
            pos = text.find(target, pos + 1); 
        }
        // 注意：题目要求的首字母位置，因为我们前面强行加了一个空格，所以真实的物理位置不用变
        // text 里的下标 0 是我们加的空格，下标 first_pos 刚好对应原字符串里的真实下标
        cout << count << " " << first_pos << endl;
    }

    return 0;
}