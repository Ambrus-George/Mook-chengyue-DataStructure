/* 你的代码将被嵌在这里 */
/* 函数Insert将X插入二叉搜索树BST并返回结果树的根结点指针 */
BinTree Insert( BinTree BST, ElementType X ){
    if (!BST)
    {
        Position node = (Position)malloc(sizeof(struct TNode));
        node->Data = X;
        node->Left = NULL;
        node->Right = NULL;

        return node;
    }else{
        if (X >= BST->Data)
        {
            BST->Right = Insert(BST->Right, X);
        }else{
            BST->Left = Insert(BST->Left, X);
        }  
    }
    return BST;
}

/* 函数Delete将X从二叉搜索树BST中删除，并返回结果树的根结点指针；
如果X不在树中，则打印一行Not Found并返回原树的根结点指针 */
BinTree Delete( BinTree BST, ElementType X ){

    if (!BST)
    {
        printf("Not Found\n");
    }else{
        if (X == BST->Data)
        {
            /* found */
            if ((BST->Left) && (BST->Right))
            {
                Position Pitem = FindMin(BST->Right);
                BST->Data = Pitem->Data;
                BST->Right = Delete(BST->Right, Pitem->Data);
            }else{
                Position Pitem = BST;
                if (BST->Left)      BST = BST->Left;
                else                BST = BST->Right;
                free(Pitem);
            }
            
        }

        else if (X > BST->Data)     BST->Right = Delete(BST->Right, X);
        else                        BST->Left = Delete(BST->Left, X);
        
        
    }
    return BST;
}

/* 函数Find在二叉搜索树BST中找到X，返回该结点的指针；如果找不到则返回空指针 */
Position Find( BinTree BST, ElementType X ){
    Position Pitem = NULL;

    if (!BST)  return NULL;
    else{
        if (X == BST->Data)     Pitem = BST;
        else if (X > BST->Data) Pitem = Find(BST->Right, X);
        else                    Pitem = Find(BST->Left, X);
    }
    return Pitem;
}

/* 函数FindMin返回二叉搜索树BST中最小元结点的指针 */
Position FindMin( BinTree BST ){

    if (BST){
        while (BST->Left)       BST = BST->Left;
    }
    return BST;
}

/* 函数FindMax返回二叉搜索树BST中最大元结点的指针 */
Position FindMax( BinTree BST ){
    if (BST){
        while (BST->Right)      BST = BST->Right;
    }
    return BST;
}