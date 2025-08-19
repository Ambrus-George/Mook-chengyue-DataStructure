#include <iostream>
#include <string>
#include <array>
#include <limits>

#define MAXSIZE 63

typedef char ElementType;
typedef int UsingFrenqency;

typedef struct TNode* PtrToTreeNode;
typedef PtrToTreeNode HuffmanTree;
struct TNode {
	ElementType Ch;
	UsingFrenqency UF;
	int depthNode;
	PtrToTreeNode Left;
	PtrToTreeNode Right;
	TNode(ElementType c, UsingFrenqency f) : Ch(c), UF(f), depthNode(0), Left(nullptr), Right(nullptr) {}
};

class MinHeap
{
public:
	// 默认构造函数
	MinHeap() : index(0) {
		setMinZero();
	}

	// 复制构造函数
	MinHeap(const MinHeap& other) : index(other.index) {
		// 深拷贝哨兵节点
		Data[0] = new TNode(' ', other.Data[0]->UF);

		// 深拷贝其他节点
		for (int i = 1; i <= index; i++) {
			if (other.Data[i]) {
				Data[i] = new TNode(*other.Data[i]);
			}
			else {
				Data[i] = nullptr;
			}
		}
	}

	// 复制赋值运算符
	MinHeap& operator=(const MinHeap& other) {
		if (this != &other) {
			clear();
			delete Data[0];

			index = other.index;
			Data[0] = new TNode(' ', other.Data[0]->UF);

			for (int i = 1; i <= index; i++) {
				if (other.Data[i]) {
					Data[i] = new TNode(*other.Data[i]);
				}
				else {
					Data[i] = nullptr;
				}
			}
		}
		return *this;
	}

	// 移动构造函数（C++11+）
	MinHeap(MinHeap&& other) noexcept
		: index(other.index), Data() {
		// 转移哨兵节点
		Data[0] = other.Data[0];
		other.Data[0] = nullptr;

		// 转移其他节点
		for (int i = 1; i <= index; i++) {
			Data[i] = other.Data[i];
			other.Data[i] = nullptr;
		}
		other.index = 0;
	}

	// 移动赋值运算符（C++11+）
	MinHeap& operator=(MinHeap&& other) noexcept {
		if (this != &other) {
			clear();
			delete Data[0];

			index = other.index;
			Data[0] = other.Data[0];
			other.Data[0] = nullptr;

			for (int i = 1; i <= index; i++) {
				Data[i] = other.Data[i];
				other.Data[i] = nullptr;
			}
			other.index = 0;
		}
		return *this;
	}

	// 析构函数
	~MinHeap() {
		clear();
		delete Data[0]; // 清理哨兵节点
	}

	PtrToTreeNode findElement(ElementType ch)
	{
		PtrToTreeNode item = nullptr;
		for (int i = 0; i <= index; i++)
		{
			if (ch == Data[i]->Ch) {
				item = Data[i];
				break;
			}
		}

		return item;
	}

	void insert(ElementType ch, UsingFrenqency uf)
	{
		insertHelper(ch, uf);
	}

	void insertPtr(PtrToTreeNode newnode)
	{
		insertPtrHelper(newnode);
	}

	bool isEmpty()
	{
		return (index == 0);
	}

	bool haveOneNode()
	{
		return (index == 1);
	}

	PtrToTreeNode deleteMin()
	{
		return deleteMinHelper();
	}

private:
	PtrToTreeNode Data[2 * MAXSIZE];
	int index;

	void insertPtrHelper(PtrToTreeNode newnode)
	{
		int i = ++index;

		for (; Data[i / 2]->UF > newnode->UF; i /= 2)
		{
			Data[i] = Data[i / 2];
		}

		Data[i] = newnode;
	}

	void insertHelper(ElementType ch, UsingFrenqency uf)
	{
		PtrToTreeNode item = new TNode(ch, uf);
		int i = ++index;

		for (; Data[i/2]->UF > uf; i /= 2)
		{
			Data[i] = Data[i / 2];
		}

		Data[i] = item;
	}

	void clear()
	{
		for (int i = 1; i <= index; i++)
		{
			delete Data[i];
		}
	}

	void setMinZero()
	{
		PtrToTreeNode item = new TNode( ' ', std::numeric_limits<int>::min());
		Data[0] = item;
	}

	PtrToTreeNode deleteMinHelper()
	{
		int parent = 0, child = 0;
		PtrToTreeNode minNode = nullptr;
		PtrToTreeNode item = nullptr;

		if (isEmpty())
		{
			return nullptr;
		}

		minNode = Data[1];
		item = Data[index--];
		for (parent = 1; parent *2 <= index; parent = child)
		{
			child = parent * 2;

			// choose the smaller child 
			if (((child + 1) <= index) && (Data[child]->UF > Data[child + 1]->UF))
			{
				child++;
			}

			// find the right index
			if (item->UF < Data[child]->UF)
			{
				break;
			}
			// now Data[1] save the last ptr(original) ,percolate down the item
			else {
				Data[parent] = Data[child];
			}

		}

		Data[parent] = item;

		return minNode;
	}
};


class Huffman
{
public:
	Huffman() : HT(nullptr) {}
	~Huffman()
	{
		destoryTree(HT);
	}

	PtrToTreeNode findElement(ElementType c)
	{
		PtrToTreeNode item = findHelper(c, HT);
		return item;
	}

	void writeFrenquence(MinHeap Fix)
	{
		PtrToTreeNode item = HT;
		writeFrenquenceHelper(Fix, item);
		countNodesDepth(HT, 0);
	}

	void buildFromMinHeap(MinHeap& MH)
	{
		buildFromMinHeapHelper(MH);
	}

