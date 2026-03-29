#include <iostream>
using namespace std;

int a[20][20]; // 主地形（稍微开大一点防爆）
int b[5][5];   // 下落方块

// 💥 架构师核心引擎：绝对探测雷达
// 传入小方块左上角的物理坐标 (row, col)
// 如果发生物理重叠或越界，立刻报警返回 false
bool check(int row, int col) {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (b[i][j] == 1) { // 只关心方块实体的碰撞！
                int map_r = row + i - 1; // 映射到地形的绝对行坐标
                int map_c = col + j - 1; // 映射到地形的绝对列坐标
                
                // 报警条件：1. 砸穿了底盘（>15）  2. 和地形原有的实心块重叠了（==1）
                if (map_r > 15 || a[map_r][map_c] == 1) {
                    return false;
                }
            }
        }
    }
    return true; // 安全
}

int main() {
    // 1. 绝对干净的数据读入（绝不写错 i 和 j）
    for (int i = 1; i <= 15; i++) {
        for (int j = 1; j <= 10; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            cin >> b[i][j];
        }
    }
    
    int c;
    cin >> c;
    
    // 2. 物理引擎：重力下落模拟
    int drop_r = 1; 
    // 只要当前位置还能放得下，就继续往下掉
    while (check(drop_r, c)) {
        drop_r++; 
    }
    
    // 循环结束时，drop_r 是【第一个发生碰撞】的非法位置
    // 💥 绝对法则：回退一步，这就是最终卡死的位置！
    drop_r--; 
    
    // 3. 物质融合：极其严谨地填埋地形
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (b[i][j] == 1) { // 只有方块实体才会改变地形！绝不覆盖 0！
                a[drop_r + i - 1][c + j - 1] = 1;
            }
        }
    }
    
    // 4. 打印最终沙盘
    for (int i = 1; i <= 15; i++) {
        for (int j = 1; j <= 10; j++) {
            if (j > 1) cout << " ";
            cout << a[i][j];
        }
        cout << "\n";
    }
    
    return 0;
}