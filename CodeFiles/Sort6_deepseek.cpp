#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    // 记录每个数字的位置
    unordered_map<int, int> num_pos;
    int zero_pos = -1;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        // 记录0的位置
        if (nums[i] == 0) {
            zero_pos = i;
        }
        // 记录每个非0数字的位置
        else {
            num_pos[nums[i]] = i;
        }
    }

    int swaps = 0;
    int idx = 1;  // 用于0在0位置时查找错位位置的起始索引

    while (true) {
        if (zero_pos != 0) {
            // 0不在0位置时：使当前0位置对应的数字归位
            int target = zero_pos;  // 0所在位置应该放置的数字
            int target_pos = num_pos[target];  // 目标数字当前所在位置

            // 交换0和目标数字
            swap(nums[zero_pos], nums[target_pos]);
            swaps++;

            // 更新位置记录
            num_pos[target] = zero_pos;  // 目标数字已归位
            zero_pos = target_pos;  // 更新0的新位置
        }
        else {
            // 0已归位时：查找第一个错位的位置
            bool found = false;
            while (idx < n) {
                if (nums[idx] != idx) {
                    // 交换0和错位数字
                    swap(nums[0], nums[idx]);
                    swaps++;

                    // 更新位置记录
                    num_pos[nums[0]] = 0;   // 将0位置上的数字记录到位置0
                    zero_pos = idx;         // 更新0的新位置
                    idx++;                  // 下次从这个位置之后开始查找
                    found = true;
                    break;
                }
                idx++;
            }
            // 已完全有序，退出循环
            if (!found) break;
        }
    }

    cout << swaps << endl;
    return 0;
}