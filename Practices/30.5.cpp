#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9; // 物理极限负无穷防爆

struct Edge {
    int v;
    int w;
    int mask;
};

// 预处理降维：剔除平行边的冗余，只留最优
int min_w[26][26][1024];
vector<Edge> adj[26];

// 全局雷达：dist[起点][终点][收集的状态]
int dist_map[26][26][1024]; 

int main() {
    // 解除物理封锁
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    string t;
    if (!(cin >> N >> t)) return 0;

    int t_len = t.length();
    int full_mask = (1 << t_len) - 1;

    vector<string> s(N);
    vector<int> s_w(N);
    vector<int> s_mask(N);

    // 内存初始化
    for(int i=0; i<26; i++)
        for(int j=0; j<26; j++)
            for(int m=0; m<1024; m++)
                min_w[i][j][m] = INF;

    for (int i = 0; i < N; i++) {
        cin >> s[i];
        int u = s[i].front() - 'a';
        int v = s[i].back() - 'a';
        s_w[i] = s[i].length() - 1; // 物理成本：长度 - 1
        
        int mask = 0;
        for (int j = 0; j < t_len; j++) {
            // 💥 绝对防爆：这是判断 C++ 字符串包含的唯一正确写法！
            if (s[i].find(t[j]) != string::npos) {
                mask |= (1 << j);
            }
        }
        s_mask[i] = mask;
        // 如果有两条一模一样的边，极其冷血地只保留最短的那个
        min_w[u][v][mask] = min(min_w[u][v][mask], s_w[i]);
    }

    // 组装精简后的核心引擎
    for(int u=0; u<26; u++) {
        for(int v=0; v<26; v++) {
            for(int m=0; m<1024; m++) {
                if(min_w[u][v][m] != INF) {
                    adj[u].push_back({v, min_w[u][v][m], m});
                }
            }
        }
    }

    // 初始化全局雷达
    for(int i=0; i<26; i++)
        for(int j=0; j<26; j++)
            for(int m=0; m<1024; m++)
                dist_map[i][j][m] = INF;

    // 💥 核心点火：只跑 26 次 Dijkstra！
    for(int start = 0; start < 26; start++) {
        dist_map[start][start][0] = 0;
        // 按照距离从小到大排序的真·优先队列
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        // 状态压缩：用一个 int 装下 节点 u 和 mask，节约寻址时间
        pq.push({0, (start << 10) | 0});

        while(!pq.empty()) {
            auto [d, state] = pq.top();
            pq.pop();

            int u = state >> 10;
            int m = state & 1023;

            // 惰性删除剪枝
            if(d > dist_map[start][u][m]) continue;

            for(const auto& edge : adj[u]) {
                int nm = m | edge.mask;
                int nd = d + edge.w;
                if(nd < dist_map[start][edge.v][nm]) {
                    dist_map[start][edge.v][nm] = nd;
                    pq.push({nd, (edge.v << 10) | nm});
                }
            }
        }
    }

    // 💥 降维覆盖 (SOS DP 思想)：
    // 允许"多拿字符"，所以拥有全集状态的路径，也可以作为子集的合法解！
    for(int s = 0; s < 26; s++) {
        for(int e = 0; e < 26; e++) {
            for(int m = full_mask; m >= 0; m--) {
                for(int i = 0; i < t_len; i++) {
                    if(!(m & (1 << i))) {
                        dist_map[s][e][m] = min(dist_map[s][e][m], dist_map[s][e][m | (1 << i)]);
                    }
                }
            }
        }
    }

    // $O(1)$ 终极结算
    for (int i = 0; i < N; i++) {
        int u = s[i].front() - 'a';
        int v = s[i].back() - 'a';
        // 还需要哪些字符？异或运算完美剥离
        int needed_mask = full_mask ^ (full_mask & s_mask[i]);
        
        // 我们从 v 开始走，收集剩下的字符，最后回到起点 u 形成闭环
        int ans = s_w[i] + dist_map[v][u][needed_mask];
        
        if (ans >= INF) {
            cout << "-1\n";
        } else {
            cout << ans << "\n";
        }
    }

    return 0;
}