#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

// 计算哈夫曼树的标准WPL
int calcHuffmanWPL(vector<int>& freqs) {
    priority_queue<int, vector<int>, greater<int>> pq; // 最小堆
    for (int f : freqs) {
        pq.push(f);
    }

    int wpl = 0;
    while (pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        int sum = a + b;
        wpl += sum;
        pq.push(sum);
    }
    return wpl;
}

// 检查学生提交的编码是否为有效前缀码
bool isPrefixFree(vector<string>& codes) {
    // 按编码长度排序
    sort(codes.begin(), codes.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
        });

    for (int i = 0; i < codes.size(); i++) {
        for (int j = i + 1; j < codes.size(); j++) {
            // 检查是否有前缀关系
            if (codes[i] == codes[j].substr(0, codes[i].length())) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int N, M;
    cin >> N;

    // 读取字符和频率
    map<char, int> freqMap;
    vector<int> freqs;
    for (int i = 0; i < N; i++) {
        char c;
        int f;
        cin >> c >> f;
        freqMap[c] = f;
        freqs.push_back(f);
    }

    // 计算标准哈夫曼WPL
    int huffmanWPL = calcHuffmanWPL(freqs);

    cin >> M; // 读取学生数量

    // 处理每个学生的提交
    for (int i = 0; i < M; i++) {
        vector<pair<char, string>> submissions;
        vector<string> studentCodes;
        bool validPrefix = true;
        int studentWPL = 0;

        // 读取学生提交的编码
        for (int j = 0; j < N; j++) {
            char c;
            string code;
            cin >> c >> code;
            submissions.push_back({ c, code });
            studentCodes.push_back(code);

            // 计算该编码的WPL贡献
            if (freqMap.find(c) != freqMap.end()) {
                studentWPL += freqMap[c] * code.length();
            }
        }

        // 检查是否为有效前缀码
        validPrefix = isPrefixFree(studentCodes);

        // 验证结果：前缀有效且WPL等于哈夫曼WPL
        if (validPrefix && studentWPL == huffmanWPL) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }

    return 0;
}