#include<iostream>
#include<vector>
#include<queue>
using namespace std;
//输出所有岛的步数
vector<int> sides[100005];
bool visited[100005] = {false};
int dist[100005]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        sides[u].push_back(v);
        sides[v].push_back(u);
    }

    // 极其冷血的初始化：所有城市默认距离为 -1（不可达）
    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
    }

    queue<int> q; // 标准工业管子

    // 起点点火
    visited[1] = true;
    dist[1] = 0;
    q.push(1);
//每次循环只走一步，q中同层级起点一定能无影响地清空（visited()保证）
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (size_t i = 0; i < sides[u].size(); i++) {
            int v = sides[u][i];
            if (!visited[v]) {

                // ==========================================
                // ⚠️ 把下面三行残缺的逻辑补全 ⚠️
                // 1. 给 v 打上 visited 烙印
                visited[v]=true;
                // 2. 更新 dist[v] 的值
                dist[v]=dist[u]+1;
                // 3. 把 v 推进管子 q 里
                q.push(v);
                // ==========================================
            }
        }
    }

    // 验收结果：输出 n 个城市的绝对物理距离
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    cout << "\n";

    return 0;
}