#include <stdio.h>
#include <stdlib.h>
#include "record.h"
#include "file.h"

int main()
{

    system("chcp 65001");

    load_from_file();

    int choice;

    while (1)
    {
        printf("\n==== 记账本系统 ====\n");
        printf("1. 添加账单\n");
        printf("2. 查看账单\n");
        printf("3. 删除账单\n");
        printf("4. 保存账单\n");
        printf("5. 退出\n");

        printf("请选择：");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_record();
            break;
        case 2:
            show_record();
            break;
        case 3:
            delete_record();
            break;
        case 4:
            save_to_file();
            break;
        case 5:
            return 0;
            break;
        default:
            printf("无效的选择！\n");
        }
    }

    return 0;
}