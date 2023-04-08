#include <stdio.h>

#define S_SIZE 5
#define MAX_SIZE 30

void OutputResult(int *preO, int *inO, int N);
void PrintPost(int* preO, int* inO, int N);

int printFlag = 0;
//Push 的顺序就是先序遍历的结果
int preOrder[MAX_SIZE];
//Pop 的顺序就是中序遍历的结果
int inOrder[MAX_SIZE];

int main()
{
    int N = 0;
    scanf("%d\n", &N);

    if (N)
    {
        OutputResult(preOrder, inOrder, N);
    }
    

    return 0;
}

void OutputResult(int *preO, int *inO, int N)
{
    int stack[N];//模拟堆栈
    int p_stack = -1;

    int pushNum = 0;
    int popNum = 0;

    for (int i = 0; i < (N + N); i++)
    {
        char s[S_SIZE] = {0};//存放“Push", "Pop"
        scanf("%s", s);
        
        if ('u' == s[1])
        {
            int item = 0;
            scanf(" %d\n", &item);
            *(preO + pushNum) = item; //先序的数组存放
            pushNum++;
            stack[++p_stack] = item;//堆栈存放
        }else{
            *(inO + popNum) = stack[p_stack--];
            popNum++;
        }
        
    }
    PrintPost(preO, inO, N);
}

/*打印后序遍历结果*/
void PrintPost(int* preO, int* inO, int N)
{
    int n = N;

    if (1 == n)
    {
        
        if (printFlag)
        {
            printf(" ");
        }
        
        printf("%d", *preO);
        printFlag = 1;

        return;
    }

    
    int root = *preO;
    int nLeft = 0;

    for (int i = 0; i < n; i++)
    {
        /* 中序遍历数组中找根结点 */
        if (root == *(inO + i))
        {
            nLeft = i;
            break;
        }
        
    }
    
    /* 先输出左子树 */
    if (nLeft)
    {
        PrintPost((preO+1), inO, nLeft);
    }

    /* 后输出右子树 */
    if (N-1-nLeft)
    {
        PrintPost((preO+nLeft+1), (inO+nLeft+1), (N-1-nLeft));
    }

    /* 最后输出根结点 */
    PrintPost(preO, inO+nLeft, 1);
}