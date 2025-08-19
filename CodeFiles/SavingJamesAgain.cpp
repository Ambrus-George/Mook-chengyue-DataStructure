#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <limits>

class SavingJamesAgain
{
public:
	SavingJamesAgain(int N, int M) : NumOfCorcodiles(N), JumpDistance(M), diameter(15.0)
	{
		Corcodiles.resize(N, std::vector<int>(2, 0));
		Path.resize(N);
		FirstStepLength.resize(N);
	}
	~SavingJamesAgain() {}

	void readNCorcodiles()
	{
		for (size_t i = 0; i < NumOfCorcodiles; i++)
		{
			int a = 0, b = 0;
			std::cin >> a >> b;

			writeHelper(i, a, b);
		}
	}

	bool checkPath()
	{
		// 在岸上挑选第一条鳄鱼跳上去，选中，即入栈
		// 对于入栈的鳄鱼，顺序访问它的邻接鳄鱼，能跳过去，就入栈
		// 当栈顶的鳄鱼跳不上岸也跳不到别的鳄鱼头上，那这条鳄鱼是条死路，pop
		// 继续循环

		bool flag = false;

		for (size_t i = 0; i < NumOfCorcodiles; i++)
		{
			double xIndex = (double)Corcodiles.at(i).at(0);
			double yIndex = (double)Corcodiles.at(i).at(1);

			double distance = std::sqrt(std::pow(xIndex, 2) + std::pow(yIndex, 2));

			FirstStepLength.at(i) = distance - (diameter / 2);

			if (distance > (diameter / 2 + JumpDistance))
			{
				continue;
			}
			else {
				flag = checkCorcodiles(i);
			}
		}

		return flag;
	}

	bool checkCorcodiles(int item)
	{
		std::stack<int> Stack;

		// 记录当前这个鳄鱼访问到了第几个鳄鱼
		std::vector<int> indexHelper(NumOfCorcodiles, -1);
		
		std::vector<bool> Flag(NumOfCorcodiles, false);
		Stack.push(item);
		Flag.at(item) = true;

		while (!Stack.empty())
		{
			int thisone = Stack.top();

			// 如果前面的跳法一样，但是发现从中途的一只鳄鱼开始跳有多条路线
			// 针对这种情况，程序是判断不出来的
			if (isSafety(thisone))
			{
				break;
			}

			double xIndex = (double)Corcodiles.at(thisone).at(0);
			double yIndex = (double)Corcodiles.at(thisone).at(1);

			int i = indexHelper.at(thisone)+1;
			for (; i < NumOfCorcodiles; i++, indexHelper.at(thisone)++)
			{
				// 已经在路径上的鳄鱼就不访问了
				if (Flag.at(i))
				{
					continue;
				}

				double distance = std::sqrt(std::pow(xIndex - Corcodiles.at(i).at(0), 2) + std::pow(yIndex - Corcodiles.at(i).at(1), 2));

				if (distance > JumpDistance)
				{
					continue;
				}
				else {
					Stack.push(i);
					Flag.at(i) = true;
					indexHelper.at(thisone) = i;
					break;
				}
			}


			// 没有鳄鱼可以跳了，这是条绝路
			if (i == NumOfCorcodiles)
			{
				Flag.at(thisone) = false;
				Stack.pop();
			}
		}

		if (Stack.empty())
		{
			return false;
		}
		else {
			while (!Stack.empty())
			{
				int topOne = Stack.top();
				Path.at(item).push(topOne);
				Stack.pop();
			}

			return true;
		}
	}

	bool isSafety(int item)
	{
		int xIndex = Corcodiles.at(item).at(0);
		int yIndex = Corcodiles.at(item).at(1);

		if ((50 - std::abs(xIndex) <= JumpDistance) || (50 - std::abs(yIndex) <= JumpDistance))
		{
			return true;
		}

		return false;
	}

	void printResult()
	{
		int minSteps = std::numeric_limits<int>::max();
		int finalIndex = 0;
		size_t i = 0;

		for (; i < NumOfCorcodiles; i++)
		{
			// 没有路的鳄鱼和步数多的路排除
			if (Path.at(i).size() == 0 || minSteps < Path.at(i).size())
			{
				continue;
			}

			if (minSteps > Path.at(i).size())
			{
				finalIndex = i;
				minSteps = Path.at(i).size();
			}

			if (minSteps == Path.at(i).size())
			{
				finalIndex = (FirstStepLength.at(finalIndex) < FirstStepLength.at(i)) ? finalIndex : i;
			}
		}

		std::cout << (Path.at(finalIndex).size() + 1) << std::endl;
		while (!Path.at(finalIndex).empty())
		{
			int item = Path.at(finalIndex).top();
			std::cout << Corcodiles.at(item).at(0) << " " << Corcodiles.at(item).at(1) << std::endl;
			Path.at(finalIndex).pop();
		}
	}

private:
	double diameter;
	int NumOfCorcodiles;
	int JumpDistance;
	std::vector<std::vector<int>> Corcodiles;
	std::vector<std::stack<int>> Path;
	std::vector<double> FirstStepLength;

	void writeHelper(int index, int a, int b)
	{
		Corcodiles.at(index).at(0) = a;
		Corcodiles.at(index).at(1) = b;
	}
};



int main()
{
	int N = 0, M = 0;
	std::cin >> N >> M;
	SavingJamesAgain Bond(N, M);

	// 读入鳄鱼的坐标
	Bond.readNCorcodiles();	

	// 判断James能不能逃出去
	bool checkResult = Bond.checkPath();

	// 输出
	if (!checkResult)
	{
		std::cout << "0";
	}
	else {
		Bond.printResult();
	}

	return 0;
}