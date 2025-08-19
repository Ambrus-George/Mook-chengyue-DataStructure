#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <stack>

typedef struct Node *PtrToNode;
struct Node {
	int x;					// 鳄鱼坐标
	int y;
	bool canJump;			// 是否靠近中心岛
	bool isSafe;			// 是否靠近岸边
	Node(int x, int y, bool c, bool s) : x(x), y(y), canJump(c), isSafe(s) {}
};

class SavingJamesAgain
{
public:
	SavingJamesAgain(int N, int M) : NumOfCorcodiles(N), StepLength(M), diameter(15.0)
	{
		Corcodiles.resize(N, nullptr);
		Pre.resize(N, -1);
		Dist.resize(N, std::numeric_limits<int>::max());
		Connection.resize(N, std::vector<bool>(N, false));
		Visited.resize(N, false);
	}
	~SavingJamesAgain()
	{
		for (size_t i = 0; i < NumOfCorcodiles; i++)
		{
			delete(Corcodiles.at(i));
		}
	}

	bool canJump(int x, int y)																	
	{
		double distance = std::sqrt(std::pow((double)x, 2) + std::pow((double)y, 2));
		return ((diameter / 2 + StepLength) > distance);
	}

	bool isSafe(int x, int y)
	{
		return (((StepLength + std::abs(x)) >= 50) || ((StepLength + std::abs(y)) >= 50));
	}

	bool isConnected(int x, int y, int m, int n)
	{
		double distace = std::pow((double)x - (double)m, 2) + std::pow((double)y - (double)n, 2);
		return distace <= std::pow(StepLength, 2);
	}

	void initData()
	{
		// 读入数据
		for (size_t i = 0; i < NumOfCorcodiles; i++)
		{
			int x = 0, y = 0;
			std::cin >> x >> y;
			bool c = canJump(x, y);
			bool s = isSafe(x, y);

			Corcodiles.at(i) = new Node(x, y, c, s);
		}

		// 两条鳄鱼之间可以跳过去
		for (size_t i = 0; i < NumOfCorcodiles; i++)
		{
			for (size_t j = 0; j < NumOfCorcodiles; j++)
			{
				Connection.at(i).at(j) = isConnected(Corcodiles.at(i)->x, Corcodiles.at(i)->y, Corcodiles.at(j)->x, Corcodiles.at(j)->y);
			}
		}

	}

	void Dijkstra(int item)
	{
		Dist.at(item) = 0;

		while (true)
		{
			int nextItem = -1;
			int min = std::numeric_limits<int>::max();

			for (size_t i = 0; i < NumOfCorcodiles; i++)
			{
				if (!Visited.at(i) && (Dist.at(i) < min))
				{
					nextItem = i;
					min = Dist.at(i);
				}
			}

			if (nextItem == -1)	return;
			Visited.at(nextItem) = true;

			for (size_t i = 0; i < NumOfCorcodiles; i++)
			{
				if (!Visited.at(i) && Connection.at(nextItem).at(i) && ((Dist.at(nextItem) + 1) < Dist.at(i)))
				{
					Dist.at(i) = Dist.at(nextItem) + 1;
					Pre.at(i) = nextItem;
				}
			}
		}
	}

	bool comp(int a, int b)    // 返回 a 点比 b 点更靠近中心岛
	{
		double dis_a = std::pow(Corcodiles.at(a)->x, 2) + std::pow(Corcodiles.at(a)->y, 2);
		double dis_b = std::pow(Corcodiles.at(b)->x, 2) + std::pow(Corcodiles.at(b)->y, 2);

		return dis_a < dis_b;
	}

	void printPath(int starIndex, int endIndex, std::vector<int>& path)
	{
		std::stack<int> S;

		while (endIndex != starIndex)
		{
			S.push(endIndex);
			endIndex = path.at(endIndex);
		}

		S.push(starIndex);

		while (!S.empty())
		{
			int item = S.top();
			std::cout << Corcodiles.at(item)->x << " " << Corcodiles.at(item)->y << std::endl;
			S.pop();
		}
	}

	void saving007()
	{
		// 可以从中心岛直接上岸
		if (((diameter / 2) + StepLength) >= 50.0)
		{
			std::cout << "1";
			return;
		}

		int starAdd = -1;								// 最短路径的值  // 起点
		int endAdd = -1;												 // 终点
		int minDist = std::numeric_limits<int>::max();					 // 最小步数
		std::vector<int> Path(NumOfCorcodiles, -1);						 // 路径

		for (size_t i = 0; i < NumOfCorcodiles; i++)
		{
			if (Corcodiles.at(i)->canJump)														// 找最短路径的起点
			{
				std::fill(Pre.begin(), Pre.end(), -1);
				std::fill(Dist.begin(), Dist.end(), std::numeric_limits<int>::max());
				std::fill(Visited.begin(), Visited.end(), false);

				Dijkstra(i);

				for (size_t j = 0; j < NumOfCorcodiles; j++)
				{
					if (Corcodiles.at(j)->isSafe && minDist > Dist.at(j))						// 找对应起点的终点
					{
						starAdd = i;
						endAdd = j;
						minDist = Dist.at(j);
						Path = Pre;
					}
					else if (Corcodiles.at(j)->isSafe && Dist.at(j) !=std::numeric_limits<int>::max() && minDist == Dist.at(j) && comp(i, starAdd))
					{
						starAdd = i;
						endAdd = j;
						minDist = Dist.at(j);
						Path = Pre;
					}
				}
			}
		}


		if (minDist == std::numeric_limits<int>::max())
		{
			std::cout << "0";
		}
		else {
			std::cout << minDist + 2 << std::endl;
			printPath(starAdd, endAdd, Path);
		}
	}


private:
	double diameter;
	int NumOfCorcodiles;						// 鳄鱼数量
	int StepLength;								// Bond能跳多远
	std::vector<PtrToNode> Corcodiles;			// 鳄鱼坐标数据
	std::vector<std::vector<bool>> Connection;	// 鳄鱼之间是否能跳过去

	std::vector<int> Pre;						// 上岸路径
	std::vector<int> Dist;						// 每条鳄鱼的最短跳跃长度
	std::vector<bool>Visited;					// 鳄鱼有没有被访问过
};

int main()
{
	int N = 0, M = 0;
	std::cin >> N >> M;
	SavingJamesAgain Bond(N, M);

	Bond.initData();

	Bond.saving007();

	return 0;
}