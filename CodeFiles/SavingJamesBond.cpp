#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>

class SavingJames
{
public:
	SavingJames(int N, int D) : JumpDistance(D), Num(0)
	{
		Position.at(0) = 0;
		Position.at(1) = 0;
		CrocodilesP.resize(N);
		Visited.resize(N, false);
	}
	~SavingJames() {}

	// 读入鳄鱼的坐标
	void ReadCrocodiles(int N)
	{
		for (int i = 0; i < N; i++)
		{
			int x = 0, y = 0;
			std::cin >> x >> y;
			writeHelper(x, y);
		}
	}

	// 判断是不是第一步，从岸上跳
	bool IsFirstStep()
	{
		return ((Position.at(0) == 0) && (Position.at(1) == 0));
	}

	bool IsSafe()
	{
		int a = 50 - std::abs(Position.at(0));
		int b = 50 - std::abs(Position.at(1));

		return ((a <= JumpDistance) || (b <= JumpDistance));
	}

	bool DFS(int root)
	{
		int originalPosition0 = Position.at(0);
		int originalPosition1 = Position.at(1);

		bool result = false;

		// 路径上已经访问过的直接返回false
		if (Visited.at(root))
		{
			return false;
		}

		// 看能不能跳得过来
		// 是从岸上跳的第一步
		if (IsFirstStep())
		{
			/*std::cout << "James Bond 从岸上准备跳了" << std::endl;*/

			long double distance = sqrt(pow(CrocodilesP.at(root).at(0), 2) + pow(CrocodilesP.at(root).at(1), 2));
			if (distance > (long double)JumpDistance + 7.5)
			{

				/*std::cout << CrocodilesP.at(root).at(0) << "---" << CrocodilesP.at(root).at(1) << "这只鳄鱼跳不上去,距离原点  " << distance << std::endl;*/

				return false;
			}
			else {

				/*std::cout << CrocodilesP.at(root).at(0) << "---" << CrocodilesP.at(root).at(1) << "现在跳到这只鳄鱼身上了,距离原点  " << distance << std::endl;*/

				Visited.at(root) = true;
				Position.at(0) = CrocodilesP.at(root).at(0);
				Position.at(1) = CrocodilesP.at(root).at(1);
			}
		}
		// 从一只鳄鱼头上跳到另一个鳄鱼头上
		else {
			long double distance = sqrt(pow(CrocodilesP.at(root).at(0) - Position.at(0), 2) + pow(CrocodilesP.at(root).at(1) - Position.at(1), 2));
			if (distance > (long double)JumpDistance)
			{
				/*std::cout << CrocodilesP.at(root).at(0) << "---" << CrocodilesP.at(root).at(1) << "这只鳄鱼跳不上去，距离" << Position.at(0) 
					<< Position.at(1)  << "    " << distance << std::endl;*/

				return false;
			}
			else {

				/*std::cout << CrocodilesP.at(root).at(0) << "---" << CrocodilesP.at(root).at(1) << "现在跳到这只鳄鱼身上了，距离" << Position.at(0)
					<< Position.at(1) << "    " << distance << std::endl;*/

				Visited.at(root) = true;
				Position.at(0) = CrocodilesP.at(root).at(0);
				Position.at(1) = CrocodilesP.at(root).at(1);
			}
		}
		// 好了，现在跳过来了
		Visited.at(root) = true;
		// 检查从当前这里能不能直接上岸
		if (IsSafe())
		{
			/*std::cout << CrocodilesP.at(root).at(0) << "---" << CrocodilesP.at(root).at(1) << "可以上岸了" << std::endl;*/

			return true;
		}
		else {
			for (int i = 0; i < Num; i++)
			{
				// 不知道是不是邻接点，所以遍历全部的点
				if (!Visited.at(i))
				{
					result = DFS(i);
					if (result)
					{
						break;
					}
				}
			}
		}

		// 如果跳到当前点上后续没有合适的路了，那就证明这个点也不该跳，回去刚刚的位置，然后这个点需要重置访问状态
		if (!result)
		{
			Position.at(0) = originalPosition0;
			Position.at(1) = originalPosition1;
			Visited.at(root) = false;
		}

		return result;
	}

	void EscapeCheck()
	{
		bool f = false;

		for (int i = 0; i < Num; i++)
		{
			f = DFS(i);

			if (f)
			{
				break;
			}
			
			std::fill(Visited.begin(), Visited.end(), false);
		}

		if (f)
		{
			std::cout << "Yes";
		}
		else {
			std::cout << "No";
		}
	}

private:
	std::array<int, 2> Position;
	int JumpDistance;
	int Num;
	std::vector<std::array<int, 2>> CrocodilesP;
	std::vector<bool> Visited;

	void writeHelper(int x, int y)
	{
		CrocodilesP.at(Num).at(0) = x;
		CrocodilesP.at(Num).at(1) = y;
		Num++;
	}
};

int main()
{
	int N = 0, D = 0;
	std::cin >> N >> D;
	SavingJames Bond(N, D);

	// 读入鳄鱼的坐标
	Bond.ReadCrocodiles(N);
	
	// 看看能不能上岸
	Bond.EscapeCheck();

	return 0;
}