#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

struct User {
    int id;
    vector<int> scores;
    int total = 0;
    int perfect = 0;
    bool shown = false;
};

int main() {
    int N, K, M;
    cin >> N >> K >> M;
    vector<int> full(K + 1);
    for (int i = 1; i <= K; ++i) cin >> full[i];

    vector<User> users(N + 1);
    for (int i = 1; i <= N; ++i) {
        users[i].id = i;
        users[i].scores = vector<int>(K + 1, -2); // -2: never submitted
    }

    for (int i = 0; i < M; ++i) {
        int uid, pid, score;
        cin >> uid >> pid >> score;
        if (score != -1) users[uid].shown = true;
        if (score > users[uid].scores[pid]) users[uid].scores[pid] = score;
    }

    for (int i = 1; i <= N; ++i) {
        int sum = 0, perf = 0;
        for (int j = 1; j <= K; ++j) {
            if (users[i].scores[j] >= 0) sum += users[i].scores[j];
            if (users[i].scores[j] == full[j]) ++perf;
        }
        users[i].total = sum;
        users[i].perfect = perf;
    }

    vector<User> ranklist;
    for (int i = 1; i <= N; ++i)
        if (users[i].shown) ranklist.push_back(users[i]);

    sort(ranklist.begin(), ranklist.end(), [&](const User &a, const User &b) {
        if (a.total != b.total) return a.total > b.total;
        if (a.perfect != b.perfect) return a.perfect > b.perfect;
        return a.id < b.id;
    });

    int rank = 1, prevScore = -1, cnt = 1;
    for (size_t i = 0; i < ranklist.size(); ++i) {
        if (ranklist[i].total != prevScore) rank = cnt;
        printf("%d %05d %d", rank, ranklist[i].id, ranklist[i].total);
        for (int j = 1; j <= K; ++j) {
            if (ranklist[i].scores[j] == -2) printf(" -");
            else if (ranklist[i].scores[j] == -1) printf(" 0");
            else printf(" %d", ranklist[i].scores[j]);
        }
        printf("\n");
        prevScore = ranklist[i].total;
        ++cnt;
    }
    return 0;
}