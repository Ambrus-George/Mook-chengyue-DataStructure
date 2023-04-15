#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PNode;
typedef PNode Tree;
struct Node
{
    int item;
    Tree left;
    Tree right;
};


void ComputeInput(int N, int L);
Tree InsertNode(PNode item, Tree T);
int IsSameTree(Tree T1, Tree T2);
void DeleteTree(Tree T);
PNode NewNode(int item);

int main()
{
    int N = 0;
    scanf("%d", &N);

    while (N)
    {
        /* N 非 0 ，有输入 */
        int L = 0;
        scanf("%d", &L);
        ComputeInput(N, L);

        scanf("%d", &N);
    }
    

    return 0;
}


void ComputeInput(int N, int L){
    int n = N;//结点的数量
    int l = L;//需要判定的的树的数量

    Tree T0 = NULL;

    for (int i = 0; i < n; i++)
    {
        int item = 0;
        scanf("%d", &item);
        PNode Pitem = NewNode(item);
        T0 = InsertNode(Pitem, T0);
    }
    
    for (int i = 0; i < l; i++)
    {
        Tree T1 = NULL;
        for (int j = 0; j < n; j++)
        {
            int item = 0;
            scanf("%d", &item);
            PNode Pitem = NewNode(item);
            T1 = InsertNode(Pitem, T1);
        }
        if (IsSameTree(T0, T1))
        {
            printf("Yes\n");
        }else{
            printf("No\n");
        }
        
        DeleteTree(T1);
    }
    
    DeleteTree(T0);
}

Tree InsertNode(PNode Pitem, Tree T){

    /* 如果是空树，返回头结点 */
    if (!T)
    {
        T = Pitem;
    }else{
        /* 如果不是空树，就要插入 */
        if (Pitem->item > T->item)
        {
            T->right = InsertNode(Pitem, T->right);
        }
        if (Pitem->item < T->item)
        {
            T->left = InsertNode(Pitem, T->left);
        }
    }

    return T;
}

int IsSameTree(Tree T1, Tree T2){

    //both-EmptyTree
    if (!T1 && !T2)
    {
        return 1;
    }

    //one of them is not Empty
    if ((!T1 && T2) || (!T2 && T1))
    {
        return 0;
    }
    
    //both-not-Empty
    if (T1->item != T2->item)
    {
        return 0;
    }else{
        return (IsSameTree(T1->left, T2->left) && IsSameTree(T1->right, T2->right));
    }
    
}

void DeleteTree(Tree T){
    if (T->left)
    {
        DeleteTree(T->left);
    }
    if (T->right)
    {
        DeleteTree(T->right);
    }
    free(T);
}

PNode NewNode(int item){
    PNode Prlitem = (Tree)malloc(sizeof(struct Node));
    Prlitem->item = item;
    Prlitem->left = NULL;
    Prlitem->right = NULL;
    return Prlitem;
}