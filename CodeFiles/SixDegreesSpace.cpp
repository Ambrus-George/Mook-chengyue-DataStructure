#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>

typedef struct Node *PtrToNode;
struct Node
{
	int character;
	PtrToNode Next;
	Node(int item) : character(item), Next(nullptr) {}
};

PtrToNode aNewNode(int a)
{
	PtrToNode item = new Node(a);
	return item;
}

class SixDSpace
{
public:
	SixDSpace(int N) : NumOfMembers(N)
	{
		Visited.resize(N, 0);
		List.resize(N, nullptr);
	}
	~SixDSpace()
	{
		for (int i = 0; i < NumOfMembers; i++)
		{
			/* code */
			PtrToNode ptr = List.at(i);
			while (ptr)
			{
				PtrToNode item = ptr;
				ptr = ptr->Next;
				delete(item);
			}
			
		}
		
	}


	void readEdges(int M)
	{
		for (int i = 0; i < M; i++)
		{
			/* 读入M条边 */
			int a = 0, b = 0;
			std::cin >> a >> b;
			PtrToNode aPtr = aNewNode(a);
			PtrToNode bPtr = aNewNode(b);

			/* 由于是无向图，一条边需要建立两个结点，存储两次 */
			insertHelper(a - 1, bPtr);
			insertHelper(b - 1, aPtr);
		}
		
	}

	int countNum(int a)
	{
		// 计算每个结点有多少结点符合六度空间理论
		Visited.at(a) = 1;
		std::queue<int> Que;
		Que.push(a);

		while (!Que.empty())
		{
			/* Queue is not empty */
			int item = Que.front();
			Que.pop();
			int visitedCount = Visited.at(item);


			PtrToNode ptr = List.at(item);
			// 
			for (; ptr != nullptr; ptr = ptr->Next)
			{
				/* code */
				int i = ptr->character - 1;

				if (!Visited.at(i))
				{
					/* code */
					Visited.at(i) = visitedCount + 1;

					Que.push(i);
				}
				
			}
			
		}
		
		// 已经计算了对于结点 a 的连通集
		int countOfNum = 0;
		for (int i = 0; i < NumOfMembers; i++)
		{
			/* code */
			if (Visited.at(i) && Visited.at(i) < 8)
			{
				/* code */
				countOfNum++;
			}
			
		}


		return countOfNum;
		
	}

	void printCountNum(int countNum)
	{
		double item = (double)countNum / NumOfMembers * 100;
		std::cout << std::fixed << std::setprecision(2) << item << "%" << std::endl;
	}

	void retVisitedGroup()
	{
		resetHelper();
	}

private:
	int NumOfMembers;
	std::vector<int> Visited;
	std::vector<PtrToNode> List;

	void insertHelper(int a, PtrToNode ptr)
	{
		PtrToNode item = List.at(a);
		List.at(a) = ptr;
		ptr->Next = item;
	}

	void resetHelper()
	{
		std::fill(Visited.begin(), Visited.end(), 0);
	}
};

int main()
{
	int N = 0, M = 0;
	std::cin >> N >> M;
	SixDSpace SDS(N);

	// 读入M条边
	SDS.readEdges(M);

	// 输出
	for (int i = 0; i < N; i++)
	{
		/* 对每个结点计算他们符合六度空间理论的节点数 */
		int countNum = SDS.countNum(i);

		/* 输出 */

		std::cout << i+1 << ": ";
		SDS.printCountNum(countNum);

		SDS.retVisitedGroup();
	}
	
	return 0;
}