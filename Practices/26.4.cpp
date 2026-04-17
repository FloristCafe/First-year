#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

// 物理探针：定义反射面实体
struct Reflector {
    int type; // 1 表示 '/'， 2 表示 '\'
    double a; // 折损率
    bool active; // 存活雷达，用于惰性删除
};

const int MAXM = 100005;
Reflector refs[MAXM];

// 降维打击核心：将线段彻底碾碎为离散点。
// row_map[y][x] = id: 在水平线 y 上，x 坐标处的反射面编号
map<long long, map<long long, int>> row_map; 
// col_map[x][y] = id: 在垂直线 x 上，y 坐标处的反射面编号
map<long long, map<long long, int>> col_map; 

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    if (!(cin >> m)) return 0;

    for (int k = 1; k <= m; ++k) {
        int op;
        cin >> op;
        if (op == 1) {
            long long x1, y1, x2, y2;
            double a;
            cin >> x1 >> y1 >> x2 >> y2 >> a;
            
            // 判定反射面绝对朝向
            int dx = (x2 > x1) ? 1 : -1;
            int dy = (y2 > y1) ? 1 : -1;
            int type = (dx == dy) ? 1 : 2;
            
            refs[k] = {type, a, true};
            
            // 💥 物理坍缩：将反射面碾碎为内部离散点注入哈希空间
            long long steps = abs(x1 - x2);
            for (long long i = 1; i < steps; ++i) { // 严格剔除端点
                long long px = x1 + i * dx;
                long long py = y1 + i * dy;
                row_map[py][px] = k;
                col_map[px][py] = k;
            }
        } else if (op == 2) {
            int id;
            cin >> id;
            refs[id].active = false; // 惰性删除，绝不浪费算力去遍历点阵
        } else if (op == 3) {
            long long x, y;
            int d;
            double I_double;
            long long t;
            cin >> x >> y >> d >> I_double >> t;
            
            long long I = (long long)I_double;
            
            // 光线追踪主循环：事件驱动，而非空间步进
            while (t > 0 && I >= 1) {
                bool hit = false;
                long long hit_val = 0;
                int hit_id = 0;
                
                // 💥 O(log N) 极速索敌与惰性清理引擎
                if (d == 0) { // 向 +x 发射
                    while (true) {
                        auto it = row_map[y].lower_bound(x + 1); // 严格寻找大于当前 x 的点
                        if (it == row_map[y].end()) break;
                        if (refs[it->second].active) {
                            hit = true; hit_val = it->first; hit_id = it->second; break;
                        } else {
                            row_map[y].erase(it); // 清理历史残骸
                        }
                    }
                } else if (d == 2) { // 向 -x 发射
                    while (true) {
                        auto it = row_map[y].lower_bound(x); // 寻找 >=x 的点
                        if (it == row_map[y].begin()) break;
                        --it; // 回退一步，必然是严格小于 x 的最大点
                        if (refs[it->second].active) {
                            hit = true; hit_val = it->first; hit_id = it->second; break;
                        } else {
                            row_map[y].erase(it);
                        }
                    }
                } else if (d == 1) { // 向 +y 发射
                    while (true) {
                        auto it = col_map[x].lower_bound(y + 1);
                        if (it == col_map[x].end()) break;
                        if (refs[it->second].active) {
                            hit = true; hit_val = it->first; hit_id = it->second; break;
                        } else {
                            col_map[x].erase(it);
                        }
                    }
                } else if (d == 3) { // 向 -y 发射
                    while (true) {
                        auto it = col_map[x].lower_bound(y);
                        if (it == col_map[x].begin()) break;
                        --it;
                        if (refs[it->second].active) {
                            hit = true; hit_val = it->first; hit_id = it->second; break;
                        } else {
                            col_map[x].erase(it);
                        }
                    }
                }
                
                // 如果前方虚空，光线直接耗尽时间前进
                if (!hit) {
                    if (d == 0) x += t;
                    else if (d == 1) y += t;
                    else if (d == 2) x -= t;
                    else if (d == 3) y -= t;
                    t = 0;
                    break;
                }
                
                // 计算碰撞物理距离
                long long dist = (d % 2 == 0) ? abs(hit_val - x) : abs(hit_val - y);
                
                // 如果在时间耗尽前无法到达碰撞点
                if (dist > t) {
                    if (d == 0) x += t;
                    else if (d == 1) y += t;
                    else if (d == 2) x -= t;
                    else if (d == 3) y -= t;
                    t = 0;
                    break;
                }
                
                // 发生绝对碰撞，时空状态跃迁
                if (d % 2 == 0) x = hit_val;
                else y = hit_val;
                t -= dist;
                
                // 能量损耗：利用 floor 避免任何浮点精度溢出问题
                I = (long long)floor((double)I * refs[hit_id].a);
                if (I < 1) {
                    I = 0;
                    break;
                }
                
                // 光路绝对偏转
                if (refs[hit_id].type == 1) { // '/' 面
                    d = d ^ 1;
                } else {                      // '\' 面
                    d = 3 - d;
                }
            }
            
            // 终端汇报
            if (I < 1) cout << "0 0 0\n";
            else cout << x << " " << y << " " << I << "\n";
        }
    }
    return 0;
}