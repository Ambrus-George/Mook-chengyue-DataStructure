#include <iostream>
#include <vector>
#include <limits>

typedef struct Node* PtrToNode;
struct Node
{
	int edgeWeight;
	int vertex_1;
	int vertex_2;
	Node(int weight, int v1, int v2) : edgeWeight(weight), vertex_1(v1), vertex_2(v2) {}
};

class MinHeap
{
public:
	MinHeap() {}
	~MinHeap()
	{
		for (int i = 0; i <= size; ++i)
		{
			delete heap.at(i);
		}
	}

	void init(int capacity)
	{
		size = 0;
		heap.resize(capacity + 1, nullptr);	// 实际上最小堆从1开始存储
		heap.at(0) = new Node(0, -1, -1);	// 0号位放一个绝对小的值
	}

	void insert(PtrToNode newptr)
	{
		insertHelper(newptr);
	}

	PtrToNode top()
	{
		return heap.at(1);
	}

	void deleteMin()
	{
		deleteHelper();
	}

	bool isEmpty()
	{
		return (size == 0);
	}

private:
	int size;
	std::vector<PtrToNode> heap;

	void insertHelper(PtrToNode newptr)
	{
		size++;
		size_t index = size;

		for (; newptr->edgeWeight < heap.at(index/2)->edgeWeight; 
				index /= 2)
		{
			heap.at(index) = heap.at(index / 2);
		}

		heap.at(index) = newptr;
	}

	void deleteHelper()		// 删除最小值，本质上是假装最后的一个值在初始位，然后更新这条路径上的值
	{
		if (isEmpty())
		{
			return;
		}

		delete heap.at(1);
		heap.at(1) = nullptr;

		size_t parent = 1;
		size_t child = 0;
		for (; parent*2 <= size; parent = child)
		{
			
			child = parent * 2;

			// 选择两个子节点权重较小的那个
			if (child + 1 <= size &&
				heap.at(child + 1)->edgeWeight < heap.at(child)->edgeWeight)
			{
				child++;
			}

			// 找到合适的位置，退出循环
			if (heap.at(size)->edgeWeight < heap.at(child)->edgeWeight)
			{
				break;
			}

			heap.at(parent) = heap.at(child);
		}

		heap.at(parent) = heap.at(size);
		size--;
	}
};

class VillagesRoads
{
public:
	VillagesRoads(int villagenum, int roadnum);
	~VillagesRoads() {}
	void init();
	void printMinCost();
	int findRoot(int m);
	bool merge(int x, int y);

private:
	int villagesNum;
	int roadsNum;
	MinHeap heap;
	std::vector<int> parent;
};

bool VillagesRoads::merge(int x, int y)
{
	int root_x = findRoot(x);
	int root_y = findRoot(y);

	if (root_x == root_y)
	{
		return false;
	}

	parent.at(root_x) = root_y;
	return true;
}

int VillagesRoads::findRoot(int m)
{
	if (parent.at(m) != m)
	{
		parent.at(m) = findRoot(parent.at(m));
	}

	return parent.at(m);
}

void VillagesRoads::printMinCost()
{
	if (roadsNum < villagesNum - 1)
	{
		std::cout << "-1";
		return;
	}

	int count = 0;			// 记录从最小堆中抛出了多少条边
	int workload = 0;		// 抛出边的时候更新工作量

	while (count < (villagesNum - 1) && !heap.isEmpty())
	{
		auto item = heap.top();

		// 如果是一个树，将构成回路，那就不要这条边了
		int root1 = findRoot(item->vertex_1);
		int root2 = findRoot(item->vertex_2);
		if (root1 != root2)
		{
			count++;
			merge(root1, root2);
			workload += item->edgeWeight;
		}

		heap.deleteMin();
	}

	if (count < (villagesNum - 1))
	{
		std::cout << "-1";
	}
	else
	{
		std::cout << workload;
	}
}

void VillagesRoads::init()
{
	for (size_t i = 0; i < roadsNum; i++)
	{
		int weight = 0, v1 = 0, v2 = 0;
		std::cin >> v1 >> v2 >> weight;

		PtrToNode item = new Node(weight, v1, v2);
		heap.insert(item);
	}
}

VillagesRoads::VillagesRoads(int villagenum, int roadnum)
{
	villagesNum = villagenum;
	roadsNum = roadnum;
	parent.resize(villagenum + 1);
	for (size_t i = 0; i < parent.size(); i++)
	{
		parent.at(i) = (int)i;
	}
	heap.init(roadnum);
}

int main()
{
	int villagenum = 0;
	int roadsnum = 0;
	std::cin >> villagenum >> roadsnum;
	VillagesRoads CountrysidePlan(villagenum, roadsnum);

	// 初始话对象，读入计划的道路信息
	CountrysidePlan.init();

	CountrysidePlan.printMinCost();
}