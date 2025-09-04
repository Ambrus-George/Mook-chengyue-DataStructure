#include <iostream>
#include <vector>
#include <string>


class KMP {
private:
    std::vector<std::vector<int>> dp;
    std::string pat;

public:
    KMP(const std::string& pat) {
        this->pat = pat;
        int M = pat.length();
        dp = std::vector<std::vector<int>>(M, std::vector<int>(256, 0));
        dp[0][(unsigned char)pat[0]] = 1;
        int X = 0;
        for (int j = 1; j < M; j++) {
            for (int c = 0; c < 256; c++)
                dp[j][c] = dp[X][c];
            dp[j][(unsigned char)pat[j]] = j + 1;
            X = dp[X][(unsigned char)pat[j]];
        }
    }

    int search(const std::string& txt) {
        int M = pat.length();
        int N = txt.length();
        int j = 0;
        for (int i = 0; i < N; i++) {
            j = dp[j][(unsigned char)txt[i]];
            if (j == M) return i - M + 1;
        }
        return -1;
    }

    void printRestChar(const std::string& txt)
    {
        int i = this->search(txt);
        if (i != -1)
        {
            for (; i < txt.size(); i++)
            {
                std::cout << txt.at(i);
            }
        }
        else
        {
            std::cout << "Not Found";
        }
        
        std::cout << std::endl;
    }
};

int main()
{
    std::string txt;
    std::cin >> txt;

    int N;
    std::cin >> N;

    if (N)
    {
        for (int i = 0; i < N; i++)
        {
            std::string pat;
            std::cin >> pat;
            KMP kmp(pat);
            kmp.printRestChar(txt);
        }
    }


    return 0;
}


