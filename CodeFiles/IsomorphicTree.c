#include <stdio.h>

#define Null -1
#define MAXSIZE 10
typedef char ElementType;
typedef int Tree;

struct Node
{
    ElementType data;
    Tree left;
    Tree right;
}T1[MAXSIZE], T2[MAXSIZE];

Tree BuildTree(struct Node T[]);
int Isomorphic(Tree r1, Tree r2);

int main()
{
    //build the first tree
    Tree root1 = 0;
    root1 = BuildTree(T1);

    //build the second tree
    Tree root2 = 0;
    root2 = BuildTree(T2);

    //adjust
    if (Isomorphic(root1, root2)) { printf("Yes\n"); }
    else { printf("No\n"); }
    
    return 0;
}

Tree BuildTree(struct Node T[])
{
    int N = 0;
    scanf("%d\n", &N);

    if (N)
    {   
        int check[N];
        for (int i = 0; i < N; i++)
        {
            /* 判断是不是根结点的判断数组 */
            check[i] = 1;
        }
        
        for (int i = 0; i < N; i++)
        {
            char c2, c3;
            scanf("%c %c %c\n", &T[i].data, &c2, &c3);

            /*将读入转化为int，判断是不是 ‘-’*/
            if (c2 == '-')
            {
                T[i].left = -1;
            }else{
                T[i].left = c2 - '0';
                check[T[i].left] = 0;
            }
            
            if (c3 == '-')
            {
                T[i].right = -1;
            }else{
                T[i].right = c3 - '0';
                check[T[i].right] = 0;
            }
        }

        for (int i = 0; i < N; i++)
        {
            /* 查找根结点 */
            if (check[i])
            {
                return i;
            }
        }
        
    }

    //如果没有树可以建立
    return Null;
}

int Isomorphic(Tree r1, Tree r2)
{
    //都是空树, 同构
    if (r1 == Null && r2 == Null)
    {
        return 1;
    }

    //一个树为空，一个树不为空
    if ((r1 == Null && r2 != Null) || (r2 == Null && r1 != Null))
    {
        return 0;
    }
    
    
    //根结点都不一样，不同构
    if (T1[r1].data != T2[r2].data)
    {
        return 0;
    }

    //根结点的左子树是空的，需要判定右子树是否同构
    if ((T1[r1].left == Null) && (T2[r2].left == Null))
    {
        return Isomorphic(T1[r1].right, T2[r2].right);
    }
    
    if ((T1[r1].left != Null) && (T2[r2].left != Null) &&
        (T1[T1[r1].left].data == T2[T2[r2].left].data))
    {
        /* 左子树都不空，并且左子树的结点一致，不需要交换 */
        return ( Isomorphic(T1[r1].left, T2[r2].left) &&
                 Isomorphic(T1[r1].right, T2[r2].right));
    }else{
        /* 需要交换 */
        return ( Isomorphic(T1[r1].left, T2[r2].right) &&
                 Isomorphic(T1[r1].right, T2[r2].left));
    }
    
}