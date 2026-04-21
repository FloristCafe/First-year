#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

static unsigned long long next_val = 1;
/* RAND_MAX assumed to be 32767 */
int myrand(void) {
    next_val = (next_val * 1103515245 + 12345) % (1ULL << 32); // 确保在 32 位溢出等价范围内
    return ((unsigned)(next_val / 65536) % 32768);
}

// 突触物理连接
struct Synapse {
    int target;
    double w;
    int D;
};

// 神经元内部状态舱
struct Neuron {
    double v, u, a, b, c, d;
    int fire_count;
};

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S, P, T;
    if (!(cin >> N >> S >> P >> T)) return 0;

    double dt;
    cin >> dt;

    vector<Neuron> neurons(N);
    int read_count = 0;
    while (read_count < N) {
        int R;
        double v, u, a, b, c, d;
        cin >> R >> v >> u >> a >> b >> c >> d;
        for (int j = 0; j < R; ++j) {
            neurons[read_count + j] = {v, u, a, b, c, d, 0};
        }
        read_count += R;
    }

    vector<int> r_param(P);
    for (int i = 0; i < P; ++i) {
        cin >> r_param[i];
    }

    // adjacency list: node_id -> list of synapses
    vector<vector<Synapse>> adj(N + P);
    
    // 寻找系统最大传播延迟，以构建循环时间轴
    int max_D = 1; 
    for (int i = 0; i < S; ++i) {
        int s, t, D;
        double w;
        cin >> s >> t >> w >> D;
        adj[s].push_back({t, w, D});
        if (D > max_D) max_D = D;
    }

    // 💥 降维引擎核心：循环时间轴 Ring Buffer
    // pulse_buffer[t % buf_size][neuron_id] 表示在未来的某个时刻到达该神经元的总强度
    int buf_size = max_D + 5;
    vector<vector<double>> pulse_buffer(buf_size, vector<double>(N, 0.0));

    // 时间轴推演：离散时刻 k 从 1 推进到 T
    for (int k = 1; k <= T; ++k) {
        int cur_buf_idx = k % buf_size;

        // 1. 发放脉冲源 (P nodes)
        for (int i = 0; i < P; ++i) {
            if (r_param[i] > myrand()) {
                // 发放脉冲，投递到未来
                for (const auto& syn : adj[N + i]) {
                    int target_time = (k + syn.D) % buf_size;
                    pulse_buffer[target_time][syn.target] += syn.w;
                }
            }
        }

        // 2. 神经元状态演化与判定 (N nodes)
        for (int i = 0; i < N; ++i) {
            Neuron& n_ref = neurons[i];
            double old_v = n_ref.v;
            double old_u = n_ref.u;
            double I_k = pulse_buffer[cur_buf_idx][i]; // 当前时刻收到的总强度

            // 物理方程演算
            double new_v = old_v + dt * (0.04 * old_v * old_v + 5 * old_v + 140 - old_u) + I_k;
            double new_u = old_u + dt * n_ref.a * (n_ref.b * old_v - old_u);

            n_ref.v = new_v;
            n_ref.u = new_u;

            // 脉冲发放判定
            if (n_ref.v >= 30.0) {
                n_ref.fire_count++;
                
                // 投递自身脉冲到未来
                for (const auto& syn : adj[i]) {
                    int target_time = (k + syn.D) % buf_size;
                    pulse_buffer[target_time][syn.target] += syn.w;
                }
                
                // 状态绝对重置 (注意这里是对刚刚算出的 new_u 进行加减，而不是 old_u)
                n_ref.v = n_ref.c;
                n_ref.u = n_ref.u + n_ref.d; 
            }
        }
        
        // 💥 时空清扫：当前时刻的脉冲已经被全部消耗，必须清零，为下一次循环绕回做准备
        fill(pulse_buffer[cur_buf_idx].begin(), pulse_buffer[cur_buf_idx].end(), 0.0);
    }

    // 终端统计与汇报
    double min_v = 1e18, max_v = -1e18;
    int min_fire = 2e9, max_fire = -1;

    for (int i = 0; i < N; ++i) {
        if (neurons[i].v < min_v) min_v = neurons[i].v;
        if (neurons[i].v > max_v) max_v = neurons[i].v;
        if (neurons[i].fire_count < min_fire) min_fire = neurons[i].fire_count;
        if (neurons[i].fire_count > max_fire) max_fire = neurons[i].fire_count;
    }

    cout << fixed << setprecision(3) << min_v << " " << max_v << "\n";
    cout << min_fire << " " << max_fire << "\n";

    return 0;
}//