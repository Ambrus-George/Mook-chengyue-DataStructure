#include <stdio.h>

#define MAXSIZE 1000

void printResult(int num[], int M, int N);

int main()
{
    //read the input
    int M = 0;
    int N = 0;
    int K = 0;
    scanf("%d %d %d", &M, &N, &K);

    int num[K][N];
    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &num[i][j]);
        }
        
    }

    //adjust and print the result
    for (int i = 0; i < K; i++)
    {
        printResult(num[i], M, N);
    }
    
    return 0;
}

void printResult(int num[], int M, int N)
{

    int capacityOfS = M;
    int numOfN = N;
    int flag = 1;//最后输出的标识，0--NO，1--YES

    //判段是否正确有两个因素，如下：

    //1.想要输出这个样子的队列，堆栈的容量是否满足，也就是超没有超
    if (flag)
    {
        for (int i = 0; i < numOfN; i++)
        {
            /* push的次数不小于pop的次数，但不能超过4 */
            if ((capacityOfS + i) < num[i])
            {
                flag = 0;
                break;
            }
            
        }  
    }

    //2.输出的顺序要正确，比如说不能有“7 5 6”这样的顺序，像个山谷一样
    if (flag)
    {
        int valleyWest = 0;
        int valleyBottom = 0;
        int valleyEast = 0;

        for (int i = 0; i < numOfN-2; i++)
        {
            valleyWest = num[i];
            for(int j = i + 1; j <numOfN - 1; j++)
            {
                if (num[j] < valleyWest)
                {
                    valleyBottom = num[j];
                    for(int h = j+1; h < numOfN; h++)
                    {
                        valleyEast = num[h];
                        if ((valleyEast > valleyBottom) && (valleyEast < valleyWest))
                        {
                            flag = 0;
                            break;
                        }
                        
                    }
                }
                
            }
        }
        
    }
    
    if (flag)
    {
        printf("YES\n");
    }else{
        printf("NO\n");
    }
}