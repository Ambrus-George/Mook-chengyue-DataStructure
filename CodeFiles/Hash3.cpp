#include <iostream>
#include <vector>
#include <string>

class QQManagement
{
private:
	struct Node 
	{
		bool Occupied;			// 这个结点有数据
		bool Deleted;			// 这个结点数据被删
		long long Key;				// Key
		std::string Account;	// QQ账号
		std::string Password;	// QQ密码

		Node() : Occupied(false), Deleted(false), Key(0) {}
	};

	int N;						// 记录的用户数量
	int K;						// 
	int Hash_size;				// 4*K + 3
	float Stock_factor;			// 装填因子
	std::vector<Node> Data;		// 数据

public:

	QQManagement() : N(0), K(1), Stock_factor(0)
	{
		Hash_size = 4 * K + 3;
		Data.resize(Hash_size);
	}

	long long getHashKey(std::string str)
	{
		/*int chunksize = 3;
		std::vector<std::string> chunks;
		int num = 0;

		while (!str.empty())
		{
			int take = std::min(chunksize, static_cast<int>(str.length()));
			chunks.push_back(str.substr(str.length() - take));
			str.resize(str.length() - take);
		}

		for (const auto& chunk : chunks)
		{
			int num1 = 0;
			for (int i = 0; i < chunk.size(); i++)
			{
				int item = chunk.at(i) - '0';
				num1 = num1 * 10 + item;
			}
			num += num1;
		}

		num %= 1000;
		return num;*/


		long long hash = 0;
		for (char c : str) {
			hash = hash * 131 + c; // 使用质数乘法减少冲突
		}
		return hash;
	}

	//int findPosition(std::vector<Node>& data, long long key)
	//{
	//	int newPos, oldPos;
	//	newPos = oldPos = key % data.size();
	//	int count = 0;

	//	while (data.at(newPos).Occupied && !data.at(newPos).Deleted && data.at(newPos).Key != key)
	//	{
	//		if (++count % 2)	// 奇数次冲突
	//		{
	//			newPos = oldPos + (count + 1) * (count + 1) / 4;
	//			if (newPos >= data.size())
	//			{
	//				newPos %= data.size();
	//			}
	//		}
	//		else				// 偶数次冲突
	//		{
	//			newPos = oldPos - count * count / 4;
	//			if (newPos < 0)
	//			{
	//				newPos += data.size();
	//			}
	//		}
	//	}

	//	return newPos;
	//}

	int findPosition(std::vector<Node>& data, long long key) {
		int size = data.size();
		int pos = key % size;
		int count = 0;

		while (data[pos].Occupied && !data[pos].Deleted && data[pos].Key != key) {
			count++;
			pos = (key + count * count) % size; // 仅使用正增量
		}

		return pos;
	}


	void loginAccount(std::string account, std::string password)
	{
		long long key = getHashKey(account);
		int position = findPosition(Data, key);

		if (!Data.at(position).Occupied)
		{
			std::cout << "ERROR: Not Exist" << std::endl;
			return;
		}
		if(Data.at(position).Password == password)
		{
			std::cout << "Login: OK" << std::endl;
			return;
		}
		std::cout << "ERROR: Wrong PW" << std::endl;
	}

	bool IsPrime(int item)
	{
		if (item <= 1)	return false;
		if (item == 2)	return true;
		if (item % 2 == 0)	return false;
		for (int i = 3; i * i <= item; i += 2)
		{
			if (item % i == 0) return false;
		}

		return true;
	}

	/*void expandData()
	{
		while (Stock_factor > 0.5 || !IsPrime(Hash_size))
		{
			K++;
			Hash_size = 4 * K + 3;
			Stock_factor = (decltype(Stock_factor))N / Hash_size;
		}

		decltype(Data) TempData = Data;
		Data.clear();
		Data.resize(Hash_size);

		for (auto item : TempData)
		{
			if (item.Occupied && !item.Deleted)
			{
				long long key = getHashKey(item.Account);
				int position = findPosition(Data, key);

				Data.at(position).Account = item.Account;
				Data.at(position).Deleted = false;
				Data.at(position).Key = key;
				Data.at(position).Occupied = true;
				Data.at(position).Password = item.Password;
			}
		}
	}*/

	void expandData() {
		// 计算新的大小
		int newK = K * 2;
		int newSize = 4 * newK + 3;
		while (!IsPrime(newSize)) {
			newK++;
			newSize = 4 * newK + 3;
		}

		// 创建新表
		std::vector<Node> newData(newSize);

		// 重新哈希所有元素
		for (const auto& node : Data) {
			if (node.Occupied && !node.Deleted) {
				long long key = getHashKey(node.Account);
				int pos = key % newSize;

				// 使用平方探测找到新位置
				int count = 0;
				while (newData[pos].Occupied) {
					count++;
					pos = (key + count * count) % newSize;
				}

				newData[pos] = node;
			}
		}

		// 更新类成员
		K = newK;
		Hash_size = newSize;
		Data = std::move(newData);
		Stock_factor = static_cast<float>(N) / Hash_size;
	}

	void registerAccount(std::string account, std::string password)
	{
		long long key = getHashKey(account);
		int position = findPosition(Data, key);

		if (!Data.at(position).Deleted && Data.at(position).Account == account)
		{
			std::cout << "ERROR: Exist" << std::endl;
			return;
		}

		Data.at(position).Account = account;
		Data.at(position).Deleted = false;
		Data.at(position).Key = key;
		Data.at(position).Occupied = true;
		Data.at(position).Password = password;

		N++;
		Stock_factor = (decltype(Stock_factor))N / Hash_size;

		if (0.5 < Stock_factor)		expandData();

		std::cout << "New: OK" << std::endl;
	}
};

int main()
{
	int N;
	std::cin >> N;
	QQManagement HashTable;

	if (N)
	{
		for (int i = 0; i < N; i++)
		{
			char ch;
			std::cin >> ch;

			switch (ch)
			{
			case 'L':
			{
				std::string str1, str2;
				std::cin >> str1 >> str2;
				HashTable.loginAccount(str1, str2);
				break;
			}


			case 'N':
			{
				std::string str1, str2;
				std::cin >> str1 >> str2;
				HashTable.registerAccount(str1, str2);
				break;
			}

			default:
				break;
			}
		}
	}


	return 0;
}











