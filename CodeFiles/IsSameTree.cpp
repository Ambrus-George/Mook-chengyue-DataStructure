#include <iostream>
#include <array>

#define MAXSIZE 10

typedef int ElementType;

typedef struct TNode* PtrToNode;
typedef PtrToNode Tree;
struct TNode {
	ElementType Data;
	PtrToNode Left;
	PtrToNode Right;
	bool traveled;
	TNode(ElementType x) : Data(x), Left(nullptr), Right(nullptr), traveled(false) {}
};

class Stack
{
public:
	Stack() : index(0) {}

	void push(PtrToNode p)
	{
		index++;
		DataGroup[index] = p;
	}

	PtrToNode pop()
	{
		PtrToNode p = DataGroup[index];
		index--;
		return p;
	}

	bool isEmpty()
	{
		return !index;
	}

private:
	std::array<PtrToNode, MAXSIZE + 1> DataGroup;
	int index;
};

class BinarySearchTree
{
public:
	BinarySearchTree() : root(nullptr) {}

	void insertNode(ElementType x)
	{
		PtrToNode newnode = new TNode(x);
		
		if (!root)
		{
			root = newnode;
			return;
		}

		PtrToNode currentPtr = root;
		PtrToNode parentPtr = nullptr;

		while (currentPtr)
		{
			parentPtr = currentPtr;
			if (x < currentPtr->Data)
			{
				currentPtr = currentPtr->Left;
			}
			else  {
				currentPtr = currentPtr->Right;
			}
		}

		if (x < parentPtr->Data)
		{
			parentPtr->Left = newnode;
		}
		else {
			parentPtr->Right = newnode;
		}
	}

	bool equalTree(ElementType x)
	{
		PtrToNode p = root;

		if (!p)
		{
			return false;
		}

		while (p)
		{

			if (x == p->Data)
			{
				if (!p->traveled)
				{
					p->traveled = true;
					return true;
				}
				else {
					return false;
				}
			}
			else {
				if (p->traveled)
				{
					if (x > p->Data) {
						p = p->Right;
					}

					if (x < p->Data) {
						p = p->Left;
					}
				}
				else {
					return false;
				}
			}

			

		}

		return false;
	}

	void reSetTravelFlag()
	{
		PtrToNode p = root;
		Stack stackTree;

		while (p || !stackTree.isEmpty())
		{
			while (p) {
				stackTree.push(p);
				p->traveled = false;
				p = p->Left;
			}

			if (!stackTree.isEmpty())
			{
				p = stackTree.pop();
				p = p->Right;
			}
		}
		
	}

private:
	PtrToNode root;
};





int main()
{
	bool noEndFlag = true;

	while (true)
	{
		bool printFlag = true;
		int N = -1, L = 0;
		std::cin >> N;
		if (!N)
		{
			break;
		}
		std::cin >> L;

		BinarySearchTree T;

		for (int i = 0; i < N; i++)
		{
			int item = 0;
			std::cin >> item;
			T.insertNode(item);
		}

	
		for (int i = 0; i < L; i++)
		{
			for (int j = 0; j < N; j++)
			{
				int item = 0;
				std::cin >> item;

				if (printFlag)
				{
					printFlag = T.equalTree(item);
				}
				
			}

			if (printFlag)
			{
				std::cout << "Yes" << std::endl;
			}
			else {
				std::cout << "No" << std::endl;
			}

			printFlag = true;
			T.reSetTravelFlag();
		}

	}

	return 0;
}