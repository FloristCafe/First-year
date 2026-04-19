#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 物理状态定义
enum State {
    UNALLOCATED = 0, // 未分配
    PENDING = 1,     // 待分配
    OCCUPIED = 2,    // 占用
    EXPIRED = 3      // 过期
};

// IP 地址舱
struct IPNode {
    State state;
    string owner;
    long long expire_time;
};

int N;
long long T_def, T_max, T_min;
string H;

vector<IPNode> ip_pool;

// 💥 引擎组件 1：时空同步探针
// 在处理任何报文前，强制将系统时间快进到 t，并触发所有因时间流逝导致的状态坍缩
void update_time(long long current_time) {
    for (int i = 1; i <= N; ++i) {
        if (ip_pool[i].expire_time > 0 && ip_pool[i].expire_time <= current_time) {
            if (ip_pool[i].state == PENDING) {
                ip_pool[i].state = UNALLOCATED;
                ip_pool[i].owner = "";
                ip_pool[i].expire_time = 0;
            } else if (ip_pool[i].state == OCCUPIED) {
                ip_pool[i].state = EXPIRED;
                ip_pool[i].expire_time = 0;
            }
        }
    }
}

// 💥 引擎组件 2：过期时间物理钳制
long long calculate_expire(long long current_time, long long req_expire) {
    long long exp = req_expire;
    if (exp == 0) {
        exp = current_time + T_def;
    }
    
    // 强制截断在上下限之间
    long long limit_min = current_time + T_min;
    long long limit_max = current_time + T_max;
    
    if (exp < limit_min) exp = limit_min;
    if (exp > limit_max) exp = limit_max;
    
    return exp;
}

// 💥 引擎组件 3：系统广播发射器
void send_packet(string receive_host, string type, int ip, long long expire) {
    cout << H << " " << receive_host << " " << type << " " << ip << " " << expire << "\n";
}

int main() {
    // 拔除 I/O 物理限速
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> N >> T_def >> T_max >> T_min >> H)) return 0;

    ip_pool.assign(N + 1, {UNALLOCATED, "", 0});

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        long long t;
        string sender, receiver, type;
        int req_ip;
        long long req_expire;

        cin >> t >> sender >> receiver >> type >> req_ip >> req_expire;

        // 绝对纪律：先同步时间！
        update_time(t);

        // 1. 判断接收主机
        if (receiver != H && receiver != "*") {
            if (type != "REQ") continue;
        }

        // 2. 判断报文类型
        if (type != "DIS" && type != "REQ") continue;

        // 3. 判断组合合法性
        if ((receiver == "*" && type != "DIS") || (receiver == H && type == "DIS")) continue;

        if (type == "DIS") {
            int selected_ip = 0;

            // 规则 a: 寻找曾占用的
            for (int j = 1; j <= N; ++j) {
                if (ip_pool[j].owner == sender) {
                    selected_ip = j;
                    break;
                }
            }

            // 规则 b: 寻找最小未分配
            if (selected_ip == 0) {
                for (int j = 1; j <= N; ++j) {
                    if (ip_pool[j].state == UNALLOCATED) {
                        selected_ip = j;
                        break;
                    }
                }
            }

            // 规则 c: 寻找最小过期
            if (selected_ip == 0) {
                for (int j = 1; j <= N; ++j) {
                    if (ip_pool[j].state == EXPIRED) {
                        selected_ip = j;
                        break;
                    }
                }
            }

            // 若均无，处理结束
            if (selected_ip == 0) continue;

            // 分配并锁定
            ip_pool[selected_ip].state = PENDING;
            ip_pool[selected_ip].owner = sender;
            ip_pool[selected_ip].expire_time = calculate_expire(t, req_expire);

            send_packet(sender, "OFR", selected_ip, ip_pool[selected_ip].expire_time);

        } else if (type == "REQ") {
            if (receiver != H) {
                // 客户端选择了其它服务器，清理本服务器为其预留的资源
                for (int j = 1; j <= N; ++j) {
                    if (ip_pool[j].owner == sender && ip_pool[j].state == PENDING) {
                        ip_pool[j].state = UNALLOCATED;
                        ip_pool[j].owner = "";
                        ip_pool[j].expire_time = 0;
                    }
                }
                continue; // 处理结束
            }

            // 客户端选择了本服务器
            if (req_ip >= 1 && req_ip <= N && ip_pool[req_ip].owner == sender) {
                ip_pool[req_ip].state = OCCUPIED;
                ip_pool[req_ip].expire_time = calculate_expire(t, req_expire);
                send_packet(sender, "ACK", req_ip, ip_pool[req_ip].expire_time);
            } else {
                send_packet(sender, "NAK", req_ip, 0);
            }
        }
    }

    return 0;
}
