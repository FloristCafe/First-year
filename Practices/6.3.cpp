<<<<<<< HEAD
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 使用 dx, dy 阵列进行 4 连通扫描
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, q;
    if (!(cin >> m >> n >> q)) return 0;

    // 动态开辟精确的画布物理空间，摒弃 101x101 的魔数
    vector<vector<char>> a(m, vector<char>(n, '.'));

    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 0) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            
            if (x1 == x2) { // 竖直线
                int start_y = min(y1, y2);
                int end_y = max(y1, y2);
                for (int j = start_y; j <= end_y; j++) {
                    if (a[x1][j] == '-' || a[x1][j] == '+') {
                        a[x1][j] = '+';
                    } else {
                        a[x1][j] = '|';
                    }
                }
            } else if (y1 == y2) { // 水平线
                int start_x = min(x1, x2);
                int end_x = max(x1, x2);
                for (int j = start_x; j <= end_x; j++) {
                    if (a[j][y1] == '|' || a[j][y1] == '+') {
                        a[j][y1] = '+';
                    } else {
                        a[j][y1] = '-';
                    }
                }
            }
        } else if (op == 1) {
            int start_x, start_y;
            char c;
            cin >> start_x >> start_y >> c;

            // 物理防爆：如果起点已经画好了线段，按照题意不会发生，但以防万一直接拦截
            if (a[start_x][start_y] == '-' || a[start_x][start_y] == '|' || a[start_x][start_y] == '+') {
                continue;
            }

            queue<pair<int, int>> Q;
            vector<vector<bool>> visited(m, vector<bool>(n, false));

            // 💥 补上致命漏洞：源点必须立刻染色！
            Q.push({start_x, start_y});
            visited[start_x][start_y] = true;
            a[start_x][start_y] = c; 

            while (!Q.empty()) {
                int curr_x = Q.front().first;
                int curr_y = Q.front().second;
                Q.pop();

                for (int d = 0; d < 4; d++) {
                    int nx = curr_x + dx[d];
                    int ny = curr_y + dy[d];

                    // 越界拦截
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;//需要放在前面，防止后面的越界访问
                    // 已访问拦截
                    if (visited[nx][ny]) continue;
                    
                    // 物理碰撞检测：撞到线段墙壁则停止蔓延
                    if (a[nx][ny] == '-' || a[nx][ny] == '|' || a[nx][ny] == '+') continue;

                    // 染色并继续蔓延
                    visited[nx][ny] = true;
                    a[nx][ny] = c;
                    Q.push({nx, ny});
                }
            }
        }
    }

    // 💥 终极渲染引整：倒转 Y 轴，还原真实的物理视角
    for (int y = n - 1; y >= 0; y--) {
        for (int x = 0; x < m; x++) {
            cout << a[x][y]; // 严丝合缝输出，拒绝空格污染
        }
        cout << "\n";
    }

    return 0;
=======
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 使用 dx, dy 阵列进行 4 连通扫描
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, q;
    if (!(cin >> m >> n >> q)) return 0;

    // 动态开辟精确的画布物理空间，摒弃 101x101 的魔数
    vector<vector<char>> a(m, vector<char>(n, '.'));

    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 0) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            
            if (x1 == x2) { // 竖直线
                int start_y = min(y1, y2);
                int end_y = max(y1, y2);
                for (int j = start_y; j <= end_y; j++) {
                    if (a[x1][j] == '-' || a[x1][j] == '+') {
                        a[x1][j] = '+';
                    } else {
                        a[x1][j] = '|';
                    }
                }
            } else if (y1 == y2) { // 水平线
                int start_x = min(x1, x2);
                int end_x = max(x1, x2);
                for (int j = start_x; j <= end_x; j++) {
                    if (a[j][y1] == '|' || a[j][y1] == '+') {
                        a[j][y1] = '+';
                    } else {
                        a[j][y1] = '-';
                    }
                }
            }
        } else if (op == 1) {
            int start_x, start_y;
            char c;
            cin >> start_x >> start_y >> c;

            // 物理防爆：如果起点已经画好了线段，按照题意不会发生，但以防万一直接拦截
            if (a[start_x][start_y] == '-' || a[start_x][start_y] == '|' || a[start_x][start_y] == '+') {
                continue;
            }

            queue<pair<int, int>> Q;
            vector<vector<bool>> visited(m, vector<bool>(n, false));

            // 💥 补上致命漏洞：源点必须立刻染色！
            Q.push({start_x, start_y});
            visited[start_x][start_y] = true;
            a[start_x][start_y] = c; 

            while (!Q.empty()) {
                int curr_x = Q.front().first;
                int curr_y = Q.front().second;
                Q.pop();

                for (int d = 0; d < 4; d++) {
                    int nx = curr_x + dx[d];
                    int ny = curr_y + dy[d];

                    // 越界拦截
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;//需要放在前面，防止后面的越界访问
                    // 已访问拦截
                    if (visited[nx][ny]) continue;
                    
                    // 物理碰撞检测：撞到线段墙壁则停止蔓延
                    if (a[nx][ny] == '-' || a[nx][ny] == '|' || a[nx][ny] == '+') continue;

                    // 染色并继续蔓延
                    visited[nx][ny] = true;
                    a[nx][ny] = c;
                    Q.push({nx, ny});
                }
            }
        }
    }

    // 💥 终极渲染引整：倒转 Y 轴，还原真实的物理视角
    for (int y = n - 1; y >= 0; y--) {
        for (int x = 0; x < m; x++) {
            cout << a[x][y]; // 严丝合缝输出，拒绝空格污染
        }
        cout << "\n";
    }

    return 0;
>>>>>>> e3718e7119451d180d0fc9eee75a2b96fa2e0eb4
}