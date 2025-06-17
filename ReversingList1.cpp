#include <iostream>
#include <iomanip>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
struct Node {
	PtrToNode Last;
	int addressNum;
	int data;		  //for HeadNode:length of the List
	int rearAddress;
	bool hadReversted;//sortedList-->sorted;reverstedList-->reversted
	PtrToNode Next;
};

List readTheInput(int N);
void printList(List L);
List deleteList(List L);
PtrToNode aNewNode(int add, int data, int rearadd);
List sortTheList(List L, int f);                    //L-->originalList; f-->address of the first num
List reverstTheList(List L, int K);					//
bool haveAList(List L);

int main()
{
	//1. read the input and build the List1
	//2. build the sorted List2 according the List1
	//3. build the reversted List3 according the List2
	//4. print the reversted List3


	List oList = NULL;
	List sList = NULL;
	List rList = NULL;

	//1
	int firstAdress = 0, N = 0, K = 0;
	std::cin >> firstAdress >> N >> K;
	oList = readTheInput(N);


	//2
	sList = sortTheList(oList, firstAdress);
	

	//3
	rList = reverstTheList(sList, K);
	

	//4
	printList(rList);


	oList = deleteList(oList);
	sList = deleteList(sList);
	rList = deleteList(rList);

	return 0;
}

List reverstTheList(List L, int K)
{
	if (!K || K == 1)
	{
		List reverstedL = aNewNode(0, 0, 0);
		PtrToNode ptr = reverstedL;
		PtrToNode item = L->Next;

		while (item)
		{
			PtrToNode newN = aNewNode(item->addressNum, item->data, item->rearAddress);
			ptr->Next = newN;
			ptr = ptr->Next;
			item = item->Next;
		}
		return reverstedL;
	}

	List reverstedL = aNewNode(0, 0, 0);
	PtrToNode ptr = reverstedL;
	PtrToNode head = L->Next;
	PtrToNode tail = L->Next;

	int countNum = 1;

	while(tail && head)
	{
		if (countNum == K+1)
		{
			countNum = 1;
			continue;
		}

		if (countNum == K)
		{
			head = tail;

			for (int i = 0; i < K; i++)
			{
				PtrToNode newN = aNewNode(head->addressNum, head->data, head->rearAddress);
				ptr->Next = newN;
				ptr = ptr->Next;
				head = head->Last;
			}

			head = tail->Next;
		}

		tail = tail->Next;
		countNum++;
	}

	while (head)
	{
		PtrToNode newN = aNewNode(head->addressNum, head->data, head->rearAddress);
		ptr->Next = newN;
		ptr = ptr->Next;
		head = head->Next;
	}

	ptr = reverstedL;
	ptr->hadReversted = false;
	while (ptr->Next)
	{
		ptr->rearAddress = ptr->Next->addressNum;
		ptr->Next->hadReversted = false;
		ptr->Next->Last = ptr;
		ptr = ptr->Next;
	}

	return reverstedL;
}

List sortTheList(List L, int f)
{
	List sortedL = aNewNode(0, 0, f);
	PtrToNode ptr = sortedL;
	PtrToNode item = L->Next;

	while (ptr->rearAddress != -1)
	{
		if (!item)
		{
			item = L->Next;
		}
		//finded!!!! and try next
		if (!item->hadReversted && (item->addressNum == ptr->rearAddress)) {
			PtrToNode newN = aNewNode(item->addressNum, item->data, item->rearAddress);
			ptr->Next = newN;
			ptr = ptr->Next;
			item->hadReversted = true;
		}
		item = item->Next;
	}

	ptr = sortedL;
	ptr->hadReversted = false;
	while (ptr->Next)
	{
		ptr->rearAddress = ptr->Next->addressNum;
		ptr->Next->hadReversted = false;
		ptr->Next->Last = ptr;
		ptr = ptr->Next;
	}

	return sortedL;

}

List deleteList(List L)
{
	while (L)
	{
		PtrToNode item = L;
		L = L->Next;
		delete item;
	}
	return L;
}

PtrToNode aNewNode(int add, int data, int rearadd)
{
	PtrToNode ptr = new Node;
	ptr->Last = NULL;
	ptr->Next = NULL;
	ptr->data = data;
	ptr->hadReversted = false;
	ptr->addressNum = add;
	ptr->rearAddress = rearadd;

	return ptr;
}

List readTheInput(int N)
{
	List L = aNewNode(0, N, 0);
	PtrToNode ptr = L;

	if (N)
	{
		for (int i = 0; i < N; i++) 
		{
			int add = 0, data = 0, rearadd = 0;
			std::cin >> add >> data >> rearadd;
			ptr->Next = aNewNode(add, data, rearadd);
			ptr = ptr->Next;
		}
	}

	return L;

}

bool haveAList(List L)
{
	return L->Next;
}

void printList(List L)
{
	/*bool hadPrinted = false;*/

	if (haveAList(L))
	{
		PtrToNode ptr = L->Next;
		while (ptr)
		{
			std::cout << std::setw(5) << std::setfill('0') << ptr->addressNum << " " << ptr->data << " ";

			if (!ptr->Next)
			{
				std::cout << "-1" << std::endl;
				return;
			}
			std::cout << std::setw(5) << std::setfill('0') << ptr->rearAddress << std::endl;
			ptr = ptr->Next;
		}
	}
	
}
