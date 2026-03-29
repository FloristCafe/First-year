# 极速图论引擎：Dijkstra (优先队列优化)

## 1. 物理组件
* **时间复杂度：** O((V + E) log V)
* **核心数据结构：** `priority_queue` (小根堆), `std::vector<pair<int, int>>` (邻接表)
* **适用战区：** 单源最短路径，**绝对禁止负权边**。

## 2. 战术备忘录 (防爆指南)
* **堆的定义绝对法则：** 必须使用 `greater<pair<int, int>>` 实现小根堆。并且 `pair` 的 `first` **必须是距离**，因为默认按 first 排序！
* **历史废料清除：** 弹出的节点必须经过 `if (d > dist[u]) continue;` 判定，极其重要，否则会引发 TLE (超时)。
* **初始锚点：** 永远别忘了 `dist[S] = 0` 和 `pq.push({0, S})`。

## 3. 实战源码
* 核心实现见本目录下的 `dijkstra.cpp`。