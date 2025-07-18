#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>

#define MAXSIZE 55

typedef int ElementType;

typedef struct QNode* PtrToNode;
struct QNode {
	ElementType element;
	PtrToNode Next;
	QNode(ElementType e) : element(e), Next(nullptr) {}
};

bool printFlag = false;
int DFSLevel = 0;

class Quence
{
public:
	Quence() : root(nullptr) {}
	~Quence() {}

	bool isEmpty()
	{
		return !root;
	}

	PtrToNode newNode(ElementType item)
	{
		PtrToNode ptr = new QNode(item);
		return ptr;
	}

	void enQuence(ElementType item)
	{
		PtrToNode ptr = root;
		PtrToNode parentPtr = nullptr;
		PtrToNode itemptr = newNode(item);

		if (!root)
		{
			root = itemptr;
			return;
		}

		while (ptr)
		{
			parentPtr = ptr;
			ptr = ptr->Next;
		}

		parentPtr->Next = itemptr;
	}

	PtrToNode popQuence()
	{
		if (isEmpty())
		{
			return nullptr;
		}

		PtrToNode item = root;
		root = item->Next;
		return item;
	}

private:
	PtrToNode root;
};


class Graph
{
public:
	Graph(int m) : totalNum{ m }
	{
		std::fill(Data.begin(), Data.end(), 0);
		std::fill(Flag.begin(), Flag.end(), false);
	}
	~Graph() {}

	void ReSetFlag()
	{
		std::fill(Flag.begin(), Flag.end(), false);
	}

	void readInput(int m)
	{
		for (int i = 0; i < m; i++)
		{
			ElementType a = 0, b = 0;
			std::cin >> a >> b;
			insertEdge(a, b);
		}
		
	}

	void insertEdge(ElementType a, ElementType b)
	{
		insertHelper(a, b);
	}

	int whichLine(int a)
	{
		int i = 0;

		for (; a > (i * (i + 1) / 2 + i); i++) 
		{
		
		}

		return i;
	}

	void BFS(int root, Quence& Q)
	{
		// 对第一个结点访问并输出
		int c = root;

		if (!Flag[c])
		{
			std::cout << "{ " << c;
			printFlag = true;
			Flag[c] = true;
		}
		else {
			return;
		}
		
		/*int i = ((int)pow(c, 2) + c) / 2 + c;
		i += (c + 1);*/

		// 第一个结点入队列
		Q.enQuence(c);

		// 队列不空就抛出来，入队列的一定是经过访问的，抛出来的访问它的邻接结点然后再压入队列

		while (!Q.isEmpty())
		{
			PtrToNode ptr = Q.popQuence();
			int c1 = ptr->element;
			delete(ptr);


			int i = ((int)pow(c1, 2) + c1) / 2 + c1;
			i += (c1 + 1);

			for (; i < (totalNum * (totalNum + 1) / 2); i += (c1 + 1))
			{
				c1 = whichLine(i);


				if (Data[i])
				{
					if (!Flag[c1])
					{
						std::cout << " " << c1;
						printFlag = true;
						Flag[c1] = true;
						Q.enQuence(c1);
					}
				}
			}
		}

		if (printFlag)
		{
			std::cout << " }" << std::endl;
			printFlag = false;
		}
	}

	void DFS(int root)
	{
		DFSLevel++;
		int c = root;
		int i = ((int)pow(c, 2) + c) / 2 + c;
		i += (c + 1);

		if (!Flag[c])
		{
			
			if (!printFlag && (DFSLevel == 1))
			{
				std::cout << "{";
			}
			std::cout << " " << c;
			printFlag = true;
			
			Flag[c] = true;
		}


		for (; i < (totalNum * (totalNum + 1) / 2); i += (c + 1))
		{
			c = whichLine(i);
			

			if (Data[i])
			{
				DFS(c);
			}
		}

		if (printFlag && (DFSLevel == 1))
		{
			std::cout << " }" << std::endl;
			printFlag = false;
		}

		DFSLevel--;
	}

	int Length()
	{
		return totalNum;
	}

private:
	std::array<ElementType, MAXSIZE> Data;
	std::array<bool, MAXSIZE> Flag;
	int totalNum;

	void insertHelper(ElementType a, ElementType b)
	{
		int c = a;
		int v = b;

		if (b > a)
		{
			c = b;
			v = a;
		}

		int index = c * (c + 1) / 2 + v;
		Data[index] = 1;
	}
};

int main()
{
	int n = 0, m = 0;
	std::cin >> n >> m;
	Graph G(n);
	Quence Q;

	G.readInput(m);

	for (int i = 0; i < G.Length(); i++)
	{
		G.DFS(i);
	}

	G.ReSetFlag();

	for (int i = 0; i < G.Length(); i++)
	{
		G.BFS(i, Q);
	}

	return 0;
}