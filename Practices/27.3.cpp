#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

// 物理探针：漫游数据的结构化封装
struct Record {
    int d_recv;   // 系统接收到这条数据的日期 d0
    int d_visit;  // 用户实际到访的日期 d1
    int u;        // 用户 ID
    int r;        // 地区 ID
};

// 时空状态板：risky[d] 存放第 d 天所有处于风险状态的地区
const int MAX_DAYS = 2005; 
unordered_set<int> risky[MAX_DAYS];
vector<Record> active_records;

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    for (int d = 0; d < n; ++d) {
        int r_cnt, m_cnt;
        cin >> r_cnt >> m_cnt;

        // 💥 阶段 1：风险地区状态注入 (绝对暴力填充)
        for (int i = 0; i < r_cnt; ++i) {
            int p;
            cin >> p;
            // d0 日收到，自 d0 至 d0+6 日绝对处于风险状态
            for (int D = d; D <= d + 6; ++D) {
                risky[D].insert(p);
            }
        }

        // 💥 阶段 2：漫游数据接收
        for (int i = 0; i < m_cnt; ++i) {
            int d_visit, u, r;
            cin >> d_visit >> u >> r;
            active_records.push_back({d, d_visit, u, r});
        }

        // 💥 阶段 3：风险用户筛查与数据清洗
        vector<Record> next_active;
        set<int> risk_users; // 利用 std::set 的物理特性：自动去重且严格递增排序

        for (const auto& rec : active_records) {
            // 数据清洗：如果接收日期已经超出近7日范围，直接斩断，不留内存碎片
            if (rec.d_recv < d - 6) continue;
            
            // 存活的数据进入下一代的考察队列
            next_active.push_back(rec);

            // 风险判定法则 1：到访日期必须在近7日内
            if (rec.d_visit < d - 6 || rec.d_visit > d) continue;

            // 风险判定法则 2：时空连续性审查
            bool is_continuous = true;
            for (int D = rec.d_visit; D <= d; ++D) {
                // 绝对越界防御：D < 0 时绝对安全，瞬间判定断裂
                if (D < 0 || risky[D].find(rec.r) == risky[D].end()) {
                    is_continuous = false;
                    break;
                }
            }

            // 锁定目标
            if (is_continuous) {
                risk_users.insert(rec.u);
            }
        }
        
        // 时空转移：替换为已清洗的活跃数据集，压榨内存
        active_records = next_active;

        // 终端输出：冷酷执行
        cout << d;
        for (int u : risk_users) {
            cout << " " << u;
        }
        cout << "\n";
    }

    return 0;
}
