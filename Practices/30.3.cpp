#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// 物理探针：将 16 进制字符转化为整数
int hex_to_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int s;
    if (!(cin >> s)) return 0;

    vector<uint8_t> compressed_data;
    compressed_data.reserve(s);

    // 💥 第一阶段：吞噬所有十六进制文本，还原为纯粹的字节流
    string token;
    while (compressed_data.size() < s && cin >> token) {
        for (size_t i = 0; i < token.length(); i += 2) {
            uint8_t byte_val = (hex_to_val(token[i]) << 4) | hex_to_val(token[i + 1]);
            compressed_data.push_back(byte_val);
        }
    }

    int ptr = 0; // 输入流指针

    // 💥 第二阶段：解析 LEB128 导引域 (原始数据长度)
    uint32_t original_length = 0;
    int shift = 0;
    while (ptr < s) {
        uint8_t b = compressed_data[ptr++];
        original_length |= (uint32_t)(b & 0x7F) << shift;
        shift += 7;
        if ((b & 0x80) == 0) break; // 探测到最后一块碎片的标志位
    }

    vector<uint8_t> output;
    output.reserve(original_length);

    // 💥 第三阶段：解压状态机主循环
    while (ptr < s && output.size() < original_length) {
        uint8_t b = compressed_data[ptr++];
        uint8_t tag = b & 0x03;

        if (tag == 0x00) {
            // --- 字面量 ---
            uint32_t len_info = b >> 2;
            uint32_t l = 0;
            
            if (len_info <= 59) {
                l = len_info + 1;
            } else {
                int bytes_for_len = len_info - 59; // 1, 2, 3, or 4
                uint32_t len_val = 0;
                // 小端序读取长度
                for (int i = 0; i < bytes_for_len; ++i) {
                    len_val |= (uint32_t)compressed_data[ptr++] << (i * 8);
                }
                l = len_val + 1;
            }
            
            // 物理搬运原始字节
            for (uint32_t i = 0; i < l; ++i) {
                output.push_back(compressed_data[ptr++]);
            }
            
        } else if (tag == 0x01) {
            // --- 回溯引用 1 ---
            uint32_t l = ((b >> 2) & 0x07) + 4;
            uint32_t o = ((uint32_t)(b & 0xE0) << 3) | compressed_data[ptr++];
            
            // 严禁使用 memcpy！因为可能存在重叠拷贝 (o < l)
            for (uint32_t i = 0; i < l; ++i) {
                output.push_back(output[output.size() - o]);
            }
            
        } else if (tag == 0x10) {
            // --- 回溯引用 2 ---
            uint32_t l = (b >> 2) + 1;
            uint32_t o = compressed_data[ptr++];
            o |= (uint32_t)compressed_data[ptr++] << 8; // 小端序读取 o
            
            for (uint32_t i = 0; i < l; ++i) {
                output.push_back(output[output.size() - o]);
            }
        }
    }

    // 💥 终极渲染：严格按 8 字节切割，输出十六进制
    int out_len = output.size();
    for (int i = 0; i < out_len; ++i) {
        // 利用 cout 的格式化控制器
        cout << hex << setfill('0') << setw(2) << (int)output[i];
        if ((i + 1) % 8 == 0 || i == out_len - 1) {
            cout << "\n";
        }
    }

    return 0;
}