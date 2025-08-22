#include <bits/stdc++.h>
using namespace std;

/*
  思路（0 作中转站）：
  - 维护 pos[x] = 数字 x 当前所在的位置。
  - 如果 0 不在位置 0：把应该放在 zero_pos 的数字（就是值 = zero_pos）
    和 0 交换，这一步会“就位”一个元素。
  - 如果 0 在位置 0：把 0 和任意一个还没就位的元素交换，
    让 0 进入某个环中，再按上一步循环消环。
*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    vector<int> pos(N);
    for (int i = 0; i < N; ++i) pos[a[i]] = i;

    long long swaps = 0;
    int p = 1; // 指向下一个“未就位”的位置（跳过已就位的，整体只前进，不会退，保证 O(N)）
    auto advance_p = [&]() {
        while (p < N && a[p] == p) ++p;
        };

    while (true) {
        if (pos[0] == 0) {              // 0 在原位，需要把 0 拉进某个未就位的环
            advance_p();
            if (p >= N) break;          // 全部就位，结束
            int v = a[p];               // 位置 p 上的值
            swap(a[0], a[p]);           // Swap(0, v)
            pos[0] = p;
            pos[v] = 0;
            ++swaps;
        }
        else {                        // 0 不在原位，修正 zero_pos 处的元素
            int zero_pos = pos[0];      // 0 当前所在的位置
            int target_val = zero_pos;  // 这个位置应该放的值就是 zero_pos
            int target_pos = pos[target_val]; // 这个值现在在哪
            swap(a[zero_pos], a[target_pos]); // 把 target_val 放回去，同时移动 0
            pos[0] = target_pos;
            pos[target_val] = zero_pos;
            ++swaps;
        }
    }

    cout << swaps << '\n';
    return 0;
}
