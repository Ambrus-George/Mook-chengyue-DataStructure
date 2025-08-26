#include <iostream>
#include <vector>
#include <algorithm>

typedef int ElementType;

int main()
{
	int N;
	std::cin >> N;
	std::vector<ElementType> Data(N);
	std::for_each(Data.begin(), Data.end(), [](auto& item) {
		std::cin >> item;
		});

	int c = 0;
	int count_in_c = 1;
	int p = 0;
	int ptr = p;
	bool haveZero = false;
	auto advance_p = [&]() {
		while (p < N && Data.at(p) == p)
		{
			p++;
		}
		};

	while (true)
	{
		if (!ptr)	haveZero = true;

		if (Data.at(ptr) == ptr)
		{
			count_in_c--;
			if (count_in_c > 1)
			{
				if (!haveZero)
				{
					c += (count_in_c + 1);
				}
				else {
					c += (count_in_c - 1);
				}
				
			}
			count_in_c = 0;
			

			advance_p();
			if (p >= N)
			{
				break;
			}

			ptr = p;
			count_in_c++;
			haveZero = false;
		}
		else {
			auto old_ptr = ptr;
			ptr = Data.at(ptr);
			Data.at(old_ptr) = old_ptr;
			count_in_c++;
		}
	}

	/*if (N == 1 || !c)
	{
		std::cout << c;
	}
	else {
		std::cout << (c - 2);
	}*/
	
	std::cout << c;

	return 0;
}