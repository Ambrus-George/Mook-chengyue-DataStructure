#include <iostream>
#include <vector>
#include <limits>

bool IsPrime(int item)
{
	if (item <= 1)	return false;
	if (item == 2)	return true;
	if (item % 2 == 0)	return false;
	for (int i = 3; i*i <= item; i += 2)
	{
		if (item % i == 0) return false;
	}

	return true;
}

int HashGreaterThan(int M)
{
	int item = M;
	while (true)
	{
		if (IsPrime(item))	break;
		if (item == std::numeric_limits<int>::max())	return -1;
		item++;
	}
	return item;
}

int FindPositionInsert(int item, std::vector<int>& HashTable)
{
	int hash_size = HashTable.size();
	int hash_key = item % hash_size;
	int newPos;
	newPos = hash_key;
	int count = 0;
	std::vector<bool> Visited(hash_size, false);

	while (!Visited.at(newPos))
	{
		if (HashTable.at(newPos) == -1)	break;
		else {
			Visited.at(newPos) = true;
			count++;
			newPos = hash_key + (count * count);
			if (newPos >= hash_size)	newPos %= hash_size;
		}
	}

	if (Visited.at(newPos))	return -1;
	else
	{
		HashTable.at(newPos) = item;
		return newPos;
	}

}

int main()
{
	int M, N;
	std::cin >> M >> N;
	int hash_size = HashGreaterThan(M);
	std::vector<int> Data(N, -1);
	std::vector<int> HashTable(hash_size, -1);
	std::vector<int> HashIndex(N, -1);
	

	// Write the Data
	for (auto& item : Data)
	{
		std::cin >> item;
	}

	for (int i = 0; i < Data.size(); i++)
	{
		auto item = Data.at(i);
		auto position_item = FindPositionInsert(item, HashTable);
		HashIndex.at(i) = position_item;
	}

	bool print_flag = false;
	for (auto item : HashIndex)
	{
		if (print_flag)	std::cout << " ";

		if (item == -1)
		{
			std::cout << "-";
			print_flag = true;
		}
		else {
			std::cout << item;
			print_flag = true;
		}
	}

	return 0;
}