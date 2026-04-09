#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9; // 绝对的物理深渊
const int MAXM = 300005;

struct Cell {
    int x, w, id;
    bool operator<(const Cell& other) const {
        return x < other.x; // 绝对靠左优先
    }
};

int max_tree[MAXM << 2]; // 💥 线段树维护：存活节点的最大基础水量
int W[MAXM];             // 每个节点的基础水量
bool is_alive[MAXM];     // 存活雷达

// 构建最大值线段树
void build(int p, int l, int r) {
    if (l == r) {
        max_tree[p] = W[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    max_tree[p] = max(max_tree[p << 1], max_tree[p << 1 | 1]);
}

// 单点物理修正：指挥部直接点中某个水珠
void add_point(int p, int l, int r, int idx, int val) {
    if (l == r) {
        max_tree[p] += val;
        return;
    }
    int mid = (l + r) >> 1;
    if (idx <= mid) add_point(p << 1, l, mid, idx, val);
    else add_point(p << 1 | 1, mid + 1, r, idx, val);
    max_tree[p] = max(max_tree[p << 1], max_tree[p << 1 | 1]);
}

// 物理抹除：水珠已经进入爆裂倒计时，将其踢出宇宙
void kill_point(int p, int l, int r, int idx) {
    if (l == r) {
        max_tree[p] = -INF;
        return;
    }
    int mid = (l + r) >> 1;
    if (idx <= mid) kill_point(p << 1, l, mid, idx);
    else kill_point(p << 1 | 1, mid + 1, r, idx);
    max_tree[p] = max(max_tree[p << 1], max_tree[p << 1 | 1]);
}

// 💥 雷达索敌核心：寻找最靠左的、达到阈值的水珠
int find_leftmost_ready(int p, int l, int r, int threshold) {
    if (l == r) return l; // 锁定目标
    int mid = (l + r) >> 1;
    // 优先探查左子树，绝对保证“最靠左的先爆开”法则！
    if (max_tree[p << 1] >= threshold) {
        return find_leftmost_ready(p << 1, l, mid, threshold);
    } else {
        return find_leftmost_ready(p << 1 | 1, mid + 1, r, threshold);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, m, n;
    if (!(cin >> c >> m >> n)) return 0;

    vector<Cell> cells(m);
    for (int i = 0; i < m; ++i) {
        cin >> cells[i].x >> cells[i].w;
    }
    sort(cells.begin(), cells.end());

    map<int, int> x_to_id;
    for (int i = 1; i <= m; ++i) {
        W[i] = cells[i - 1].w;
        x_to_id[cells[i - 1].x] = i;
        is_alive[i] = true;
    }

    build(1, 1, m);
    int alive = m;
    int global_add = 0; // 💥 全局爆裂能量场

    // 变式核心调度器
    for (int i = 0; i < n; ++i) {
        int pos;
        cin >> pos;
        
        if (x_to_id.find(pos) != x_to_id.end()) {
            int id = x_to_id[pos];
            if (is_alive[id]) {
                add_point(1, 1, m, id, 1); // 指挥部单点注水
            }
        }

        queue<int> burst_queue;

        // 💥 能量波及扫描引擎
        auto scan_and_enqueue = [&]() {
            int threshold = 5 - global_add;
            // 只要全服最大值达到了阈值，就把它揪出来！
            while (max_tree[1] >= threshold) {
                int id = find_leftmost_ready(1, 1, m, threshold);
                burst_queue.push(id);
                kill_point(1, 1, m, id); // 立刻抹除，防止重复入队
                is_alive[id] = false;
            }
        };

        // 第 0 代扫描：处理指挥部单点注水引发的爆裂
        scan_and_enqueue();

        // 广度优先物理坍缩：绝对遵循代际优先法则
        while (!burst_queue.empty()) {
            int curr = burst_queue.front();
            burst_queue.pop();

            alive--; // 彻底死亡
            global_add++; // 💥 爆裂！全宇宙能量阈值下降 1 点！

            // 扫描因本次爆裂而达到临界点的新生代水珠，排入队尾！
            scan_and_enqueue();
        }

        cout << alive << "\n";
    }

    return 0;
}
