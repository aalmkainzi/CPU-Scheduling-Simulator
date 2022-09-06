#include "scheduling/scheduling.h"
#include "processfiles.h"
#include <stdlib.h>
#include <string.h>

process get_process(FILE*);
int peekf(FILE*);

process* process_buffer_from(FILE*f, int*size)
{
    array* processes = init_array(10, sizeof(process), NULL);
    while(peekf(f) != EOF)
    {
        process p = get_process(f);
        arr_add(processes, &p);
    }
    *size = processes->size;
    shrink_to_fit(processes);
    process* buffer = (process*) processes->arr;
    free(processes);
    return buffer;
}

void print_processes(process*processes, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        process pd = processes[i];
        printf("process %d:\nname: %s\tat: %d\tbt: %d\tp: %d\n", i, pd.name, pd.AT, pd.BT, pd.P);
    }
}

void add_process_name(FILE* f, process* pd)
{
    char p_name[MAX_PROCESS_NAME] = {0};
    int name_len = 0;
    char c;
    while((c = fgetc(f))!=',' && name_len < MAX_PROCESS_NAME - 1)
    {
        p_name[name_len++] = c;
    }
    memcpy(pd->name, p_name, MAX_PROCESS_NAME);
}

#define MAX_NUMLEN 11

void add_process_at(FILE*f, process* pd)
{
    char AT_str[MAX_NUMLEN] = {0};
    int num_len = 0;
    char c;
    while((c = fgetc(f))!=',' && num_len < MAX_NUMLEN-1)
    {
        AT_str[num_len++] = c;
    }
    pd->AT = atoi(AT_str);
}

void add_process_bt(FILE*f, process* pd)
{
    char BT_str[MAX_NUMLEN] = {0};
    int num_len = 0;
    char c;
    while((c = fgetc(f))!=',' && num_len < MAX_NUMLEN-1 && c!='\n' && c!=EOF)
    {
        BT_str[num_len++] = c;
    }
    pd->BT = atoi(BT_str);
}

void add_process_p(FILE*f, process* pd)
{
    fseek(f, -1, SEEK_CUR);
    char p_check = fgetc(f);
    if(p_check == '\n')
    {
        pd->P = 0;
        return;
    }
    char P_str[MAX_NUMLEN] = {0};
    int num_len = 0;
    char c;
    while((c = fgetc(f))!=EOF && c!='\n' && num_len < MAX_NUMLEN-1)
    {
        P_str[num_len++] = c;
    }
    pd->P = atoi(P_str);
}

process get_process(FILE*f)
{
    process pd;
    add_process_name(f, &pd);
    add_process_at(f, &pd);
    add_process_bt(f, &pd);
    add_process_p(f, &pd);
    return pd;
}

int peekf(FILE*file)
{
    int c = fgetc(file);
    if(c!=EOF)
        fseek(file, -1*sizeof(char), SEEK_CUR);
    return c;
}