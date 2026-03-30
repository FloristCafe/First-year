#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

char a[105][105];
int dp[105][105][16]; // 💥 维度降维：4把钥匙只有16种状态(0~15)

struct Node {
    int x, y, mask, step;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    int sx, sy;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            for (int k = 0; k < 16; k++) dp[i][j][k] = INF;
            if (a[i][j] == 'S') { sx = i; sy = j; }
        }
    }

    queue<Node> q;
    dp[sx][sy][0] = 0;
    q.push({sx, sy, 0, 0});

    while (!q.empty()) {
        Node curr = q.front(); // 💥 普通队列用 front!
        q.pop();

        // 到达终点，立刻返回（BFS的绝对单调性保证了这是最短路）
        if (a[curr.x][curr.y] == 'E') {
            cout << curr.step << "\n";
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            // 1. 物理越界与死胡同防爆
            if (nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] == '#') continue;

            int nmask = curr.mask; // 💥 绝对隔离：创建平行宇宙的新状态，不污染本我！

            // 2. 权限校验与获取
            if (a[nx][ny] >= 'A' && a[nx][ny] <= 'D') {
                int req_key = a[nx][ny] - 'A';
                if (!(nmask & (1 << req_key))) continue; // 没钥匙，直接撞墙
            } 
            else if (a[nx][ny] >= 'a' && a[nx][ny] <= 'd') {
                int get_key = a[nx][ny] - 'a';
                nmask |= (1 << get_key); // 捡起钥匙，状态跃迁
            }

            // 3. 高维雷达探测：这个平行宇宙我们来过吗？
            if (dp[nx][ny][nmask] > curr.step + 1) {
                dp[nx][ny][nmask] = curr.step + 1;
                q.push({nx, ny, nmask, curr.step + 1});
            }
        }
    }

    cout << "-1\n"; // 彻底绝望，无路可走
    return 0;
}