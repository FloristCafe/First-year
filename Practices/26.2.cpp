#include <iostream>
#include <vector>

using namespace std;

// 物理探针：定义树的真实坐标
struct Point {
    int x, y;
};

int B[55][55];

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, L, S;
    if (!(cin >> n >> L >> S)) return 0;

    // 存储宇宙中仅存的 n 棵树
    vector<Point> trees(n);
    for (int i = 0; i < n; i++) {
        cin >> trees[i].x >> trees[i].y;
    }

    int total_B_ones = 0;
    
    // 💥 破除输入陷阱：藏宝图数据是自顶向下 (S 到 0) 给出的
    for (int i = S; i >= 0; i--) {
        for (int j = 0; j <= S; j++) {
            cin >> B[i][j];
            if (B[i][j] == 1) total_B_ones++;
        }
    }

    int valid_maps = 0;

    // 遍历这 n 棵树，将它们逐一作为藏宝图的左下角候选点
    for (int i = 0; i < n; i++) {
        int cx = trees[i].x;
        int cy = trees[i].y;

        // 物理防爆：藏宝图的右上角绝对不能越过整个绿化图的边界 L
        if (cx + S > L || cy + S > L) continue;

        int match_cnt = 0;
        bool possible = true;

        // 💥 视角翻转：不扫描藏宝图，而是直接扫描宇宙中所有的树！
        for (int j = 0; j < n; j++) {
            int tx = trees[j].x;
            int ty = trees[j].y;

            // 如果这棵树落在了当前候选藏宝图的物理边界内
            if (tx >= cx && tx <= cx + S && ty >= cy && ty <= cy + S) {
                // 查验藏宝图上对应的局部坐标。如果是 0，说明产生了绝对冲突！
                if (B[tx - cx][ty - cy] == 0) {
                    possible = false;
                    break;
                }
                match_cnt++;
            }
        }

        // 只有当没有发生冲突，且框住的树的数量与藏宝图上 1 的数量绝对吻合时，才是真迹
        if (possible && match_cnt == total_B_ones) {
            valid_maps++;
        }
    }

    cout << valid_maps << "\n";
    return 0;
}