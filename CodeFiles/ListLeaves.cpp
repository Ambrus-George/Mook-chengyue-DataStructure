#include <iostream>
#include <array>

#define MAXSIZE 10
#define NOTFOUND -1

typedef struct Node* Tree;

struct Node {
	std::array<std::array<int, 2>, MAXSIZE + 1> Data;
	int index;
};

typedef struct NodeQ *QueueFrame;
struct NodeQ {
	std::array<int, MAXSIZE + 1> Data;
	int index;
};

int FindTheRoot(Tree T);
void PushQueue(QueueFrame Q, int INDEX);
int PopQueue(QueueFrame Q);
bool isLeave(Tree T, int item);

int main()
{
	// 1. Read the input and Build the Tree
	// 2. Find the root
	// 3. Push the root into the queue
	// 4. Using the queue to pop the leaves


	//1
	int N = 0, rootT = 0;
	Tree T = new Node{ 0 };
	QueueFrame Q = new NodeQ{ 0 };
	bool hadPrinted = false;

	std::cin >> N;
	T->index = N - 1;
	for (int i = 0; i < N; i++)
	{
		int left = 0, right = 0;
		char a = ' ', b = ' ';
		std::cin >> a >> b;

		if (a == '-')
		{
			left = NOTFOUND;
		}
		else {
			left = a - '0';
		}

		if (b == '-')
		{
			right = NOTFOUND;
		}
		else {
			right = b - '0';
		}

		T->Data[i][0] = left;
		T->Data[i][1] = right;
	}

	//2
	rootT = FindTheRoot(T);

	//3
	PushQueue(Q, rootT);

	//4
	while (Q->index)
	{
		int itme = PopQueue(Q);
		

		if (isLeave(T, itme))
		{
			if (hadPrinted)
			{
				std::cout << " ";
			}

			std::cout << itme;
			hadPrinted = true;
		}

		PushQueue(Q, T->Data[itme][0]);
		PushQueue(Q, T->Data[itme][1]);
	}

	return 0;
}

bool isLeave(Tree T, int item)
{
	if ((T->Data[item][0] == NOTFOUND) && (T->Data[item][1] == NOTFOUND))
	{
		return true;
	}

	return false;
}


void PushQueue(QueueFrame Q, int INDEX)
{
	if (INDEX == NOTFOUND)
	{
		return;
	}

	Q->Data[++Q->index] = INDEX;
}

int FindTheRoot(Tree T)
{
	std::array<bool, MAXSIZE + 1> arr;
	arr.fill(true);
	for (int i = 0; i < T->index+1; i++)
	{
		if (T->Data[i][0] != NOTFOUND)
		{
			arr[T->Data[i][0]] = false;
		}
		
		if (T->Data[i][1] != NOTFOUND)
		{
			arr[T->Data[i][1]] = false;
		}
		
	}

	for (int i = 0; i < T->index + 1; i++)
	{
		if (arr[i]) {
			return i;
		}
	}
	return NOTFOUND;
}

int PopQueue(QueueFrame Q)
{
	if (!Q->index)
	{
		return NOTFOUND;
	}

	int item = Q->Data[1];

	for (int i = 1; i < Q->index; i++)
	{
		Q->Data[i] = Q->Data[i + 1];
	}

	Q->index--;
	return item;
}