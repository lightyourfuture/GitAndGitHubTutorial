#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "model.h"
#include "global.h"
#include "tool.h"
#include "global.h"
#define CARDCHARNUM 256
Card praseCard(char *pBuf);
int saveCard(const Card *pCard, const char *pPath)
{
    // 将卡信息保存到文本文件中
    FILE *fp = NULL;                  // 文件结构体指针
    char startTime[TIMELENGTH] = {0}; // 开卡时间
    char endTime[TIMELENGTH] = {0};   // 截止时间
    char lastTime[TIMELENGTH] = {0};  // 最后使用时间
    // 以追加的模式打开文件,如果打开失败,这一只写的模式打开文件
    if ((fp = fopen(pPath, "a")) == NULL)
    {
        if ((fp = fopen(pPath, "w")) == NULL)
        {
            return FALSE;
        }
    }
    // 将时间转换为字符串
    timeToString(pCard->tStart, startTime);
    timeToString(pCard->tEnd, endTime);
    timeToString(pCard->tLastTime, lastTime);
    // 将数据写进文件
    // 一张卡的每个信息间用“##”分隔，保存格式如下：
    // 卡号##密码##状态##开卡时间##截止时间##累积金额##最后使用时间##使用次数##当前余额##删除标识
    fprintf(fp, "%s##%s##%d##%lld##%lld##%.1f##%lld##%d##%.1f##%d\n", pCard->aName, pCard->aPwd, pCard->nStatus, pCard->tStart, pCard->tEnd, pCard->fTotalUse, pCard->tLastTime, pCard->nUseCount, pCard->fBalance, pCard->nDel);
    // 关闭文件
    fclose(fp);
    return TRUE; // 搭建程序结构时,暂时直接返回TRUE
}

int readCard(Card *pCard, const char *pPath)
{
    // 从文件中读取卡信息
    // 卡号1#密码1##状态1#开卡时间1#截止时间1#累积金额1#最后使用时间1#使用次数1#余额1#删除标识1
    // 卡号2##密码2#状态2#开卡时间2##截止时间2累积金额2##最后使用时间2#使用次数2I余额2#删除标识2
    FILE *fp = NULL;
    char aBuf[CARDCHARNUM] = {0};
    // 打开文件
    fp = fopen(pPath, "r");
    if (fp == NULL)
    {
        return FALSE;
    }
    int i = 0;
    // 读取文件
    // 从文件中逐行读取文件
    // 调用praseCard(),解析读取的卡信息
    while (!feof(fp))
    {
        memset(aBuf, 0, CARDCHARNUM); // 清空数组
        if (fgets(aBuf, CARDCHARNUM, fp) != NULL)
        {
            if (strlen(aBuf) > 0)
            {
                pCard[i] = praseCard(aBuf);
                i++;
            }
        }
    }
    // 关闭文件
    fclose(fp);
    return TRUE;
}
// 解析从文件读取的卡信息
Card praseCard(char *pBuf)
{
    Card card;
    const char *delims = "##"; // 字符串中的分隔符
    char *buf = NULL;
    char *str = NULL;
    char flag[10][20] = {0}; // 保存分割后的字符串
    int index = 0;
    buf = pBuf;                // 第一次调用strok时,buf为解析字符串
    str = strtok(buf, delims); // 这里不是str = strtok(pBuf, delims)
    while (str != NULL)
    {
        strcpy(flag[index], str);
        buf = NULL; // 后面调用strtok函数时,第一个参数为NULL
        index++;
        str = strtok(buf, delims); // 这里漏了这一句
    }
    // 原本视频给的代码,编译器警告提示buf定义后未使用(warning: variable 'buf' set but not used [-Wunused-but-set-variable])
    // char *buf = NULL;
    // char *str = NULL;
    // char flag[10][20] = {0}; // 保存分割后的字符串
    // int index = 0;
    // buf = pBuf; // 第一次调用strok时,buf为解析字符串
    // str = strtok(buf, delims);
    // while ( str!= NULL)
    // {
    //     strcpy(flag[index], str);
    //     buf = NULL; // 后面调用strtok函数时,第一个参数为NULL
    //     index++;
    //     str = strtok(buf,delims);
    // }
    // 我查了一下strtok()函数的用法:
    // 声明
    // 下面是 strtok() 函数的声明。
    // char *strtok(char *str, const char *delim)
    // 参数
    // str -- 要被分解成一组小字符串的字符串。
    // delim -- 包含分隔符的 C 字符串。
    // 返回值
    // 该函数返回被分解的第一个子字符串，如果没有可检索的字符串，则返回一个空指针。

    // 实例
    // 下面的实例演示了 strtok() 函数的用法。

    // 实例
    // #include <string.h>
    // #include <stdio.h>
    // int main ()
    // {
    //    char str[80] = "This is - www.runoob.com - website";
    //    const char s[2] = "-";
    //    char *token;
    //    /* 获取第一个子字符串 */
    //    token = strtok(str, s);
    //    /* 继续获取其他的子字符串 */
    //    while( token != NULL )
    //    {
    //       printf( "%s\n", token );
    //       token = strtok(NULL, s);
    //    }
    //    return(0);
    // }
    // 让我们编译并运行上面的程序，这将产生以下结果：

    // This is
    // www.runoob.com
    // website

    strcpy(card.aName, flag[0]);
    strcpy(card.aPwd, flag[1]);
    card.nStatus = atoi(flag[2]);           // 状态
    card.tStart = stringToTime(flag[3]);    // 开卡时间
    card.tEnd = stringToTime(flag[4]);      // 截止时间
    card.fTotalUse = (float)atof(flag[5]);  // 累计金额
    card.tLastTime = stringToTime(flag[6]); // 最后使用时间
    card.nUseCount = atoi(flag[7]);         // 使用次数
    card.fBalance = (float)atof(flag[8]);   // 余额
    card.nDel = atoi(flag[9]);              // 删除标识
    return card;
}
int getCardCount(const char *pPath)
{
    FILE *fp = NULL;
    char aBuf[CARDCHARNUM] = {0};
    int nCount = 0;
    // 打开文件
    fp = fopen(pPath, "r");
    if (fp == NULL)
    {
        return FALSE;
    }
    // 读取文件
    while (!feof(fp))
    {
        memset(aBuf, 0, CARDCHARNUM); // 清空数组
        if (fgets(aBuf, CARDCHARNUM, fp) != NULL)
        {
            if (strlen(aBuf) > 0)
            {
                nCount++;
            }
        }
    }
    // 关闭文件
    fclose(fp);
    return nCount;
}
