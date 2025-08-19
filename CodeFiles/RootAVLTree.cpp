#include <iostream>
#include <array>

#define MAXSIZE 20

typedef int ElementType;
typedef struct TreeNode* PtrToNode;
typedef PtrToNode Tree;
struct TreeNode {
	ElementType data;
	int height;
	PtrToNode Left;
	PtrToNode Right;
	TreeNode(ElementType x) : data(x), height(1), Left(nullptr), Right(nullptr) {}
};

class BinaryBalenceTree
{
public:
	BinaryBalenceTree() : root(nullptr) {}
	~BinaryBalenceTree() {
		destroyTree(root);
	}

	// Get the ptr to root
	PtrToNode getRoot()
	{
		return root;
	}

	// Read N numbers and insert Nodes
	void readInsert(int N)
	{
		for (int i = 0; i < N; i++)
		{
			ElementType item = 0;
			std::cin >> item;
			insertNewNode(item);
			
		}
	}

	void insertNewNode(ElementType item)
	{
		root = insertNewNodeHelper(root, item);
	}



	int balenceFactor(PtrToNode node)
	{
		int BF = 0;
		BF = heightNode(node->Left) - heightNode(node->Right);
		return BF;
	}

private:
	Tree root;

	void destroyTree(Tree node) {
		if (node)
		{
			destroyTree(node->Left);
			destroyTree(node->Right);
			delete node;
		}
	}

	PtrToNode LLRevert(PtrToNode P)
	{
		PtrToNode originalRoot = P;
		P = originalRoot->Left;
		originalRoot->Left = P->Right;
		P->Right = originalRoot;

		updateHeight(P->Right);
		updateHeight(P);
		return P;
	}

	PtrToNode LRRevert(PtrToNode P)
	{
		PtrToNode originalR = P;
		P = originalR->Left->Right;
		originalR->Left->Right = P->Left;
		P->Left = originalR->Left;
		originalR->Left = P->Right;
		P->Right = originalR;

		updateHeight(P->Left);
		updateHeight(P->Right);
		updateHeight(P);

		return P;
	}

	PtrToNode RLRevert(PtrToNode P)
	{
		PtrToNode originalR = P;
		P = originalR->Right->Left;
		originalR->Right->Left = P->Right;
		P->Right = originalR->Right;
		originalR->Right = P->Left;
		P->Left = originalR;
		
		updateHeight(P->Right);
		updateHeight(P->Left);
		updateHeight(P);

		return P;
	}

	PtrToNode RRRevert(PtrToNode P)
	{
		PtrToNode originalR = P;
		P = originalR->Right;
		originalR->Right = P->Left;
		P->Left = originalR;

		updateHeight(P->Left);
		updateHeight(P);

		return P;
	}

	PtrToNode insertNewNodeHelper(PtrToNode P, ElementType key)
	{
		PtrToNode newNode = new TreeNode(key);

		if (!P)
		{
			return newNode;
		}

		if (key > P->data)
		{
			P->Right = insertNewNodeHelper(P->Right, key);
		}
		else {
			P->Left = insertNewNodeHelper(P->Left, key);
		}

		updateHeight(P);

		int BF = balenceFactor(P);


		// LL-Revert
		if (BF > 1 && key < P->Left->data)
		{
			return LLRevert(P);
		}

		// LR-Revert
		if (BF > 1 && key > P->Left->data)
		{
			return LRRevert(P);
		}

		// RR-Revert
		if (BF < -1 && key > P->Right->data)
		{
			return RRRevert(P);
		}

		// RL-Revert
		if (BF < -1 && key < P->Right->data)
		{
			return RLRevert(P);
		}

		return P;
	}

	void updateHeight(PtrToNode node)
	{
		if (node)
		{
			node->height = 1 + std::max(heightNode(node->Left), heightNode(node->Right));
		}
		
	}

	int heightNode(PtrToNode node)
	{
		return (node) ? node->height : 0;
	}
};

int main()
{
	BinaryBalenceTree BBT;
	int N = 0;
	std::cin >> N;
	if (N)
	{
		BBT.readInsert(N);
	}

	std::cout << BBT.getRoot()->data;

	return 0;
}