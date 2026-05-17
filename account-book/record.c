#include <stdio.h>
#include <string.h>
#include "record.h"

Record records[MAX_RECORDS];
int record_count = 0;
void add_record() { 
    Record r;
    r.id = record_count + 1;
    printf("请输入金额: ");
    scanf("%f", &r.amount);

    printf("请输入类型(收入/支出): ");
    scanf("%s", r.type);

    printf("请输入备注: ");
    scanf("%s", r.note);

    records[record_count++] = r;
    printf("添加成功!\n");
}

void show_record() { 
    printf("\n==== 账单列表 ====\n");
    for (int i = 0; i < record_count; i++){
        printf(
            "%d\t%s\t%.2f\t%s\n",
            records[i].id,
            records[i].type,
            records[i].amount,
            records[i].note
        );
    }
}

void delete_record() { 
    int id;
    printf("请输入要删除的ID: ");
    scanf("%d", &id);

    int found = 0;

    for (int i = 0; i < record_count; i++){
        if (records[i].id == id) {
            for(int j = i; j < record_count - 1; j++) {
                records[j] = records[j + 1];
            }
            record_count--;
            found = 1;
            printf("删除成功!\n");
            break;
        }
    }
    if (!found) {
        printf("未找到该ID!\n");
    }
}