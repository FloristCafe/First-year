#include <iostream>
#include <vector>
#include <map> 

using namespace std;

int main() {
    int N = 1000; // 目标：寻找前 1000 个乌拉姆数
    vector<int> ulams;
    
    // 核心数据结构：用来记录“和”以及它被合成的“次数”
    // 思考：这里为什么用 std::map 而不是 std::unordered_map？
    map<int, int> sum_counts; 

    // 初始化基态
    ulams.push_back(1);
    ulams.push_back(2);
    sum_counts[1 + 2] = 1; // 第一次状态同步

    while (ulams.size() < N) {
        int next_ulam = 0;

        // TODO 1: 查表。遍历 sum_counts，找到下一个合法的乌拉姆数。
        // 你的判断条件必须同时满足：
        // a) 它必须严格大于当前已知的最大乌拉姆数 (ulams.back())
        // b) 它的组成方式必须唯一 (即 count == 1)
        for (auto const& [sum, count] : sum_counts) {
            if (sum > ulams.back() && count == 1) {
                next_ulam = sum;
                break; // 找到了最小的合法值，立刻跳出
            }
        }

        ulams.push_back(next_ulam);

        // TODO 2: 状态更新。既然找到了新成员，系统的可能性就扩张了。
        // 遍历之前【所有的】乌拉姆数，将它们与刚刚找到的 next_ulam 相加。
        // 并将产生的新和更新到 sum_counts 中。
        for (int i = 0; i < ulams.size() - 1; ++i) {
            // 填入你的状态更新逻辑
            sum_counts[ulams[i]+ulams[ulams.size()-1]]+=1;
        }

        // TODO 3: 内存与性能的终极拷问（可选，但区分平庸与卓越）
        // 随着 N 变大，sum_counts 会无限膨胀。
        // 实际上，那些小于 next_ulam 的 sum 已经永远不会再被用到了。
        // 如果这里不写一段清理过期数据的逻辑，你的空间复杂度会原地爆炸。
        // 你打算怎么清理？
        auto it=sum_counts.begin();
        while(it!=sum_counts.end()&&it->first<=next_ulam){
            it=sum_counts.erase(it);
        }
    }

    cout << "第 " << N << " 个乌拉姆数是: " << ulams.back() << endl;
    return 0;
}