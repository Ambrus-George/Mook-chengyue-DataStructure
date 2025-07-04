#include <iostream>
#include <cstring>

#define MAXSIZE 10000

typedef int ElementType;

class NetWork 
{
public :
	NetWork(int num) : N(num)
	{
		memset(Data, -1, sizeof(Data));
	}
	~NetWork() {}

	void checkTransfer(ElementType a, ElementType b)
	{
		ElementType root1 = findRoot(a);
		ElementType root2 = findRoot(b);

		bool flag = (root1 == root2);

		if (flag)
		{
			std::cout << "yes" << std::endl;
		}
		else {
			std::cout << "no" << std::endl;
		}
	}

	int numOfComponents()
	{
		int countNum = 0;

		for (int i = 0; i < N; i++)
		{
			if (Data[i+1] < 0)
			{
				countNum++;
			}
		}

		return countNum;
	}

	void inputtingConnection(ElementType a, ElementType b)
	{
		ElementType root1 = findRoot(a);
		ElementType root2 = findRoot(b);

		if (Data[root1] < Data[root2])
		{
			Data[root1] += Data[root2];
			Data[root2] = root1;
		}
		else {
			Data[root2] += Data[root1];
			Data[root1] = root2;
		}
	}

	ElementType findRoot(int a)
	{
		int i = a;
		while (Data[i] > 0)
		{
			i = Data[i];
		}

		return i;
	}

private:
	ElementType Data[MAXSIZE + 1];
	int N;
};

int main()
{
	int N = 0;
	std::cin >> N;
	NetWork netw(N);
	bool whilebool = true;

	while (whilebool)
	{
		char ch = ' ';
		ElementType a = 0;
		ElementType b = 0;
		std::cin >> ch;
		int numC = 0;

		switch (ch)
		{
		case 'C':
			std::cin >> a >> b;
			netw.checkTransfer(a, b);
			continue;

		case 'I':
			std::cin >> a >> b;
			netw.inputtingConnection(a, b);
			continue;

		case 'S':
			numC = netw.numOfComponents();
			if (numC == 1)
			{
				std::cout << "The network is connected." << std::endl;
			}
			else {
				std::cout << "There are " << numC << " components." << std::endl;
			}
			whilebool = false;
			break;
		default:
			break;
		}
	}

	return 0;
}
