#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "global.h"
#include "card_file.h"
Card aCard[50]; // 卡信息结构体数组
int nCount = 0; // 卡信息实际个数
int getCard();
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
    // 将卡信息保存到文件中
    return saveCard(&card, CARDPATH);
    // if (saveCard(&card, CARDPATH) == NULL) // comparison between pointer and integer,反正估计也不会再没有的情况下度,不管了
    // {
    //     return 0;
    // }
}
Card *queryCard(const char *pName)
{
    lpCardNode node = NULL;
    getCard();
    // if (getCard() == 0) // comparison between pointer and integer,,FALSE改成0不起作用,忽略吧
    // {
    //     return FALSE;
    // }
    // 从链表的头结点指向下一个结点开始遍历

    node = cardList->next;
    while (node != NULL)
    {
        if (strcmp(node->data.aName, pName) == 0)
        {
            return &node->data;
        }
        node = node->next;
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
    Card *pCard = NULL;
    getCard();
    // if(getCard()==FALSE)
    // {
    //     return FALSE;
    // }
    // 首先分配一个Card大小内存空间
    pCard = (Card *)malloc(sizeof(Card));
    if (pCard == NULL)
    {
        return NULL;
    }
    // 如果链表为空,查询失败,返回NULL
    // 从链表的头结点指向的下一个结点开始遍历
    cur = cardList->next;
    //遍历链表,结点为空表示到达链表尾部
    while (cur != NULL)
    {
        //判断在遍历到的结点的学号中,查找时候包含pName字符串
        if (strstr(cur->data.aName, pName) != NULL)
        {
            //如果有,则保存结点中的数据
            pCard[*pIndex] = cur->data;
            (*pIndex)++;
            //重新为指针分配内存
            // void *realloc(void *ptr, size_t size)
            pCard = (Card *)realloc(pCard, ((long long unsigned int)(*pIndex) + 1) * sizeof(Card)); // warning: conversion to 'long long unsigned int' from 'int' may change the sign of the result [-Wsign-conversion]
        }
        cur = cur->next;
    }

    return pCard;
}

int getCard()
{
    // 调用getCardCount(),获取文件中卡信息数量
    int count = 0; // 这里使用nCount会和本文件最上边的全局变量名字重复
    Card *pCard = NULL;
    int i = 0;
    lpCardNode node = NULL;
    lpCardNode cur = NULL;
    if (cardList != NULL)
    {
        releaseCardList();
    }
    initCardList();
    // 获取卡信息数量
    count = getCardCount(CARDPATH);
    nCount = count;
    // 动态分配内存
    pCard = (Card *)malloc(sizeof(Card) * (long long unsigned int)count); // conversion to 'long long unsigned int' from 'int' may change the sign of the result [-Wsign-conversion]gcc
    if (pCard == NULL)
    {
        return FALSE;
    }
    // 获取卡信息
    // 调用readCard(),从文件中读取卡信息
    // 将卡信息保存到card_service.c文件中的全局变量cardList链表中,链表中的每一个节点保存一条卡信息
    // 注意：为保证查询卡时,文件中的数据与链表中的数据相同。所以当查询卡时,不管链表cardList中有无数据,都会先清空链表中的数据,然后从card.txt文件中读取所有的卡信息,保存到链表中。
    if (readCard(pCard, CARDPATH) == FALSE)
    {
        free(pCard);
        pCard = NULL;
        return FALSE;
    }
    for (i = 0, node = cardList; i < count; i++)
    {
        // 为结点分配内存
        cur = (lpCardNode)malloc(sizeof(CardNode));

        // 如果内存分配失败,则返回
        if (cur == NULL)
        {
            free(pCard);
            return FALSE;
        }
        // 初始化新的空间,全部赋值为0;
        memset(cur, 0, sizeof(CardNode));

        // 将卡信息保存到结点中
        cur->data = pCard[i];
        cur->next = NULL;

        // 将结点添加到链表尾部
        node->next = cur;
        node = cur;
    }
    free(pCard);
    pCard = NULL;

    return TRUE;
}
