#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class QQManagement {
private:
    struct Node {
        bool Occupied = false;
        bool Deleted = false;
        long long Key = 0;
        std::string Account;
        std::string Password;
    };

    int N = 0;
    int K = 1;
    int Hash_size;
    float Stock_factor = 0;
    std::vector<Node> Data;

public:
    QQManagement() {
        Hash_size = 4 * K + 3;
        while (!IsPrime(Hash_size)) {
            K++;
            Hash_size = 4 * K + 3;
        }
        Data.resize(Hash_size);
    }

    // 高效的哈希函数
    long long getHashKey(const std::string& str) {
        long long hash = 0;
        for (char c : str) {
            hash = hash * 131 + c;
        }
        return hash;
    }

    // 检查质数
    bool IsPrime(int n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }

    // 优化的平方探测
    int findPosition(const std::vector<Node>& data, long long key) {
        int size = data.size();
        int pos = key % size;
        int count = 0;
        
        while (data[pos].Occupied && !data[pos].Deleted && data[pos].Key != key) {
            count++;
            pos = (key + count * count) % size;
        }
        
        return pos;
    }

    void loginAccount(const std::string& account, const std::string& password) {
        long long key = getHashKey(account);
        int position = findPosition(Data, key);

        if (!Data[position].Occupied || Data[position].Key != key) {
            std::cout << "ERROR: Not Exist" << std::endl;
            return;
        }
        
        if (Data[position].Password == password) {
            std::cout << "Login: OK" << std::endl;
        } else {
            std::cout << "ERROR: Wrong PW" << std::endl;
        }
    }

    void expandData() {
        int newK = K * 2;
        int newSize = 4 * newK + 3;
        while (!IsPrime(newSize)) {
            newK++;
            newSize = 4 * newK + 3;
        }
        
        std::vector<Node> newData(newSize);
        
        for (const auto& node : Data) {
            if (node.Occupied && !node.Deleted) {
                long long key = node.Key;
                int pos = key % newSize;
                int count = 0;
                
                while (newData[pos].Occupied) {
                    count++;
                    pos = (key + count * count) % newSize;
                }
                
                newData[pos] = node;
            }
        }
        
        K = newK;
        Hash_size = newSize;
        Data = std::move(newData);
        Stock_factor = static_cast<float>(N) / Hash_size;
    }

    void registerAccount(const std::string& account, const std::string& password) {
        long long key = getHashKey(account);
        int position = findPosition(Data, key);

        if (Data[position].Occupied && !Data[position].Deleted && Data[position].Key == key) {
            std::cout << "ERROR: Exist" << std::endl;
            return;
        }

        Data[position].Account = account;
        Data[position].Deleted = false;
        Data[position].Key = key;
        Data[position].Occupied = true;
        Data[position].Password = password;

        N++;
        Stock_factor = static_cast<float>(N) / Hash_size;

        if (Stock_factor > 0.5) {
            expandData();
        }

        std::cout << "New: OK" << std::endl;
    }
};

int main() {
    int N;
    std::cin >> N;
    QQManagement HashTable;

    for (int i = 0; i < N; i++) {
        char ch;
        std::cin >> ch;

        if (ch == 'L') {
            std::string str1, str2;
            std::cin >> str1 >> str2;
            HashTable.loginAccount(str1, str2);
        } else if (ch == 'N') {
            std::string str1, str2;
            std::cin >> str1 >> str2;
            HashTable.registerAccount(str1, str2);
        }
    }

    return 0;
}
