#include <stdio.h>

typedef struct Node *PtrNode;
struct Node
{
    int coef;
    int expon;
    PtrNode next;
};
typedef PtrNode List;

List creatTree();
void insertNode(List L, int coef, int expon);
List multiList(List L1, List L2);
List addList(List L1, List L2);
void printList(List L);
void freeList(List L);

int main(){

    //scan the input
    List L1;
    List L2;
    L1 = creatTree();
    L2 = creatTree();

    // printList(L1); 测试用
    // printf("\n");测试用
    // printList(L2);测试用

    //compute and output the multiplication-outcome
    List mList = multiList(L1, L2);
    printList(mList);
    printf("\n");

    //compute and output the addition-outcome
    List aList = addList(L1, L2);
    printList(aList);

    //free the List
    freeList(L1);
    freeList(L2);
    freeList(mList);
    freeList(aList);

    return 0;
}

List creatTree(){
    /*creat head code*/
    List l = (PtrNode)malloc(sizeof(struct Node));
    l->next = NULL;

    /**/
    int num;
    scanf("%d", &num);

    if (num)
    {
        getchar();
        /* code */
        for (int i = 0; i < num; i++)
        {
            int coef = 0;
            int expon = 0;
            scanf("%d %d", &coef, &expon);
            insertNode(l, coef, expon);
        }  
    }
    
    return l;
}

void insertNode(List L, int coef, int expon){
    int c = coef;
    int e = expon;
    
    PtrNode node = (PtrNode)malloc(sizeof(struct Node));
    node->coef = c;
    node->expon = e;
    node->next = NULL;

    PtrNode l = L;
    while (l->next && e < l->next->expon)
    {
        l = l->next;
    }

    if (l->next && e == l->next->expon)
    {
        /*这里有个大问题，如果合并出现了系数是0，还需要删除这个结点*/
        if (l->next->coef + node->coef)
        {
            l->next->coef += node->coef;
        }else{
            PtrNode d = l->next;
            l->next = d->next;
            free(d);
        }
        free(node);
    }else{
        node->next = l->next;
        l->next = node;
    }

    return L;
}

List multiList(List L1, List L2){
    List L = (List)malloc(sizeof(struct Node));
    L->next = NULL;

    List l1 = L1->next;
    List l2 = L2->next;
    while (l1)
    {
        while (l2)
        {
            insertNode(L, l1->coef * l2->coef, l1->expon + l2->expon);
            l2 = l2->next;
        }
        l2 = L2->next;
        l1 = l1->next;
    }
    return L;
}

List addList(List L1, List L2){
    List L = (List)malloc(sizeof(struct Node));
    L->next = NULL;

    List l1 = L1->next;
    List l2 = L2->next;

    while (l1 && l2)
    {
        if (l1->expon > l2->expon)
        {
            insertNode(L, l1->coef, l1->expon);
            l1 = l1->next;
        }else if(l1->expon == l2->expon){
            if(l1->coef + l2->coef){
                insertNode(L, l1->coef + l2->coef, l1->expon);
            }
            l1 = l1->next;
            l2 = l2->next;
        }else{
            insertNode(L, l2->coef, l2->expon);
            l2 = l2->next;
        }  
    }

    while (l1)
    {
        insertNode(L, l1->coef, l1->expon);
        l1 = l1->next;
    }
    
    while (l2)
    {
        insertNode(L, l2->coef, l2->expon);
        l2 = l2->next;
    }

    return L;
}

void printList(List L){
    PtrNode l = L->next;
    int flag = 0;

    if (l)
    {
        while (l)
        {
            if (flag)
            {
                printf(" ");
            }

            printf("%d %d", l->coef, l->expon);
            flag = 1;

            l = l->next;
        }
    }else{
        printf("0 0");
    }
}

void freeList(List L){
    while (L)
    {
        PtrNode l = L;
        L = L->next;
        free(l);
    } 
}