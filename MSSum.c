#include<stdio.h>

int main()
{
    int k = 0;
    int thisone = 0;
    int maxsum = 0;
    int thissum = 0;

    scanf("%d", &k);

    if(k)
    {
        for(int i = 0; i < k; i++)
        {
            scanf("%d", &thisone);
            thissum += thisone;

            if (thissum > maxsum)
            {
                maxsum = thissum;
            }
            else if(thissum < 0)
            {
                thissum = 0;
            }
            
        }
    }

    printf("%d", maxsum);

    return 0;
}