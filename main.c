#include <stdio.h>
#include "menu.h"
#include "model.h"
#include "card_file.h"
#include "card_service.h"
#include "tool.h"
int main()
{
    int nSelection = -1; // 输入菜单项编号
    printf("\n欢迎进入计费管理系统\n");
    printf("\n");

    do
    {
        // 输出系统菜单
        outputMenu();
        // 输入菜单项编号
        scanf("%d", &nSelection);

        // 输出选择的菜单编号
        switch (nSelection)
        {
        case 1: // 添加卡
        {
            add();
            break;
        }
        case 2: // 查询卡
        {
            query();
            break;
        }
        case 3: // 上机
        {
            printf("上机\n");
            break;
        }
        case 4: // 下机
        {
            printf("下机\n");
            break;
        }
        case 5: // 充值
        {
            printf("充值\n");
            break;
        }
        case 6: // 退费
        {
            printf("退费\n");
            break;
        }
        case 7: // 查询统计
        {
            printf("查询统计\n");
            break;
        }
        case 8: // 注销卡
        {
            printf("注销卡\n");
            break;
        }
        case 0: // 退出
        {
            exitApp();
            break;
        }
        default:
        {
            printf("输入的菜单序号错误!\n");
            break;
        }
        }
        printf("\n");
    } while (nSelection != 0);

    return 0;
}
