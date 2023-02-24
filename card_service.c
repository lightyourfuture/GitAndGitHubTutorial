#include <string.h>
#include <stdio.h>
#include "model.h"
#include "global.h"
Card aCard[50]; // 卡信息结构体数组
int nCount = 0; // 卡信息实际个数

int addCard(Card card)
{
    aCard[nCount] = card;
    nCount++;
    return TRUE;
}

Card* queryCard(const char * pName)
{
    Card* p = NULL;
    for(int i = 0; i < nCount; i++)
    {
        if(strcmp(pName,aCard[i].aName) == 0)
        {
            p=&aCard[i];
        }
    }
    if(p == NULL)
    {
        printf("未找到\n");
        return NULL;
    }
    else
    {
        return p;
    }
}