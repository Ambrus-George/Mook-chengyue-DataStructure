#include <iostream>
#include <vector>

typedef int ElementType;
typedef int IndexType;

int main()
{
	IndexType N;
	std::cin >> N;
	std::vector<ElementType> Data(51, 0);

	for (int i = 0; i < N; i++)
	{
		ElementType item = 0;
		std::cin >> item;
		Data.at(item)++;
	}

	for (int i = 0; i < Data.size(); i++)
	{
		if (Data.at(i))
		{
			std::cout << i << ":" << Data.at(i) << std::endl;
		}
	}



	return 0;
}