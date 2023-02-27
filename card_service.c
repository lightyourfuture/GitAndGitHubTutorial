#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "global.h"
Card aCard[50]; // 卡信息结构体数组
int nCount = 0; // 卡信息实际个数

lpCardNode cardList = NULL;

// 初始化链表
int initCardList()
{
    lpCardNode head = NULL;
    head = (lpCardNode)malloc(sizeof(CardNode));
    if (head != NULL) //
    {
        head->next = NULL;
        cardList = head;
        return TRUE;
    }
    return FALSE;
}
int addCard(Card card)
{
    lpCardNode cur = NULL;
    if (cardList == NULL)
    {
        initCardList();
    }
    // 将数据保存到结点中
    cur = (lpCardNode)malloc(sizeof(CardNode));
    if (cur != NULL)
    {
        // 将卡信息添加到当前结点
        cur->data = card;
        cur->next = NULL;
        // 找到链表的结尾
        //  遍历链表找到最后一个结点
        lpCardNode node = cardList;
        while (node->next != NULL)
        {
            node = node->next;
        }
        // 将添加的结点,添加到链表尾部
        node->next = cur;
        return TRUE;
    }
    return FALSE;
}

Card *queryCard(const char *pName)
{
    lpCardNode cur = NULL;
    if (cardList != NULL)
    {
        cur = cardList->next;
        while (cur != NULL)
        {
            if (strcmp(cur->data.aName, pName) == 0)
            {
                return &cur->data;
            }
            cur = cur->next;
        }
    }
    return NULL;
}

// 释放
// 这是原视频中的releaseCardList()函数,它只释放了一个节点,老师只是建立解决方案通过了,在运行终端的时候没有通过"输入0"来检查出程序"退出功能"的问题
// void releaseCardList()
// {
//     lpCardNode cur;
//     if (cardList != NULL)
//     {
//         while (cardList->next != NULL)
//         {
//             cur = cardList->next;
//             free(cur);
//             cur = NULL;
//         }
//     }
// }
void releaseCardList()
{
    lpCardNode cur;
    while (cardList != NULL)
    {
        cur = cardList;
        cardList = cur->next;
        free(cur);
    }
}

Card *queryCards(const char *pName, int *pIndex)
{
    lpCardNode cur = NULL;
    // 如果链表为空,查询失败,返回NULL
    // 首先分配一个Card大小内存空间
    Card *pCard = (Card *)malloc(sizeof(Card));
    // 从链表的头结点指向的下一个结点开始遍历

    if (pCard == NULL)
    {
        return NULL;
    }

    if (cardList != NULL)
    {
        cur = cardList->next;
        while (cur != NULL)
        {
            if (strstr(cur->data.aName, pName) != NULL)
            {
                pCard[*pIndex] = cur->data;
                (*pIndex)++;
                // void *realloc(void *ptr, size_t size)
                pCard = (Card *)realloc(pCard, ((long long unsigned int)(*pIndex) + 1) * sizeof(Card)); // warning: conversion to 'long long unsigned int' from 'int' may change the sign of the result [-Wsign-conversion]
            }
            cur = cur->next;
        }
    }
    return pCard;
}