#ifndef RECORD_H
#define RECORD_H

#define MAX_RECORDS 100

typedef struct
{
    int id;
    float amount;
    char type[20];
    char note[100];
} Record;

extern Record records[MAX_RECORDS];
extern int record_count;

void add_record();
void show_record();
void delete_record();

#endif