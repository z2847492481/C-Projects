#include <stdio.h>
#include "record.h"
#include "file.h"

void save_to_file()
{
    FILE *fp = fopen("data.txt", "w");

    if (fp == NULL)
    {
        printf("文件打开失败!\n");
        return;
    }

    for (int i = 0; i < record_count; i++)
    {
        fprintf(
            fp,
            "%d %.2f %s %s\n",
            records[i].id,
            records[i].amount,
            records[i].type,
            records[i].note);
    }

    fclose(fp);

    printf("保存成功!\n");
}

void load_from_file()
{
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        printf("文件打开失败!\n");
        return;
    }

    while (
        fscanf(
            fp,
            "%d %f %s %s",
            &records[record_count].id,
            &records[record_count].amount,
            records[record_count].type,
            records[record_count].note) == 4)
    {
        record_count++;
    }

    fclose(fp);
}