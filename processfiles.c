#include "scheduling/scheduling.h"
#include "processfiles.h"

process* get_process(FILE*);
int peekf(FILE*);

process** process_buffer_from(FILE*f, int*size)
{
    array* buffer = init_array(10);
    while(peekf(f) != EOF)
    {
        arr_add(buffer, get_process(f));
    }
    *size = buffer->size;
    process **rtr_arr = (process**) buffer->arr;
    free(buffer);
    return rtr_arr;
}

void print_processes(process**processes, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        process* pd = processes[i];
        printf("process %d:\nname: %s\tat: %d\tbt: %d\tp: %d\n", i, pd->name, pd->AT, pd->BT, pd->P);
    }
}

void free_processes(process** processes, int n, bool free_arr)
{
    for (int i = 0; i < n; ++i)
    {
        free(processes[i]->name);
        free(processes[i]);
    }
    if(free_arr)
        free(processes);
}

#define MAX_PNAME 4

void add_process_name(FILE* f, process* pd)
{
    char* p_name = calloc(MAX_PNAME, sizeof(char));
    int name_len = 0;
    char c;
    while((c = fgetc(f))!=',' && name_len<MAX_PNAME)
    {
        p_name[name_len++] = c;
    }
    p_name = realloc(p_name, name_len+1);
    pd->name = p_name;
}

#define MAX_NUMLEN 11

void add_process_at(FILE*f, process* pd)
{
    char* AT_str = calloc(MAX_NUMLEN, sizeof(char));
    int num_len = 0;
    char c;
    while((c = fgetc(f))!=',' && num_len < MAX_NUMLEN)
    {
        AT_str[num_len++] = c;
    }
    AT_str = realloc(AT_str, num_len + 1);
    pd->AT = atoi(AT_str);
    free(AT_str);
}

void add_process_bt(FILE*f, process* pd)
{
    char* BT_str = calloc(MAX_NUMLEN, sizeof(char));
    int num_len = 0;
    char c;
    while((c = fgetc(f))!=',' && c!='\n' && c!=EOF)
    {
        BT_str[num_len++] = c;
    }
    BT_str = realloc(BT_str, num_len + 1);
    pd->BT = atoi(BT_str);
    free(BT_str);
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
    char* P_str = calloc(11, sizeof(char));
    int num_len = 0;
    char c;
    while((c = fgetc(f))!=EOF && c!='\n' && num_len < MAX_NUMLEN)
    {
        P_str[num_len++] = c;
    }
    P_str = realloc(P_str, num_len + 1);
    pd->P = atoi(P_str);
    free(P_str);
}

process* get_process(FILE*f)
{
    process* pd = malloc(sizeof(process));
    add_process_name(f, pd);
    add_process_at(f, pd);
    add_process_bt(f, pd);
    add_process_p(f,pd);
    return pd;
}

int peekf(FILE*file)
{
    int c = fgetc(file);
    if(c!=EOF)
        fseek(file, -1*sizeof(char), SEEK_CUR);
    return c;
}