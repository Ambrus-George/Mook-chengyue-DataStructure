/*
比较简单，但要细心审题，题目中有几个细节：
1.从小到大排列
2.使用L1，L2的结点
3.L1，L2 都是带着头结点的**************************这个太重要了
4.最后的所求列表也是要带着头结点********************这个太重要了

此外注意：函数的入口的变量，最好用新的变量名取代，别影响函数外的事物
 */
List Merge( List L1, List L2 ){
    /*申请头结点，提交结果需要带有头结点*/
    PtrToNode front;
    PtrToNode rear;
    List l1, l2;
    front = (List)malloc(sizeof(PtrToNode));
    rear = front;
    front->Next = NULL;

    l1 = L1->Next;
    l2 = L2->Next;

    /**/
    while (l1 && l2)
    {
        /*L1的结点指数低*/
        if (l1->Data < l2->Data)
        {
            rear->Next = l1;
            rear = rear->Next;
            l1 = l1->Next;
        }
        
        /*L2的结点指数低或者两个结点一样*/
        else{
            rear->Next = l2;
            rear = rear->Next;
            l2 = l2->Next;
        }
    }

    /*剩下的结点都是L1的*/
    if (l1)
    {
        rear->Next = l1;
    }
    
    /*剩下的结点都是L2的*/
    if (l2)
    {
        rear->Next = l2;
    }

    L1->Next = NULL;
    L2->Next = NULL;

    return front;
}