	void countNodesDepth(HuffmanTree T, int depth)
	{
		countNodesDepthHelper(T, 0);
	}

	int WPLHuffTree()
	{
		int count = countWPLHelper(HT);
		return count;
	}

	bool buildFromString(char c, std::string str)
	{
		bool flag = buildFromStringHelper(c, str);
		return flag;
	}

	bool haveChild(HuffmanTree T)
	{
		return (T->Left || T->Right);
	}

private:
	HuffmanTree HT;

	PtrToTreeNode findHelper(ElementType c, PtrToTreeNode T)
	{
		PtrToTreeNode item = nullptr;

		if (c == T->Ch)
		{
			item = T;
			return item;
		}

		if (T->Left)
		{
			item = findHelper(c, T->Left);
		}

		if (T->Right)
		{
			item = findHelper(c, T->Right);
		}

		return item;
	}

	void writeFrenquenceHelper(MinHeap Fix, PtrToTreeNode item)
	{
		if (!item)
		{
			return;
		}

		if (item->Ch != '-')
		{
			PtrToTreeNode fixnode = Fix.findElement(item->Ch);
			item->UF = fixnode->UF;
		}

		writeFrenquenceHelper(Fix, item->Left);
		writeFrenquenceHelper(Fix, item->Right);
		return;
	}

	void destoryTree(HuffmanTree H)
	{
		if (!H)
		{
			return;
		}

		destoryTree(H->Left);
		destoryTree(H->Right);
		delete H;
	}

	bool insertNode(char c, HuffmanTree& T)
	{
		if (!T)
		{
			T = newNodePtr(c, 0);
			return true;
		}

		if ((T->depthNode == 1) && (c != '-'))
		{
			return false;
		}

		if ((c != '-') && haveChild(T))
		{
			return false;
		}

		return true;
		
	}

	bool buildFromStringHelper(char c, std::string str)
	{
		if (!HT)
		{
			HT = newNodePtr('-', 0);
			HT->depthNode = 1;
		}
		PtrToTreeNode item = HT;
		bool flag = true;
		char ch = '-';

		for (int i = 0; i < str.length(); i++)
		{
			if (!flag)
			{
				return flag;
			}

			if (i == (str.length() - 1))
			{
				ch = c;
			}

			switch (str[i])
			{
			case '0':
				flag = insertNode(ch, item->Left);
				item->Left->depthNode = 1;
				item = item->Left;
				break;

			case '1':
				flag = insertNode(ch, item->Right);
				item->Right->depthNode = 1;
				item = item->Right;
				break;

			default:
				break;
			}
		}

		return flag;
	}

	PtrToTreeNode newNodePtr(ElementType c, UsingFrenqency f)
	{
		PtrToTreeNode newPtr = new TNode(c, f);
		return newPtr;
	}

	void countNodesDepthHelper(HuffmanTree T, int depth)
	{
		if (!T)
		{
			return;
		}

		T->depthNode = depth;
		countNodesDepthHelper(T->Left, depth + 1);
		countNodesDepthHelper(T->Right, depth + 1);
	}

	void buildFromMinHeapHelper(MinHeap& MH)
	{
		while (!MH.isEmpty())
		{
			// N = 1
			if (MH.haveOneNode())
			{
				HT = MH.deleteMin();
				break;
			}

			PtrToTreeNode item1 = MH.deleteMin();
			PtrToTreeNode item2 = MH.deleteMin();

			// combine two min nodes and insert the DataGroup
			ElementType c = '-';
			UsingFrenqency f = item1->UF + item2->UF;
			PtrToTreeNode combineNode = new TNode(c, f);
			combineNode->Left = item1;
			combineNode->Right = item2;

			MH.insertPtr(combineNode);
		}

		countNodesDepth(HT, 0);
	}

	int countWPLHelper(HuffmanTree T)
	{
		if (!T)
		{
			return 0;
		}

		int leftCount = countWPLHelper(T->Left);
		int rightCount = countWPLHelper(T->Right);
		int thisCount = 0;

		if (T->Ch == '-')
		{
			thisCount = 0;
		}
		else {
			thisCount = T->depthNode * T->UF;
			/*std::cout << T->Ch << "的WPL是 " << thisCount << "已经加上了" << std::endl;*/
		}

		return (thisCount + leftCount + rightCount);
	}
};

int main()
{
	int N = 0, WPL = 0, StudentsNum = 0;
	MinHeap MH;
	Huffman Huff;

	// Read the Data and Build the MinHeap
	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		char c = ' ';
		int f = 0;
		std::cin >> c >> f;
		MH.insert(c, f);
	}

	MinHeap originalHeap = MH;

	// Build the HuffmanTree according to the MinHeap
	Huff.buildFromMinHeap(MH);

	// Count the WPL of the HuffManTree
	WPL = Huff.WPLHuffTree();

	// Read the StudentsNum
	std::cin >> StudentsNum;

	for (int i = 0; i < StudentsNum; i++)
	{
		bool rightAnswer = true;
		Huffman StudentHuffTree;
		for (int j = 0; j < N; j++)
		{	
			char c = ' ';
			std::string str = " ";
			std::cin >> c >> str;

			if (rightAnswer)
			{
				rightAnswer = StudentHuffTree.buildFromString(c, str);
				
			}
			
		}

		StudentHuffTree.writeFrenquence(originalHeap);

		int SWPL = StudentHuffTree.WPLHuffTree();

		if (rightAnswer)
		{
			rightAnswer = (SWPL <= WPL);
		}
		

		if (rightAnswer)
		{
			std::cout << "Yes" << std::endl;
		}
		else {
			std::cout << "No" << std::endl;
		}
	}

	return 0;
}