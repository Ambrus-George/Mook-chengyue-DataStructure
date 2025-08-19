#include <iostream>
#include <array>

#define MAXSIZE 1000
#define STACKISEMPTY -1

typedef struct Stack* PtrToStack;
struct Stack {
	std::array<int, MAXSIZE + 1> Data;
	bool isFull;
	bool isEmpty;
	int ptr;
	int capacityOfStack;
};

void judgeTheLine(int cap, int lengthSeq);
PtrToStack aNewStack(int capacity);
bool pushStack(PtrToStack S, int item);
int popStack(PtrToStack S);

int main()
{
	int capacityStack = 0, lengthSeq = 0, numLine = 0;

	std::cin >> capacityStack >> lengthSeq >> numLine;

	//judge the lines

	for (int i = 0; i < numLine; i++)
	{
		judgeTheLine(capacityStack, lengthSeq);
	}
	return 0;
}

void judgeTheLine(int cap, int lengthSeq)
{
	PtrToStack st = aNewStack(cap);
	bool isCorrect = true;

	for (int i = 0; i < lengthSeq; i++)
	{
		int item = 0;
		std::cin >> item;

		if (isCorrect)
		{
			if (item > st->Data[0])
			{
				for (int j = st->Data[0]+1; j <= item; j++) {
					if (pushStack(st, j))
					{
						continue;
					}
					else {
						isCorrect = false;
						break;
					}
				}
			}

			
			int popInt = popStack(st);

			if (popInt == -1)
			{
				isCorrect = false;
				continue;
			}

			isCorrect = (popInt == item);
			
		}
	}

	if (isCorrect) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
}

PtrToStack aNewStack(int capacity)
{
	PtrToStack st = new struct Stack;
	st->Data = {};
	st->capacityOfStack = capacity;
	st->isEmpty = true;
	st->isFull = false;
	st->ptr = 0;

	return st;
}

bool pushStack(PtrToStack S, int item)
{
	if (S->isFull)
	{
		return false;
	}

	S->Data[++S->ptr] = item;
	S->Data[0]++;
	S->isEmpty = false;
	if (S->ptr == S->capacityOfStack)
	{
		S->isFull = true;
	}
	return true;
}

int popStack(PtrToStack S)
{
	if (S->isEmpty)
	{
		return STACKISEMPTY;
	}

	int item = S->Data[S->ptr--];
	S->isFull = false;
	if (!S->ptr)
	{
		S->isEmpty = true;
	}
	return item;
}