#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#define INITIALSIZEKEY 1

typedef bool Deleted;
typedef unsigned int KeyType;
typedef unsigned int CountType;
typedef unsigned int Position;
typedef float Factor_Float_Type;

typedef struct Node* PtrToNode;
struct Node {
	Deleted delFlag;	// 状态位，是不是已经删除了
	KeyType key;		// 用户转码编号
	CountType c;		// 用户通话次数统计
	std::string str;	// 用户初始编号

	Node() : delFlag(true), c(0) {}
};

class CrazyTalker
{
private:
	CountType N;						// 已经记录的用户数量
	CountType size_key;					// K
	CountType data_size;				// 4 * K + 3
	Factor_Float_Type stock_factor;		// 数组装填因子
	std::vector<Node> Data;				// 数据

	PtrToNode maxPtr;					// 记录通话次数最多的用户
	CountType numOfMax;					// 最多次数通话的人数

public:
	CrazyTalker() : size_key(INITIALSIZEKEY), stock_factor(0), N(0), maxPtr(nullptr), numOfMax(0)
	{
		data_size = 4 * size_key + 3;
		Data.resize(data_size);
		
	}

	KeyType hash_key(const std::string str)
	{
		KeyType key_item = (str.at(1) - '0') * std::pow(10, 5) + (str.at(2) - '0') * std::pow(10, 4)
			+ (str.at(5) - '0') * std::pow(10, 3) + (str.at(6) - '0') * std::pow(10, 2)
			+ (str.at(9) - '0') * std::pow(10, 1) + (str.at(10) - '0');

		return key_item;
 	}

	Position findPosition(std::vector<Node>& Data, KeyType key)
	{
		Position newPos, currentPos;
		KeyType count = 0;

		newPos = currentPos = key % data_size;

		while (!Data.at(newPos).delFlag && Data.at(newPos).key != key)
		{
			if (++count % 2)
			{
				newPos = currentPos + (count + 1) * (count + 1) / 4;
				if (newPos >= data_size)
				{
					newPos %= data_size;
				}
			}
			else {
				newPos = currentPos - count * count / 4;
				while (newPos < 0)
				{
					newPos += data_size;
				}
			}
		}

		return newPos;
	}

	PtrToNode getLowerStr(PtrToNode p1, PtrToNode p2)
	{
		PtrToNode itemptr = p1;

		for (size_t i = 0; i < p1->str.size(); i++)
		{
			if (p2->str.at(i) < p1->str.at(i)) {
				itemptr = p2;
				break;
			}
			else if (p1->str.at(i) < p2->str.at(i))
			{
				break;
			}
		}

		return itemptr;
	}

	//void expandGroup()
	//{
	//	decltype(data_size) oldsize = data_size;
	//	KeyType oldmaxkey = maxPtr->key;
	//	maxPtr = nullptr;
	//	

	//	while (stock_factor > 0.5)
	//	{
	//		size_key++;
	//		data_size = 4 * size_key + 3;
	//		stock_factor = (decltype(stock_factor))N / data_size;
	//	}

	//	Data.resize(data_size);
	//	decltype(Data) itemData(data_size);

	//	for (size_t i = 0; i < oldsize; i++)
	//	{
	//		if (!Data.at(i).delFlag)
	//		{
	//			Position index_item = findPosition(itemData, Data.at(i).key);
	//			itemData.at(index_item).c = Data.at(i).c;
	//			itemData.at(index_item).delFlag = Data.at(i).delFlag;
	//			itemData.at(index_item).key = Data.at(i).key;
	//			itemData.at(index_item).str = Data.at(i).str;
	//		}
	//	}

	//	/*for (size_t i = 0; i < data_size; i++)
	//	{
	//		Data.at(i).c = itemData.at(i).c;
	//		Data.at(i).delFlag = itemData.at(i).delFlag;
	//		Data.at(i).key = itemData.at(i).key;
	//		Data.at(i).str = itemData.at(i).str;
	//	}*/

	//	Data = itemData;

	//	for (auto& item : Data)
	//	{
	//		if (oldmaxkey == item.key)
	//		{
	//			maxPtr = &item;
	//			break;
	//		}
	//	}
	//}

	void rehash() {
		std::vector<Node> oldData = Data;
		data_size = 4 * size_key + 3;
		Data.clear();
		Data.resize(data_size);
		N = 0;

		for (const auto& node : oldData) {
			if (!node.delFlag) {
				Position index = findPosition(Data, node.key);
				Data[index] = node;
				N++;
			}
		}
		stock_factor = static_cast<float>(N) / data_size;
	}

	void getARecord(std::string str)
	{
		// 将 string 转成 key 值
		// 11位电话号码，0~10，将 12 56 910取出来
		KeyType key_item = hash_key(str);
		Position index_item = findPosition(Data, key_item);

		if (Data.at(index_item).key == key_item) // 如果已经有用户信息了，更新即可
		{
			Data.at(index_item).c++;
		}
		else {
			Data.at(index_item).c++;				// 登记用户信息
			Data.at(index_item).delFlag = false;
			Data.at(index_item).key = key_item;
			Data.at(index_item).str = str;
			N++;
		}

		if (!maxPtr)
		{
			maxPtr = &Data.at(index_item);
			numOfMax = 1;
		}
		else if (Data.at(index_item).c > maxPtr->c)			// 更新最多通话的人
		{
			maxPtr = &Data.at(index_item);
			numOfMax = 1;
		}
		else if (Data.at(index_item).c == maxPtr->c)	// 通话次数相同，选择号码小的
		{
			maxPtr = getLowerStr(maxPtr, &Data.at(index_item));
			if (maxPtr != &Data.at(index_item))
			{
				numOfMax++;
			}
			
		}

		stock_factor = (decltype(stock_factor)) N / data_size;

		if (stock_factor > 0.5)		// 如果装填因子大于0.5，就需要扩大数组了
		{
			size_key *= 2;  // 大小加倍
			rehash();
		}
	}

	/*void printResult()
	{
		std::cout << maxPtr->str << " " << maxPtr->c;
		if (numOfMax > 1)	std::cout << " " << numOfMax;
	}*/

	void printResult() {
		CountType maxCount = 0;
		std::vector<PtrToNode> maxNodes;

		for (auto& node : Data) {
			if (!node.delFlag) {
				if (node.c > maxCount) {
					maxCount = node.c;
					maxNodes.clear();
					maxNodes.push_back(&node);
				}
				else if (node.c == maxCount) {
					maxNodes.push_back(&node);
				}
			}
		}
		// 找出最小号码
		auto minNode = *std::min_element(maxNodes.begin(), maxNodes.end(),
			[](PtrToNode a, PtrToNode b) {
				return a->str < b->str;
			});

		// 输出结果
		std::cout << minNode->str << " " << minNode->c;
		if (maxNodes.size() > 1) {
			std::cout << " " << maxNodes.size();
		}
	}
};

int main()
{
	int N = 0;
	CrazyTalker Recording;
	std::cin >> N;

	if (N)
	{
		for (decltype(N) i = 0; i < 2*N; i++)
		{
			std::string s;
			std::cin >> s;
			Recording.getARecord(s);
		}
	}

	Recording.printResult();
}