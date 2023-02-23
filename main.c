#include <stdio.h>
void outputMenu();
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
            printf("添加卡\n");
            break;
        }
        case 2: // 查询卡
        {
            printf("查询卡\n");
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
            printf("退出\n");
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