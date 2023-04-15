#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXSIZE 1000

int sortGroup[MAXSIZE];
int inputGroup[MAXSIZE];
int compare(const void *a, const void *b);
void printLevelOrder(int nleft, int nright, int sGroup);
int GetLeftLength(int n);

int main()
{
    int N = 0;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &inputGroup[i]);
    }
    //将读入的树按照从小到大的顺序排好
    qsort(inputGroup, N, sizeof(int), compare);

    //将层序遍历的结果顺序存储到另外一个数组当中
    printLevelOrder(0, N-1, 0);

    //输出
    int printflag = 0;
    for (int i = 0; i < N; i++)
    {
        if (printflag)
        {
            printf(" ");
        }
        
        printf("%d", sortGroup[i]);
        printflag = 1;
    }
    
    return 0;
}

int compare(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

void printLevelOrder(int nleft, int nright, int sGroup){
    int n = nright - nleft + 1;
    if (!n)     return;

    int L = GetLeftLength(n);
    sortGroup[sGroup] = inputGroup[nleft + L];

    printLevelOrder(nleft, nleft+L-1, sGroup*2+1);
    printLevelOrder(nleft+L+1, nright, sGroup*2+2);
}

int GetLeftLength(int n){
    int H = (int)log2(n+1);
    int X = n - pow(2, H) + 1;
    return (pow(2, H-1)-1+((X < pow(2, H-1)) ? X : pow(2, H-1)));
}