<<<<<<< HEAD
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

// 物理探针：定义逻辑门结构体
struct Gate {
    string type;
    int in_degree_max; // 设计入度
    vector<int> target_gates; // 输出指向哪些逻辑门
};

// 执行单个逻辑门的终极运算
int execute_gate(const string& type, const vector<int>& inputs) {
    if (type == "NOT") return !inputs[0];
    
    int res = inputs[0];
    if (type == "AND" || type == "NAND") {
        for (size_t i = 1; i < inputs.size(); ++i) res &= inputs[i];
        if (type == "NAND") res = !res;
    } else if (type == "OR" || type == "NOR") {
        for (size_t i = 1; i < inputs.size(); ++i) res |= inputs[i];
        if (type == "NOR") res = !res;
    } else if (type == "XOR") {
        for (size_t i = 1; i < inputs.size(); ++i) res ^= inputs[i];
    }
    return res;
}

void solve() {
    int M, N;
    cin >> M >> N;

    vector<Gate> gates(N + 1);
    // 输入信号到逻辑门的映射：input_targets[m] 包含输入信号 m 指向的所有逻辑门
    vector<vector<int>> input_targets(M + 1);

    for (int i = 1; i <= N; ++i) {
        string func;
        int k;
        cin >> func >> k;
        gates[i].type = func;
        gates[i].in_degree_max = k;
        
        for (int j = 0; j < k; ++j) {
            string s;
            cin >> s;
            int src_id = stoi(s.substr(1));
            if (s[0] == 'I') {
                input_targets[src_id].push_back(i);
            } else if (s[0] == 'O') {
                gates[src_id].target_gates.push_back(i);
            }
        }
    }

    int S;
    cin >> S;

    // 预备空间：存储这 S 次的所有输入矩阵，避免遇到 LOOP 提前退出时截断输入流
    vector<vector<int>> all_inputs(S, vector<int>(M + 1));
    vector<vector<int>> all_queries(S);

    for (int i = 0; i < S; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> all_inputs[i][j];
        }}
        
 for(int i=0;i<S;++i)
        {
        int si;
        cin >> si;
        all_queries[i].resize(si);
        for (int j = 0; j < si; ++j) {
            cin >> all_queries[i][j];
        }
    }

    // 💥 第一阶段：全局拓扑环路检测 (只需要测一次物理结构)
    vector<int> in_degree(N + 1);
    for (int i = 1; i <= N; ++i) {
        in_degree[i] = gates[i].in_degree_max;
    }
    
    queue<int> topo_q;
    // 假设所有的输入(I)都已经准备好，剔除这部分的入度
    for (int i = 1; i <= M; ++i) {
        for (int target : input_targets[i]) {
            in_degree[target]--;
            if (in_degree[target] == 0) {
                topo_q.push(target);
            }
        }
    }
    
    int processed_gates = 0;
    // 有些门可能没有任何输入，或者输入全来自其他入度为0的门，必须先将它们入队
    for (int i = 1; i <= N; ++i) {
        if (in_degree[i] == 0) {
            topo_q.push(i);
        }
    }

    vector<int> topo_order; // 保存绝对的运算顺序，后续加速
    while (!topo_q.empty()) {
        int u = topo_q.front();
        topo_q.pop();
        processed_gates++;
        topo_order.push_back(u);

        for (int v : gates[u].target_gates) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                topo_q.push(v);
            }
        }
    }

    // 拓扑审判：如果没有处理完所有器件，绝对存在环路
    if (processed_gates < N) {
        cout << "LOOP\n";
        return; 
    }

    // 💥 第二阶段：S 次并行或串行运转 (复用安全的拓扑顺序)
    for (int s = 0; s < S; ++s) {
        vector<int> gate_outputs(N + 1, -1);
        vector<vector<int>> received_inputs(N + 1);

        // 1. 注入源头势能 (M个输入)
        for (int i = 1; i <= M; ++i) {
            int val = all_inputs[s][i];
            for (int target : input_targets[i]) {
                received_inputs[target].push_back(val);
            }
        }

        // 2. 按照绝对安全的拓扑顺序点火
        for (int u : topo_order) {
            // 所有入度均已到达，瞬间收敛出结果
            gate_outputs[u] = execute_gate(gates[u].type, received_inputs[u]);
            
            // 将结果投递给下游
            for (int v : gates[u].target_gates) {
                received_inputs[v].push_back(gate_outputs[u]);
            }
        }

        // 3. 终端清算
        for (size_t i = 0; i < all_queries[s].size(); ++i) {
            cout << gate_outputs[all_queries[s][i]] << (i + 1 == all_queries[s].size() ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    if (cin >> Q) {
        while (Q--) {
            solve();
        }
    }
    return 0;
=======
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

// 物理探针：定义逻辑门结构体
struct Gate {
    string type;
    int in_degree_max; // 设计入度
    vector<int> target_gates; // 输出指向哪些逻辑门
};

// 执行单个逻辑门的终极运算
int execute_gate(const string& type, const vector<int>& inputs) {
    if (type == "NOT") return !inputs[0];
    
    int res = inputs[0];
    if (type == "AND" || type == "NAND") {
        for (size_t i = 1; i < inputs.size(); ++i) res &= inputs[i];
        if (type == "NAND") res = !res;
    } else if (type == "OR" || type == "NOR") {
        for (size_t i = 1; i < inputs.size(); ++i) res |= inputs[i];
        if (type == "NOR") res = !res;
    } else if (type == "XOR") {
        for (size_t i = 1; i < inputs.size(); ++i) res ^= inputs[i];
    }
    return res;
}

void solve() {
    int M, N;
    cin >> M >> N;

    vector<Gate> gates(N + 1);
    // 输入信号到逻辑门的映射：input_targets[m] 包含输入信号 m 指向的所有逻辑门
    vector<vector<int>> input_targets(M + 1);

    for (int i = 1; i <= N; ++i) {
        string func;
        int k;
        cin >> func >> k;
        gates[i].type = func;
        gates[i].in_degree_max = k;
        
        for (int j = 0; j < k; ++j) {
            string s;
            cin >> s;
            int src_id = stoi(s.substr(1));
            if (s[0] == 'I') {
                input_targets[src_id].push_back(i);
            } else if (s[0] == 'O') {
                gates[src_id].target_gates.push_back(i);
            }
        }
    }

    int S;
    cin >> S;

    // 预备空间：存储这 S 次的所有输入矩阵，避免遇到 LOOP 提前退出时截断输入流
    vector<vector<int>> all_inputs(S, vector<int>(M + 1));
    vector<vector<int>> all_queries(S);

    for (int i = 0; i < S; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> all_inputs[i][j];
        }}
        
 for(int i=0;i<S;++i)
        {
        int si;
        cin >> si;
        all_queries[i].resize(si);
        for (int j = 0; j < si; ++j) {
            cin >> all_queries[i][j];
        }
    }

    // 💥 第一阶段：全局拓扑环路检测 (只需要测一次物理结构)
    vector<int> in_degree(N + 1);
    for (int i = 1; i <= N; ++i) {
        in_degree[i] = gates[i].in_degree_max;
    }
    
    queue<int> topo_q;
    // 假设所有的输入(I)都已经准备好，剔除这部分的入度
    for (int i = 1; i <= M; ++i) {
        for (int target : input_targets[i]) {
            in_degree[target]--;
            if (in_degree[target] == 0) {
                topo_q.push(target);
            }
        }
    }
    
    int processed_gates = 0;
    // 有些门可能没有任何输入，或者输入全来自其他入度为0的门，必须先将它们入队
    for (int i = 1; i <= N; ++i) {
        if (in_degree[i] == 0) {
            topo_q.push(i);
        }
    }

    vector<int> topo_order; // 保存绝对的运算顺序，后续加速
    while (!topo_q.empty()) {
        int u = topo_q.front();
        topo_q.pop();
        processed_gates++;
        topo_order.push_back(u);

        for (int v : gates[u].target_gates) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                topo_q.push(v);
            }
        }
    }

    // 拓扑审判：如果没有处理完所有器件，绝对存在环路
    if (processed_gates < N) {
        cout << "LOOP\n";
        return; 
    }

    // 💥 第二阶段：S 次并行或串行运转 (复用安全的拓扑顺序)
    for (int s = 0; s < S; ++s) {
        vector<int> gate_outputs(N + 1, -1);
        vector<vector<int>> received_inputs(N + 1);

        // 1. 注入源头势能 (M个输入)
        for (int i = 1; i <= M; ++i) {
            int val = all_inputs[s][i];
            for (int target : input_targets[i]) {
                received_inputs[target].push_back(val);
            }
        }

        // 2. 按照绝对安全的拓扑顺序点火
        for (int u : topo_order) {
            // 所有入度均已到达，瞬间收敛出结果
            gate_outputs[u] = execute_gate(gates[u].type, received_inputs[u]);
            
            // 将结果投递给下游
            for (int v : gates[u].target_gates) {
                received_inputs[v].push_back(gate_outputs[u]);
            }
        }

        // 3. 终端清算
        for (size_t i = 0; i < all_queries[s].size(); ++i) {
            cout << gate_outputs[all_queries[s][i]] << (i + 1 == all_queries[s].size() ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    if (cin >> Q) {
        while (Q--) {
            solve();
        }
    }
    return 0;
>>>>>>> e3718e7119451d180d0fc9eee75a2b96fa2e0eb4
}