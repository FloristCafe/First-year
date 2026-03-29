// 全局必须有专门的初始化函数或循环：
// for(int i=1; i<=n; i++) { parent[i] = i; weight[i] = 0; }

int find(int x) {
    if (parent[x] == x) {
        return x; // 抵达绝对根节点
    }
    
    int old_parent = parent[x]; // 缓存旧的历史锚点
    
    // 递归：让旧父亲先去找到绝对根节点，并完成它自己的路径压缩
    parent[x] = find(parent[x]); 
    
    // 向量折叠：x 到根的向量 = x 到旧父亲的向量 + 旧父亲到根的向量
    // 绝对禁止在这里写 weight[x] = ...！必须是 += ！
    weight[x] += weight[old_parent]; 
    
    return parent[x]; // 绝对不能漏掉的 return！
}

void merge(int x, int y, int v) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
        // 你的高光时刻，绝对正确的代数推演：
        weight[rootX] = v - weight[x] + weight[y];
    }
}