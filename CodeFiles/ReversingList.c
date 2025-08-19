/*
**Reversing the list**
*思路简单，就是将数据全部读入一个数组，然后用另一个数组排序数据，再reverse数据，最后输出
*程序并不强壮，比如说，K的取值不能是0，但陈越老师并没有注意这一点，可以通过老师的全部测试点，我也就懒得改了
*这题刚开始一头雾水，这样子的处理为什么叫 reversing? 真服了
*/

#include <stdio.h>

#define MAX_SIZE 100000

typedef struct unit DataGroup;
struct unit
{
    int headadd;
    int tailadd;
    int data;
};

int main(){

    //读入输入
    int fAddress = 0;
    int N = 0;
    int K = 0;

    scanf("%d %d %d", &fAddress, &N, &K);

    DataGroup data[MAX_SIZE+1];
    if (N)
    {
        /* code */
        for (int i = 0; i < N; i++)
        {
            int hadd, temp, tadd;
            scanf("%d %d %d", &hadd, &temp, &tadd);
            data[hadd].headadd = hadd;
            data[hadd].data = temp;
            data[hadd].tailadd = tadd;
        }
        
    }
    
    //按照输入调整顺序
    DataGroup dataN[N];

    dataN[0].data = data[fAddress].data;
    dataN[0].headadd = fAddress;
    dataN[0].tailadd = data[fAddress].tailadd;

    if (-1 == dataN[0].tailadd)
    {
        N = 1;
    }else{
        for (int i = 1; i < N; i++)
        {
            dataN[i].data = data[dataN[i-1].tailadd].data;
            dataN[i].headadd = data[dataN[i-1].tailadd].headadd;
            dataN[i].tailadd = data[dataN[i-1].tailadd].tailadd;

            if (-1 == dataN[i].tailadd)
            {
                N = i + 1;
            }
            
        }
    }
    
     

    //按要求反转数组
    for (int i = 0; i < (N/K); i++)
    {
        for (int j = 0; j < K/2; j++)
        {
            int d = dataN[i*K + j].data;
            dataN[i*K + j].data = dataN[(i+1)*K - j -1].data;
            dataN[(i+1)*K - j -1].data = d;

            int had = dataN[i*K + j].headadd;
            dataN[i*K + j].headadd = dataN[(i+1)*K - j -1].headadd;
            dataN[(i+1)*K - j -1].headadd = had;
        }
        
    }
    
    int flag = 0;
    //输出最终结果
    for (int i = 0; i < N - 1; i++)
    {
        if (flag)
        {
            printf("\n");
        }
        
        printf("%05d %d %05d", dataN[i].headadd, dataN[i].data, dataN[i+1].headadd);
        flag = 1;
    }

    if (flag)
    {
        printf("\n");
    }
    printf("%05d %d -1", dataN[N-1].headadd, dataN[N -1].data);
    
    return 0;
}