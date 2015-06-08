//链表操作
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode
{
    int m_value;
    struct ListNode* m_pNext;
};

//向尾部添加节点
//注意这里的单链表是包含有头节点的单链表
void addToTail(ListNode* pHead, int value)
{
    ListNode* pNode = new ListNode();
    pNode->m_value = value;
    pNode->m_pNext = NULL;

    ListNode* pTail = pHead;
    while (pTail->m_pNext != NULL)
    {
        pTail = pTail->m_pNext;
    }
    pTail->m_pNext = pNode;
    return ;
}

//删除第一个碰到的指定值的节点
void removeNode(ListNode* pHead, int value)
{
    ListNode* pNode = pHead;
    while (pNode->m_pNext != NULL && pNode->m_pNext->m_value != value)
    {
        pNode = pNode->m_pNext;
    }
    //如果下一个节点为NULL，说明没有找到相应值
    if (NULL == pNode->m_pNext)
    {
        return ;
    }
    ListNode* pTmp = pNode->m_pNext;
    pNode->m_pNext = pTmp->m_pNext;
    delete pTmp;
}


//逆序打印链表，方法1，利用栈
void printListReverse(ListNode* pHead)
{
    std::stack<ListNode*> list_stack;
    ListNode* pNode = pHead->m_pNext;
    while (NULL != pNode)
    {
        list_stack.push(pNode);
    }
    while (!list_stack.empty())
    {
        ListNode* tmp = list_stack.top();
        printf("%d\n", tmp->m_value);
        list_stack.pop();
    }
}

//逆序打印链表，方法2，利用递归
void printListReverse(ListNode* pHead)
{
    ListNode* pNode = pHead->m_pNext;
    if (NULL == pNode)
    {
        return ;
    }
    else
    {
        printListReverse(pNode);
        printf("%d\n", pNode->m_value);
    }
}

//逆序打印链表，方法3，翻转链表
void printListReverse(ListNode* pHead)
{
    //略
}




