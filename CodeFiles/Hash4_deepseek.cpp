#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> table(N);
    vector<vector<int>> graph; // 图：graph[i] 存储依赖于元素i的其他元素索引
    vector<int> inDegree;      // 入度数组
    vector<int> elements;      // 存储所有非负元素值
    vector<int> posToElement;  // 从位置映射到元素值（如果没有元素，则为-1）
    vector<int> elementToPos;  // 从元素值映射到实际位置

    // 读取输入
    for (int i = 0; i < N; i++) {
        cin >> table[i];
        if (table[i] >= 0) {
            elements.push_back(table[i]);
        }
    }

    // 初始化图和入度
    int numElements = elements.size();
    graph.resize(numElements);
    inDegree.assign(numElements, 0);
    sort(elements.begin(), elements.end()); // 排序以便映射
    posToElement.assign(N, -1);
    elementToPos.assign(elements.back() + 1, -1); // 假设元素值不会太大

    // 构建映射：从元素值到索引（在elements中的位置）和从位置到元素值
    for (int i = 0; i < N; i++) {
        if (table[i] >= 0) {
            posToElement[i] = table[i];
            auto it = lower_bound(elements.begin(), elements.end(), table[i]);
            int idx = it - elements.begin();
            elementToPos[table[i]] = i;
        }
    }

    // 构建依赖图
    for (int i = 0; i < N; i++) {
        if (table[i] < 0) continue;
        int v = table[i];
        int p = v % N; // 理想位置
        if (p == i) {
            // 没有依赖，入度为0
            continue;
        }
        // 遍历探测路径：从p到i-1（循环）
        int cur = p;
        while (cur != i) {
            if (table[cur] >= 0) {
                // v依赖于table[cur]
                int u = table[cur];
                auto it_u = lower_bound(elements.begin(), elements.end(), u);
                auto it_v = lower_bound(elements.begin(), elements.end(), v);
                int idx_u = it_u - elements.begin();
                int idx_v = it_v - elements.begin();
                graph[idx_u].push_back(idx_v);
                inDegree[idx_v]++;
            }
            cur = (cur + 1) % N;
        }
    }

    // 拓扑排序：使用最小堆（优先队列）每次选择入度为0的最小元素
    priority_queue<int, vector<int>, greater<int>> pq; // 存储元素在elements中的索引
    for (int i = 0; i < numElements; i++) {
        if (inDegree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> result;
    while (!pq.empty()) {
        int idx = pq.top();
        pq.pop();
        result.push_back(elements[idx]);
        for (int neighbor : graph[idx]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                pq.push(neighbor);
            }
        }
    }

    // 输出结果
    for (int i = 0; i < result.size(); i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;

    return 0;
}