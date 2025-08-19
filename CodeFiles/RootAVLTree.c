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


Tree CreateTree(Tree T, int N);
Tree InsertNode(PNode item, Tree T);
void DeleteTree(Tree T);
PNode NewNode(int item);
int HeightTree(Tree T);
Tree RRFix(Tree T);
Tree RLFix(Tree T);
Tree LLFix(Tree T);
Tree LRFix(Tree T);

int main()
{
    int N = 0;
    scanf("%d", &N);

    if (N)
    {
        /* N 非 0 ，有输入 */
        Tree T = NULL;
        T = CreateTree(T, N);
        printf("%d", T->item);
        DeleteTree(T);
    }
    
    return 0;
}

/* 读入N个数，将这些数插入到T树上 */
Tree CreateTree(Tree T, int N){

    for (int i = 0; i < N; i++)
    {
        int item = 0;
        scanf("%d", &item);
        PNode Pitem = NewNode(item);
        T = InsertNode(Pitem, T);
    }
    
    return T;
}

/* 将新的结点Pitem插入到T树上，并且插入过程中 */
Tree InsertNode(PNode Pitem, Tree T){

    /* 如果是空树，返回头结点 */
    if (!T)
    {
        T = Pitem;
    }else{
    /* 如果不是空树，就要插入 */

        /*插入到右子树上，可能会触发 RR/RL*/
        if (Pitem->item > T->item)
        {
            T->right = InsertNode(Pitem, T->right);

            if (HeightTree(T->right) - HeightTree(T->left) == 2)
            {
                /* RR */
                if (Pitem->item > T->right->item)
                {
                    T = RRFix(T);
                }else{
                /* RL */
                    T = RLFix(T);
                }
                
            }
            
        }
        /*插入到左子树上，可能会触发 LL/LR*/
        if (Pitem->item < T->item)
        {
            T->left = InsertNode(Pitem, T->left);

            if (HeightTree(T->right) - HeightTree(T->left) == -2)
            {
                /* LL */
                if (Pitem->item < T->left->item)
                {
                    T = LLFix(T);
                }else{
                /* LR */
                    T = LRFix(T);
                }
                
            }
        }
    }

    return T;
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

/* 建立一个结点存储item */
PNode NewNode(int item){
    PNode Prlitem = (Tree)malloc(sizeof(struct Node));
    Prlitem->item = item;
    Prlitem->left = NULL;
    Prlitem->right = NULL;
    return Prlitem;
}

int HeightTree(Tree T){
    int height = 0;
    
    if (!T)
    {
        return height;
    }
    int lefth = HeightTree(T->left);
    int righth = HeightTree(T->right);
    height = (lefth > righth) ? lefth : righth;
    return (height+1);
}

Tree RRFix(Tree T){
    PNode root = T->right;
    T->right = root->left;
    root->left = T;
    return root;
}

Tree RLFix(Tree T){
    PNode root = T->right->left;
    T->right->left = root->right;
    root->right = T->right;
    T->right = root->left;
    root->left = T;
    return root;
}

Tree LLFix(Tree T){
    PNode root = T->left;
    T->left = root->right;
    root->right = T;
    return root;
}

Tree LRFix(Tree T){
    PNode root = T->left->right;
    T->left->right = root->left;
    root->left = T->left;
    T->left = root->right;
    root->right = T;
    return root;
}