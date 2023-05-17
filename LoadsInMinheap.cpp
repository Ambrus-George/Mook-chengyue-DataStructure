#include <iostream>

#define MAXSIZE 1000

using namespace std;

typedef int ElementType;

typedef struct HNode *Heap;
struct HNode{
    ElementType *Data;
    int Size;
    int Capacity;
};

typedef Heap MinHeap;

Heap CreateHeap(int size);
void InsertHeap(Heap H, ElementType X);
void PrintR(int p, Heap H);

int main()
{
    int N = 0;
    int M = 0;

    int M_Group[MAXSIZE];//Store M numbers

    cin >> N >> M;

    //Create a min_heap
    MinHeap minH = CreateHeap(N);

    //Insert the input and classfy the min_Heap
    for (int i = 0; i < N; i++)
    {
        ElementType item = 0;
        cin >> item;
        InsertHeap(minH, item);
    }

    //Read the position numbers
    for (int i = 0; i < M; i++)
    {
        cin >> M_Group[i];
    }

    //Print the result
    for (int i = 0; i < M; i++)
    {
        PrintR(M_Group[i], minH);
    }
    return 0;
}

void PrintR(int p, Heap H){
    int i = p;
    bool flag = false;
    for ( ; i > 0; i /= 2)
    {
        if (flag)   cout << " " ;
        cout << H->Data[i];
        flag = true;
    }
    cout << endl;
}

Heap CreateHeap(int size){
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType*)malloc((size + 1) * sizeof(ElementType));
    H->Data[0] = -10001;    //define Data[0] = min = -10001;
    H->Capacity = size;
    H->Size = 0;

    return H;
}

void InsertHeap(Heap H, ElementType X){
    int i = ++H->Size;
    
    for ( ; H->Data[i/2] > X; i /= 2)
    {
        H->Data[i] = H->Data[i/2];
    }
    H->Data[i] = X;
    return;
}