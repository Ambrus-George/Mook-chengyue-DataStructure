#include <iostream>
#include <vector>

typedef int ElementType;

bool insertion_sort_onestep(std::vector<ElementType>& Data)
{
	bool Flag = false;
	int i, j;

	for (i = 0; i < Data.size(); i++)
	{
		if (Flag)
		{
			break;
		}
		ElementType tmp = Data.at(i);
		for (j = i; j > 0 && Data.at(j - 1) > tmp; j--)
		{
			Data.at(j) = Data.at(j - 1);
			Flag = true;
		}
		Data.at(j) = tmp;
	}

	return Flag;
}

void merge(std::vector<ElementType>& A, std::vector<ElementType>& TmpA,
	int Left, int Right, int N)
{
	int tmp = Left;
	int left = Left;
	int leftend = Right - 1;
	int right = Right;
	int rightend = N;

	while (left <= leftend && right <= rightend)
	{
		if (A.at(left) <= A.at(right))
		{
			TmpA.at(tmp++) = A.at(left++);
		}
		else {
			TmpA.at(tmp++) = A.at(right++);
		}
	}
	while (left <= leftend) {
		TmpA.at(tmp++) = A.at(left++);
	}
	while (right <= rightend) {
		TmpA.at(tmp++) = A.at(right++);
	}
}

void merge_pass(std::vector<ElementType>& A, std::vector<ElementType>& TmpA,
	int N, int length)
{
	int i;
	for (i = 0; i <= N - 2 * length; i += (2 * length))
	{
		merge(A, TmpA, i, i + length, i + (2 * length) - 1);
	}

	if (i + length < N)
	{
		merge(A, TmpA, i, i + length, N - 1);
	}
	else {
		for (int j = i; j < N; j++)
		{
			TmpA.at(j) = A.at(j);
		}
	}
}

bool merge_sort_onestep(std::vector<ElementType>& Data, int N)
{
	// 合并排序是2，4，8...这样子组合排序的
	// 每一次都是固定的长度，为避免麻烦（需要传递当前组长度）
	// 从头开始合并后，每次和原始数据比较，有改变就停止
	std::vector<ElementType> copyData = Data;
	std::vector<ElementType> tmpData = Data;
	bool Flag = false;

	int length = 1;
	while (length < Data.size())
	{
		merge_pass(Data, tmpData, Data.size(), length);
		if (tmpData != copyData)
		{
			Data = tmpData;
			Flag = true;
			break;
		}
		length *= 2;
		merge_pass(tmpData, Data, Data.size(), length);
		if (Data != copyData)
		{
			Flag = true;
			break;
		}
		length *= 2;
	}
	return Flag;
}

void printData(std::vector<ElementType> data)
{
	bool flag = false;

	for (auto tmp : data)
	{
		if (flag)	std::cout << " ";
		std::cout << tmp;
		flag = true;
	}
}

int main()
{
	int N = 0;
	std::cin >> N;
	std::vector<ElementType> OriginalData(N);
	std::vector<ElementType> TestData(N);
	bool Flag = true;

	for (auto& tmp : OriginalData)
	{
		std::cin >> tmp;
	}
	for (auto& tmp : TestData)
	{
		std::cin >> tmp;
	}

	// insertion_sort_onestep: 进行一次有效的插入排序
	// merge_sort_onestep: 进行一次有效的合并排序
	decltype(OriginalData) CopyData = OriginalData;
	while (Flag)
	{
		Flag = merge_sort_onestep(CopyData, CopyData.size());
		if (CopyData == TestData)
		{
			break;
		}
	}

	if (Flag)
	{
		std::cout << "Merge Sort" << std::endl;
		if (merge_sort_onestep(TestData, TestData.size())) {}
		printData(TestData);
	}
	else {
		std::cout << "Insertion Sort" << std::endl;
		if (insertion_sort_onestep(TestData)) {}
		printData(TestData);
	}

	return 0;
}