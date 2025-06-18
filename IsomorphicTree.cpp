#include <iostream>
#include <array>

#define MAXSIZE 10
#define NOTFOUND -1

typedef struct Node* PtrToNode;
struct Node {
	int Data;
	int left;
	int right;
};

int heightOfNode(PtrToNode ptr, int data, int length);

int main()
{
	std::array< std::array<struct Node, MAXSIZE + 1>, 2> Trees{ 0 };

	/*std::array<struct Node, MAXSIZE + 1> T1{ 0 };
	std::array<struct Node, MAXSIZE + 1> T2{ 0 };*/

	int numNodes1 = 0, numNodes2 = 0;
	bool isSameTrees = true;

	//1. build the tree1
	//2. build the tree2
	for (int i = 0; i < 2; i++)
	{
		int num = 0;
		char a = ' ', b = ' ', c = ' ';
		std::cin >> num;

		if (i)
		{
			numNodes2 = num;
		}
		else {
			numNodes1 = num;
		}

		for (int j = 0; j < num; j++)
		{
			std::cin >> a >> b >> c;
			int data = a - 'A';
			int left = b - '0';
			if (b == '-')
			{
				left = NOTFOUND;
			}
			int right = c - '0';
			if (c == '-')
			{
				right = NOTFOUND;
			}

			Trees[i][j].Data = data;
			Trees[i][j].left = left;
			Trees[i][j].right = right;
		}
	}


	//3. compare the heights
	if (numNodes1 != numNodes2)
	{
		std::cout << "No";
	}
	else if (!numNodes1)
	{
		std::cout << "Yes";
	}
	else {
		for (int i = 0; i < numNodes1; i++)
		{
			if (heightOfNode(&Trees[0][0] , Trees[0][i].Data, numNodes1)
				!= heightOfNode(&Trees[1][0], Trees[0][i].Data, numNodes1))
			{
				isSameTrees = false;
				break;
			}
		}

		if (isSameTrees)
		{
			std::cout << "Yes";
		}
		else {
			std::cout << "No";
		}
	}

	return 0;
}

int heightOfNode(PtrToNode ptr, int data, int length)
{
	PtrToNode p = ptr;
	int index = -1;
	int height = 1;

	//find the data
	for (int i = 0; i < length; i++)
	{
		if (data == p->Data)
		{
			index = i;
			break;
		}
		p++;
	}

	//notfound the data
	if (index == -1)
	{
		return NOTFOUND;
	}

	//has no children
	if ((p->left == NOTFOUND) && (p->right == NOTFOUND))
	{
		return height;
	}
	else if ((p->left != NOTFOUND) && (p->right != NOTFOUND))
	{
		height += (heightOfNode(ptr, (ptr + p->left)->Data,length) > heightOfNode(ptr, (ptr + p->right)->Data, length)) ? 
					heightOfNode(ptr, (ptr + p->left)->Data, length) : heightOfNode(ptr, (ptr + p->right)->Data, length);
		return height;
	}
	else if ((p->left != NOTFOUND) && (p->right == NOTFOUND))
	{
		return height += heightOfNode(ptr, (ptr + p->left)->Data, length);
	}
	else {
		return height += heightOfNode(ptr, (ptr + p->right)->Data, length);
	}

	
}