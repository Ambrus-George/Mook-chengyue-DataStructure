/*
二分法，没啥难度，一是 while 的条件写对，二是注意，当中间这个位置不是目的，记得 -1/+1 ，因为这个已经判定过了
*/

Position BinarySearch( List L, ElementType X )
{
    Position left = 1;
    Position right = L->Last;
    Position medium = (right - left)/2 + left;

    while (left <= right)
    {
        if (X == L->Data[medium])
        {
            return medium;
        }else if(X > L->Data[medium]){
            left = ++medium;
        }else{
            right = --medium;
        }
    }
    return NotFound; 
}