#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

// 物理实体：缓存行 (Cache Line)
struct CacheLine {
    long long address; // 内存块物理地址
    bool is_dirty;     // 脏标记：是否被修改过
};

// 物理实体：组相联的一个独立组 (Set)
struct CacheSet {
    long long capacity; // 本组能容纳的最大行数 (n)
    
    // LRU 核心引擎：链表前端表示最近使用，末尾表示最久未使用
    list<CacheLine> lru_queue; 
    
    // 极速雷达：地址映射到链表节点的迭代器
    unordered_map<long long, list<CacheLine>::iterator> locator;
    
    CacheSet(long long cap) : capacity(cap) {}
    
    void process(int op, long long addr) {
        auto it = locator.find(addr);
        
        if (it != locator.end()) {
            // 💥 命中 (Cache Hit)
            
            // 1. 提取出这块数据
            CacheLine line = *(it->second);
            
            // 2. 如果是写操作，数据变脏
            if (op == 1) {
                line.is_dirty = true;
            }
            
            // 3. LRU 物理更新：把它从原位置抹杀，强行提拔到队列最前端
            lru_queue.erase(it->second);
            lru_queue.push_front(line);
            locator[addr] = lru_queue.begin(); // 更新雷达指针
            
        } else {
            // 💥 未命中 (Cache Miss)
            
            // 1. 只要未命中，CPU 必须立刻从主存拉取数据！
            cout << "0 " << addr << "\n";
            
            // 2. 检查空间是否爆满，执行替换策略
            if (lru_queue.size() == capacity) {
                // 锁定最久未使用的那个倒霉蛋（队尾元素）
                CacheLine victim = lru_queue.back();
                
                // 如果它是个脏数据，必须先写回主存！
                if (victim.is_dirty) {
                    cout << "1 " << victim.address << "\n";
                }
                
                // 物理抹杀：清除出队列，并销毁雷达坐标
                locator.erase(victim.address);
                lru_queue.pop_back();
            }
            
            // 3. 构造新的缓存行并插入到最前端
            CacheLine new_line;
            new_line.address = addr;
            new_line.is_dirty = (op == 1); // 如果当前指令是写，拉进来立刻变脏
            
            lru_queue.push_front(new_line);
            locator[addr] = lru_queue.begin(); // 记录雷达坐标
        }
    }
};

int main() {
    // 解除 I/O 物理封锁，应对海量指令
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, N, q;
    if (!(cin >> n >> N >> q)) return 0;

    // 预先分配 N 个绝对物理隔离的组宇宙
    // 注意：用指针或智能指针避免 vector 扩容带来的链表失效灾难
    vector<CacheSet*> cache_sets(N);
    for (int i = 0; i < N; ++i) {
        cache_sets[i] = new CacheSet(n);
    }

    for (int i = 0; i < q; ++i) {
        int op;
        long long addr;
        cin >> op >> addr;
        
        // 绝对算力指引：计算它属于哪个组
        long long group_id = (addr / n) % N;
        
        // 将指令投递给对应的组独立处理
        cache_sets[group_id]->process(op, addr);
    }

    // 清理战场
    for (int i = 0; i < N; ++i) {
        delete cache_sets[i];
    }

    return 0;
}