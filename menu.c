#include <stdio.h>
#include <string.h>
#include <time.h>
#include "model.h"
#include "card_service.h"
#include "menu.h"
#include "tool.h"
void outputMenu()
{
    // 输出系统菜单
    printf("----------菜单----------\n");
    printf("1.添加卡\n");
    printf("2.查询卡\n");
    printf("3.上机\n");
    printf("4.下机\n");
    printf("5.充值\n");
    printf("6.退费\n");
    printf("7.查询统计\n");
    printf("8.注销卡\n");
    printf("0.退出\n");

    // 提示选择菜单编号
    printf("请选择菜单项编号(0~8):\n");
}
// 该函数为添加卡函数，提示并接受输入的卡信息，将卡信息保存到结构体中，并显示卡信息。
void add()
{
    struct Card card;
    char aName[36] = {'\0'};
    char aPwd[20] = {'\0'};
    printf("---------添加卡---------\n");
    printf("请输入卡号:\n");
    scanf("%s", aName);
    // 判断卡号或者密码长度
    while (getSize(aName) > 18)
    {
        printf("输入的卡号长度超过最大值!\n");
        printf("请重新输入卡号:\n");
        scanf("%s", aName);
    }
    // 将输入的卡号保存到结构体中
    strcpy(card.aName, aName);
    printf("请输入密码:\n");
    scanf("%s", aPwd);
    // 提示并接受输入密码
    while (getSize(aPwd) > 8)
    {
        printf("输入的密码长度超过最大值!\n");
        printf("请重新输入密码:\n");
        scanf("%s", aPwd);
    }
    strcpy(card.aPwd, aPwd);
    // 将输入的密码保存到结构体中
    printf("请输入开卡金额:\n");
    scanf("%e", &card.fBalance);
    card.fTotalUse = card.fBalance;
    card.nUseCount = 0;
    card.nStatus = 0;
    card.nDel = 0;
    card.tStart = card.tEnd = card.tLastTime = time(NULL);
    addCard(card);
    // 输出卡信息:
    printf("-----添加的卡信息如下:-----\n");
    printf("卡号:\n");
    printf("%s\n", card.aName);
    printf("密码:\n");
    printf("%s\n", card.aPwd);
    printf("卡状态:\n");
    printf("%d\n", card.nStatus);
    printf("余额:\n");
    printf("%0.1f\n", card.fBalance);
    printf("-------------------------\n");
}
// 该函数计算字符串指针pInfo，所指向的字符串中的字符的个数。
int getSize(const char *pInfo)
{
    int nSize = 0;
    while (*(pInfo + nSize) != '\0')
    {
        nSize++;
    }
    return nSize;
}
void query()
{
    char aName[18] = {0};
    char aTime[20] = {0};
    Card *pCard = NULL;
    int nIndex = 0;

    printf("----------查询卡----------\n");

    // 提示并接收输入的卡信息
    printf("请输入查询的卡号:(长度为1~18)\n");
    scanf("%s", aName);

    // 查询卡
    pCard = queryCards(aName, &nIndex);

    // 如果pCard==NULLb,表示没有该卡的信息

    if (pCard == NULL || nIndex == 0)
    {
        printf("没有该卡的信息!\n");
    }
    else
    {
        printf("查询到的卡信息如下:\n");
        int count = 0; // 这里为了好看增加了这个
        for (int i = 0; i < nIndex; i++)
        {
            // 输出表格
            //  将时间转换为字符串
            count = count + 1;
            timeToString(pCard[i].tLastTime, aTime);
            printf("----------查到的第%d张卡----------\n", count);
            printf("卡号:\n");
            printf("%s\n", pCard[i].aName);
            printf("状态:\n");
            printf("%d\n", pCard[i].nStatus);
            printf("余额:\n");
            printf("%0.1f\n", pCard[i].fBalance);
            printf("累计使用:\n");
            printf("%0.1f\n", pCard[i].fTotalUse);
            printf("使用次数:\n");
            printf("%d\n", pCard[i].nUseCount);
            printf("上次使用时间\n");
            printf("%s\n", aTime);
            printf("---------------------------------\n");
        }
    }
}
void exitApp()
{
    releaseCardList();
}