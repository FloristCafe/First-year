#include <iostream>
#include <vector>
#include <queue>
#include <utility> // 包含 pair

using namespace std;

// 绝对二维物理内存映射
int maze[1005][1005];
bool visited[1005][1005] = {false};
int dist[1005][1005];

// 战术方向盘：上、下、左、右的绝对物理偏移
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main() {
    // 极速 I/O 装甲
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    // 拦截极其边缘的空输入情况
    if (!(cin >> n >> m)) return 0;

    // 1. 地图装填与绝对刻度表初始化
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> maze[i][j];
            dist[i][j] = -1; // 初始化所有坐标为绝对不可达
        }
    }

    // 2. 工业管子制造与零号波源点火
    queue<pair<int, int>> q;
    
    // 起点 (1,1) 打上烙印，距离置零，强行入队
    visited[1][1] = true;
    dist[1][1] = 0;
    q.push({1, 1});

    // 3. 时间波纹引擎启动（绝对的时间长河控制）
    while (!q.empty()) {
        // 抽离并解析队首物理坐标
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // 启动 4 个方向的物理雷达探测
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 防线 A：物理边界防线（绝对不可越界）
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            
            // 防线 B：实体墙壁防线（绝对不可穿墙）
            if (maze[nx][ny] == 1) continue;
            
            // 防线 C：时间倒流防线（绝对不可走回头路）
            if (visited[nx][ny]) continue;

            // 三道防线全部通过：极其冷血地执行拓扑占领
            visited[nx][ny] = true;             // 落地染黑
            dist[nx][ny] = dist[x][y] + 1;      // 距离刻度绝对传递
            q.push({nx, ny});                   // 推进管子，成为下一秒波源
        }
    }

    // 4. 验收结果：无论波纹是否触及，直接调取终点刻度表
    cout << dist[n][m] << "\n";

    return 0;
}
//墙壁占空间，存在一个格子其本身就占空间