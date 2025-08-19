#include <iostream>
#include <vector>
#include <limits>
#include <queue>

class HerryPotterExam
{
public:
	HerryPotterExam() : NumOfAnimals(0) {}
	HerryPotterExam(int n) : NumOfAnimals(n)
	{
		Data.resize(n + 1, std::vector<int>(n + 1, std::numeric_limits<int>::max()));
		Dist.resize(n + 1, std::vector<int>(n + 1, std::numeric_limits<int>::max()));
		Path.resize(n + 1, std::vector<int>(n + 1, -1));
	}
	~HerryPotterExam() {}


	void getEdge(int row, int col, int length)
	{
		addEdgeHelper(row, col, length);
	}

	void Floyd()
	{
		for (size_t i = 1; i <= NumOfAnimals; i++)
		{
			for (size_t j = 1; j <= NumOfAnimals; j++)
			{
				Dist.at(i).at(j) = Data.at(i).at(j);
			}
		}


		for (size_t k = 1; k <= NumOfAnimals; k++)
		{
			for (size_t i = 1; i <= NumOfAnimals; i++)
			{
				for (size_t j = 1; j <= NumOfAnimals; j++) 
				{
					if (i == j)
					{
						continue;
					}

					if (Dist.at(i).at(k) > std::numeric_limits<int>::max() - Dist.at(k).at(j))
					{
						// 表示这里会溢出
						continue;
					}
					else if (Dist.at(i).at(k) + Dist.at(k).at(j) < Dist.at(i).at(j))
					{
						Dist.at(i).at(j) = Dist.at(i).at(k) + Dist.at(k).at(j);
						Path.at(i).at(j) = k;
					}
				}
			}
		}
	}

	int findBestAnimal()
	{
		int animalV = 0;
		int max = std::numeric_limits<int>::max();

		for (size_t i = 1; i <= NumOfAnimals; i++)
		{
			int thisMax = getLongestNum(i);

			if (max > thisMax)
			{
				max = thisMax;
				animalV = i;
			}
		}

		return animalV;
	}

	int getLongestNum(int animal)
	{
		int longestStr = 0;

		for (size_t i = 0; i <= NumOfAnimals; i++)
		{
			if (Dist.at(animal).at(i) == std::numeric_limits<int>::max())
			{
				continue;
			}

			longestStr = (longestStr > Dist.at(animal).at(i)) ? longestStr : Dist.at(animal).at(i);
		}

		return longestStr;
	}

	bool hasOneGroup()
	{
		std::vector<bool> Flag(NumOfAnimals + 1, false);
		std::queue<int> Que;

		Que.push(1);
		Flag.at(1) = true;

		while (!Que.empty())
		{
			int item = Que.front();
			Que.pop();

			for (size_t i = 1; i <= NumOfAnimals; i++)
			{
				if (Data.at(item).at(i) == std::numeric_limits<int>::max())
				{
					continue;
				}

				if ((Data.at(item).at(i) > 0) && !Flag.at(i))
				{
					Flag.at(i) = true;
					Que.push(i);
				}
			}
		}

		for (size_t i = 1; i <= NumOfAnimals; i++)
		{
			if (!Flag.at(i)) {
				return false;
			}
		}

		return true;
	}

private:
	int NumOfAnimals;
	std::vector<std::vector<int>> Data;
	std::vector<std::vector<int>> Dist;
	std::vector<std::vector<int>> Path;

	void addEdgeHelper(int row, int col, int length)
	{
		Data.at(row).at(col) = length;
		Data.at(col).at(row) = length;
	}
};

int main()
{
	int n = 0, m = 0;
	std::cin >> n >> m;

	HerryPotterExam Herry(n);

	// 读入边
	for (size_t i = 0; i < m; i++)
	{
		int row = 0, col = 0, length = 0;
		std::cin >> row >> col >> length;
		Herry.getEdge(row, col, length);
	}

	// 使用 Floyd 算法，搞定 i, j 的最短路径问题
	Herry.Floyd();

	// 找到最合适的动物
	// 找到最长的变形咒语
	if (Herry.hasOneGroup())
	{
		int bestAnimal = Herry.findBestAnimal();
		int longestNum = Herry.getLongestNum(bestAnimal);
		std::cout << bestAnimal << " " << longestNum;
	}
	else {
		std::cout << "0";
	}


	return 0;
}