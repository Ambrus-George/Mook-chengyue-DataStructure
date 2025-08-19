#include <iostream>
#include <vector>
#include <cmath>

typedef long int ElementType;
typedef int IndexType;

void generateSedgewickSequence(std::vector<IndexType>& Q, IndexType N)
{
	Q.clear();
	IndexType k = 0;
	IndexType gap = 0;
	while (true)
	{
		if (k % 2 == 0)
		{
			gap = 9 * (pow(2, k) - pow(2, k / 2)) + 1;
		}
		else
		{
			gap = 8 * pow(2, k) - 6 * pow(2, (k + 1) / 2) + 1;
		}
		if (gap > N) break;
		if (gap > 0)
			Q.push_back(gap);
		k++;
	}
	std::reverse(Q.begin(), Q.end());
	return;
}

int main()
{
	// 读入数据
	int N = 0;
	std::vector<ElementType> Data;						// 用来存放数据
	std::vector<IndexType> SedgewickSequence;			// 用来保存Sedgewick序列
	std::cin >> N;
	if (N)
	{
		Data.resize(N);
		for (auto& item : Data)
		{
			std::cin >> item;
		}
	}

	// 生成Sedgewick序列
	generateSedgewickSequence(SedgewickSequence, N);

	// 希尔排序
	for (auto gap : SedgewickSequence)
	{
		decltype(gap) i, j;
		for (i = gap; i < N; i++)
		{
			auto Tmp = Data.at(i);
			for (j = i; j >= gap && Data.at(j - gap) > Tmp; j -= gap)
			{
				Data.at(j) = Data.at(j - gap);
			}
			Data.at(j) = Tmp;
		}
	}

	// 打印排序结果
	if (true)
	{
		bool printFlag = false;

		for (auto data : Data)
		{
			if (printFlag)
			{
				std::cout << " ";
			}
			std::cout << data;
			printFlag = true;
		}
	}

	return 0;
}