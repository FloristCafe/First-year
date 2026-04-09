#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// 物理实体定义
struct Cell {
    int x, w, id;
    // 强制按坐标从左到右物理排序
    bool operator<(const Cell& other) const {
        return x < other.x;
    }
};

const int MAXM = 300005;
int L[MAXM], R[MAXM], W[MAXM];

int main() {
    // 解除 I/O 物理封锁
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, m, n;
    if (!(cin >> c >> m >> n)) return 0;

    vector<Cell> cells(m);
    for (int i = 0; i < m; ++i) {
        cin >> cells[i].x >> cells[i].w;
    }

    // 💥 第一阶段：物理坐标系排序与对齐
    sort(cells.begin(), cells.end());

    map<int, int> x_to_id;
    // 💥 第二阶段：构建高维双向链表
    for (int i = 1; i <= m; ++i) {
        W[i] = cells[i - 1].w;
        x_to_id[cells[i - 1].x] = i; // 建立坐标到物理 ID 的映射
        
        L[i] = i - 1; // 左侧物理指针
        R[i] = i + 1; // 右侧物理指针
    }
    R[m] = 0; // 绝对边界：最后一个格子没有右邻居

    // 爆裂调度中心：利用 set 的自动排序特性，绝对保证 ID 最小（最靠左）的优先爆裂
    set<int> burst_queue;
    int alive = m; // 全局存活雷达

    // 💥 第三阶段：接受指挥部的动态操作
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        int id = x_to_id[p];

        // 注入能量
        W[id]++;
        if (W[id] >= 5) {
            burst_queue.insert(id);
        }

        // 连锁反应引擎启动
        while (!burst_queue.empty()) {
            // 取出绝对最靠左的爆裂点
            int curr = *burst_queue.begin();
            burst_queue.erase(burst_queue.begin());

            if (W[curr] < 5) continue; // 物理防爆层

            // 能量清零，宣告死亡
            W[curr] = 0; 
            alive--;

            int left_id = L[curr];
            int right_id = R[curr];

            // 💥 核心断链：将当前节点从双向链表中彻底物理抹除
            if (left_id != 0) R[left_id] = right_id;
            if (right_id != 0) L[right_id] = left_id;

            // 能量向左侧逃逸激荡
            if (left_id != 0) {
                W[left_id]++;
                if (W[left_id] >= 5) {
                    burst_queue.insert(left_id);
                }
            }

            // 能量向右侧逃逸激荡
            if (right_id != 0) {
                W[right_id]++;
                if (W[right_id] >= 5) {
                    burst_queue.insert(right_id);
                }
            }
        }

        // 汇报每次操作后的存活数
        cout << alive << "\n";
    }

    return 0;
}
