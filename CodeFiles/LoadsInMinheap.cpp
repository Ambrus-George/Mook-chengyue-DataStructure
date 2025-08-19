#include <iostream>
#include <array>
#include <limits>

#define MAXSIZE 1000

typedef int ElementType;

class MinHeap
{
public:
	MinHeap() : Data{ 0 }, index(0) 
	{
		initMinIndex0();
	}
	~MinHeap() {}

	void readInsert(ElementType item)
	{
		insertHelper(item);
	}

	void writeDataToEmptyHeap(int N)
	{
		for (int i = 0; i < N; i++)
		{
			ElementType item = 0;
			std::cin >> item;
			writeNumHelper(item);
		}

		sortMinHeap();
	}

	void sortMinHeap()
	{
		sortDataHelper();
	}

	void printIndexToRoot(int ind)
	{
		bool printFlag = false;
		for (int i = ind; i > 0; i /= 2)
		{
			if (printFlag)
			{
				std::cout << " ";
			}
			std::cout << Data[i];
			printFlag = true;
		}

		std::cout << std::endl;
	}

private:
	ElementType Data[MAXSIZE + 1];
	int index;

	void insertHelper(ElementType item)
	{
		int i = ++index;

		for (; Data[i/2] > item; i /= 2)
		{
			Data[i] = Data[i / 2];
		}

		Data[i] = item;
	}

	void initMinIndex0()
	{
		Data[0] = std::numeric_limits<ElementType>::min();
	}

	void writeNumHelper(ElementType item)
	{
		Data[++index] = item;
	}

	void sortDataHelper()
	{
		for (int i = index/2; i > 0; i--)
		{
			percolateDown(i);
		}
	}

	void percolateDown(int ind)
	{
		int parentIndex = ind;
		int childIndex = ind * 2;

		while (childIndex <= index)
		{
			// choose smaller child
			if (((childIndex + 1) <= index) && (Data[childIndex] > Data[childIndex + 1]))
			{
				childIndex++;
			}

			if (Data[parentIndex] > Data[childIndex])
			{
				swap(parentIndex, childIndex);
				parentIndex = childIndex;
				childIndex = parentIndex * 2;
			}
			else {
				break;
			}
		}
	}

	void swap(int ind1, int ind2)
	{
		ElementType item = Data[ind1];
		Data[ind1] = Data[ind2];
		Data[ind2] = item;
	}
};

int main()
{
	MinHeap minH;
	int n = 0, m = 0;

	std::cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		ElementType item = 0;
		std::cin >> item;
		minH.readInsert(item);
	}

	for (int i = 0; i < m; i++)
	{
		int index = 0;
		std::cin >> index;
		minH.printIndexToRoot(index);
	}

	return 0;
}
