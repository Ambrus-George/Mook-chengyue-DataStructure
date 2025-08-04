#include <iostream>
#include <limits>
#include <vector>


typedef struct Node* PtrToNode;
struct Node
{
	int length;
	int charge;
	Node(int len, int ch) : length(len), charge(ch) {}
};


class TravelMenu
{
public:
	TravelMenu(int numcities);
	~TravelMenu();

	void readEdges(int num);
	void checkPath(int scity, int ecity);

private:
	int NumCities;										// 城市数量
	std::vector<std::vector<PtrToNode>> Data;			// 城市公路即高速费
	/*std::vector<int> Path;*/							// 题目不需要打印最短路径
	std::vector<int> Dist;								// 
	std::vector<int> Payment;							// 
	std::vector<bool> Visited;							// 是否访问过的标志位

	void insertEdgeHelper(int c1, int c2, int len, int pay);
	void Dijkstra(int startCity);
};

TravelMenu::TravelMenu(int numcities) : NumCities(numcities)
{
	Data.resize(numcities, std::vector<PtrToNode>(numcities, nullptr));
	Dist.resize(numcities, std::numeric_limits<int>::max());
	Payment.resize(numcities, std::numeric_limits<int>::max());
	Visited.resize(numcities, false);
}

TravelMenu::~TravelMenu()
{
	for (size_t i = 0; i < NumCities; i++)
	{
		for (size_t j = 0; j < NumCities; j++)
		{
			PtrToNode item = Data.at(i).at(j);
			if (item)
			{
				delete(item);
				Data.at(i).at(j) = nullptr;
				Data.at(j).at(i) = nullptr;
			}
		}
	}
}

void TravelMenu::Dijkstra(int startCity)
{
	Dist.at(startCity) = 0;
	Payment.at(startCity) = 0;

	while (true)
	{
		int nextItem = -1;
		int min = std::numeric_limits<int>::max();
		int minP = std::numeric_limits<int>::max();

		for (size_t i = 0; i < NumCities; i++)
		{
			// 找到一个没有访问过的，Dist 最小的点
			if (!Visited.at(i) && Dist.at(i) < min)
			{
				nextItem = i;
				min = Dist.at(i);
				minP = Payment.at(i);
			}
		}

		if (-1 == nextItem)		return;

		Visited.at(nextItem) = true;

		for (size_t i = 0; i < NumCities; i++)
		{
			// 普通情况，从当前点到目标点更快（比到目标点的其他路线）
			if (!Visited.at(i) && Data.at(nextItem).at(i) 
				&& ((Dist.at(nextItem) + Data.at(nextItem).at(i)->length) < Dist.at(i)))
			{
				Dist.at(i) = Dist.at(nextItem) + Data.at(nextItem).at(i)->length;
				Payment.at(i) = Payment.at(nextItem) + Data.at(nextItem).at(i)->charge;
			}
			// 特殊情况，两条录像一样快，比高速费哪个少
			else if (!Visited.at(i) && Data.at(nextItem).at(i)
				&& ((Dist.at(nextItem) + Data.at(nextItem).at(i)->length) == Dist.at(i)))
			{
				if (Payment.at(nextItem) + Data.at(nextItem).at(i)->charge < Payment.at(i))
				{
					Payment.at(i) = Payment.at(nextItem) + Data.at(nextItem).at(i)->charge;
				}
			}
		}
	}
}

void TravelMenu::checkPath(int scity, int ecity)
{
	// 调用Dijkstra算法来计算单源有权路径图
	Dijkstra(scity);

	// 题目说保证了解的存在，那就直接找到值输出就行了
	std::cout << Dist.at(ecity) << " " << Payment.at(ecity);
}

void TravelMenu::insertEdgeHelper(int c1, int c2, int len, int pay)
{
	PtrToNode itemPtr = new Node(len, pay);

	Data.at(c1).at(c2) = itemPtr;
	Data.at(c2).at(c1) = itemPtr;
}

void TravelMenu::readEdges(int num)
{
	for (size_t i = 0; i < num; i++)
	{
		int city1 = 0, city2 = 0, length = 0, payment = 0;
		std::cin >> city1 >> city2 >> length >> payment;

		insertEdgeHelper(city1, city2, length, payment);
	}
}

int main()
{
	int numOfCities = 0;
	int numOfRoads = 0;
	int startCity = -1;
	int endCity = -1;

	std::cin >> numOfCities >> numOfRoads >> startCity >> endCity;

	TravelMenu menu(numOfCities);							// 建立对象并舒适化
		
	menu.readEdges(numOfRoads);								// 读入高速数据

	menu.checkPath(startCity, endCity);						// 找到最短的路线

	return 0;
}