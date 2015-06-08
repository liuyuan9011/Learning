//重建二叉树，给你前序遍历和中序遍历，重建二叉树

struct BinaryTreeNode
{
    int m_value;
    struct BinaryTreeNode* m_pLeft;
    struct BinaryTreeNode* m_pRight;
};

BinaryTreeNode* constructBinaryTree(int* preorder, int* inorder, int length)
{
    if (NULL == preorder || NULL == inorder || length <= 0)
    {
        return NULL;
    }
    
    return constructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}

//未完待续...
