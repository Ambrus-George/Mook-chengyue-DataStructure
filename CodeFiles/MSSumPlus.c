/*
这个算是求最大子列和的难度提升版，思想一致，方法也一致，
网上有很多人是使用数组方法做的，但我总想着，读入一个处理一个，因此，复杂度虽然低，但是，比较乱，后续有时间再整理

整体思想就是，读入一个，判断，之前的总和是不是负数，如果是负数，那么这个新的数，就有可能是最大子列的第一个数
加上这个数之后的新的总和，是不是历史最大的，如果是，那么这个数就是最大子列的尾巴

遇到的几个难处如下：
1. 数列中遇到 0 和负数的情况-------所以需要假定初始的 thissum 和 maxsum 都是 -1
2. 既然 1 假定两个是 -1，那么，maxsum，可以作为标记位使用，判断这个数列是不是均为负数
   thissum 为 -1，就不行了，因为这个参数要反应目前子列的实际总和，因此，运行时，它要变成 0
3. 如果数列均为负数，那么最后的输出会和普通情况不一致，因为，tail 一直不动，newhead 一直更新

*/

#include<stdio.h>

int main()
{
    int k = 0;
    int thisone = 0;
    int maxsum = -1;
    int thissum = -1;

    int oldHead = 0;
    int newHead = 0;
    int tail = 0;

    scanf("%d", &k);

    if(k)
    {
        for(int i = 0; i < k; i++)
        {
            scanf("%d", &thisone);

            if (thissum < 0)
            {
                /* 这里的 thissum 参数是没有加上新读入的这个数的总和 */
                /* 若这个数比0小，可能新出现的最大子列的头肯定在后面，也就是新读入的数 */
                newHead = thisone;
            }
            
            if (thissum == -1)
            {
                thissum++;
            }  
            thissum += thisone;

            if (i == 0)
            {
                /* 在最开始的时候需要对头和尾两个参数赋值，这个值是数列的第一个数字 */
                oldHead = thisone;
                tail = thisone;
            }

            if (thissum > maxsum)
            {
                maxsum = thissum;

                tail = thisone;/*当有新的最大数列产生，刚刚读入的数字一定就是最大数列的尾巴*/
                oldHead = newHead;/*此时，新的最大子列更新，那么新的头也就成了旧的头了，可能的新头会在下一次子列和小于0的时候更新*/
            }
            else if(thissum < 0)
            {
                thissum = -1;
            }
            
        }
    }

    //输出阶段
    //子列全为负数的情况
    if (maxsum == -1)
    {
        printf("0 %d %d", tail, newHead);
    }else{
        printf("%d %d %d", maxsum, oldHead, tail);
    }
    
    return 0;
}