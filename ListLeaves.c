#include <stdio.h>

#define Null -1
#define MAXSIZE 10
typedef int Tree;

int N = 0;

struct Node
{
    int position;
    Tree left;
    Tree right;
}T[MAXSIZE];

//Quence
struct Quence
{
    int quence[MAXSIZE];
    int head;
    int tail;
}Q;

Tree BuildTree(struct Node T[]);
void Output(Tree r);
void Push(int p);
int Pop();

int main()
{
    //build the tree
    Tree root = 0;
    root = BuildTree(T);

    //adjust
    Output(root);
    
    return 0;
}

Tree BuildTree(struct Node T[])
{
    scanf("%d\n", &N);

    if (N)
    {   
        int check[N];
        for (int i = 0; i < N; i++)
        {
            /* 判断是不是根结点的判断数组 */
            check[i] = 1;
            T[i].position = i;
        }
        
        for (int i = 0; i < N; i++)
        {
            char c2, c3;
            scanf("%c %c\n", &c2, &c3);

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

void Output(Tree r)
{
    //需要层序遍历树，遇到叶结点，然后输出
    //使用数组来实现一个队列
    Q.head = Null;
    Q.tail = Null;

    int printflag = 0;

    Push(r);

    while (Q.head != N-1) //队列空的时候 head == N-1
    {
        int popNum = Pop(Q);

        if ((T[popNum].left == Null) && (T[popNum].right == Null))
        {
            if (printflag)
            {
                printf(" ");
            }
            /* pop 出来的这个是叶结点，输出 */
            printf("%d", T[popNum].position);
            printflag = 1;
        }
        
        //pop 出来的这个有左结点就 push
        if (T[popNum].left != Null)
        {
            Push(T[popNum].left);
        }
        
        //pop 出来的这个有右结点就 push
        if (T[popNum].right != Null)
        {
            Push(T[popNum].right);
        }
    }

}

void Push(int p)
{
    //由于题目给定了结点的最大数量，就不做 “队列满” 的判定了
    Q.quence[Q.tail++] = p;
}

int Pop()
{
    //程序给定了数量，就不做 “队列空” 的判定了
    int result = Q.quence[Q.head++];
    return result;
}