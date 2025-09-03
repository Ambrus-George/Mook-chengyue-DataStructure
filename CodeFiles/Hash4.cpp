#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

typedef struct Node* PtrToNode;
struct Node
{
	bool Visited;
	int element;
	int key;
	int difference;
	int index;
	PtrToNode Next;
	Node() : Visited(false), element(-1), index(0),
		Next(nullptr),key(0), difference(std::numeric_limits<int>::max()) {}
};

void InsertPtr(std::vector<PtrToNode>& G, Node& item)
{
	PtrToNode itemPtr = &item;
	item.Next = G.at(item.key);
	G.at(item.key) = itemPtr;
}

int main()
{
	int N;
	std::cin >> N;						//
	std::vector<Node> Data(N);			// 存储原始数据，需要固定不动
	std::vector<PtrToNode> MinDiff;		// 下标和取余结果的差值，能反应输入顺序
	std::vector<PtrToNode> Graph(N);	// 邻接表

	int count = 0;						// 计数器，统计一共有多少个成员需要输出

	if (N)
	{
		// 读入数据，建立需要的数据结构
		for (int i = 0; i < N; i++)
		{
			int item;
			std::cin >> item;
			Data.at(i).element = item;
			if (item < 0)
			{
				Data.at(i).key = -1;
				Data.at(i).difference = std::numeric_limits<int>::max();
				Data.at(i).index = i;
			}
			else
			{
				Data.at(i).key = item % N;
				Data.at(i).difference = i - Data.at(i).key;
				Data.at(i).index = i;
				if (Data.at(i).difference < 0)
				{
					Data.at(i).difference += N;
				}

				MinDiff.push_back(&Data.at(i));			// 排序数组，按照输出规则来排序
				InsertPtr(Graph, Data.at(i));			// 邻接表

				count++;
			}
			 
		}

		// 开始处理然后一个个输出
		bool printFlag = false;
		while (count)
		{
			std::sort(MinDiff.begin(), MinDiff.end(), [](PtrToNode a, PtrToNode b) {
				if (a->difference == b->difference)
				{
					return a->element < b->element;
				}
				else {
					return a->difference < b->difference;
				}
				});

			PtrToNode minptr = MinDiff.at(0);
			if (printFlag)	std::cout << " ";
			std::cout << minptr->element;
			printFlag = true;
			minptr->difference = std::numeric_limits<int>::max();
			minptr->Visited = true;
			count--;

			// 需要变换其他结点的差值数据
			// 1.根据邻接表来减1
			PtrToNode itemPtr = Graph.at(minptr->key);
			while (itemPtr)
			{
				if (!itemPtr->Visited)
				{
					itemPtr->difference--;
				}
				itemPtr = itemPtr->Next;
			}

			// 2.顺序地减1
			int beginIndex = minptr->index + 1;
			if (beginIndex >= N)		beginIndex = 0;
			while (Data.at(beginIndex).difference && Data.at(beginIndex).difference != std::numeric_limits<int>::max())
			{
				Data.at(beginIndex).difference--;
				beginIndex++;
				if (beginIndex >= N)		beginIndex = 0;
			}


		}
	}


	return 0;
}