#include <stdio.h>
#include <stdbool.h>
#include "data structs/growable array/growable_array.h"
#include <string.h>
#include "scheduling/scheduling.h"
#include "processfiles.h"

#define MAX_FILENAME 51

//TODO implement process auto-naming if a single process name is invalid (e.g. if a process name is q_empty then name all processes "%c%d", p_num)

FILE *get_pfile();

int main()
{
    while(true)
    {
        FILE *file = get_pfile();
        if(file == NULL)
        {
            puts("file not found");
            continue;
        }

        int size;
        process** processes_buffer = process_buffer_from(file, &size);
        fclose(file);

        puts("algorithm to simulate:\n"
             "1) FCFS\n"
             "2) non-Preemptive Priority\n"
             "3) Preemptive Priority\n"
             "4) Round-Robin\n"
             "5) SJF\n"
             "6) SRTF");

        char input = getc(stdin);
        getc(stdin); //to eat the '\n' after inserting into "char input"

        gantt_c* gantt_chart;
        switch (input)
        {
            case '1':
            {
                gantt_chart = fcfs_gantt_of(processes_buffer, size);
                break;
            }
            case '2':
            {
                gantt_chart = npp_gantt_of(processes_buffer, size);
                break;
            }
            case '3':
            {
                gantt_chart = pp_gantt_of(processes_buffer, size);
                break;
            }
            case '4':
            {
                printf("enter time quantum: ");
                int tq;
                scanf("%d", &tq);
                gantt_chart = rr_gantt_of(processes_buffer, size, tq);
                break;
            }
            case '5':
            {
                gantt_chart = sjf_gantt_of(processes_buffer, size);
                break;
            }
            case '6':
            {
                gantt_chart = srtf_gantt_of(processes_buffer, size);
                break;
            }
            default: gantt_chart = NULL;
        }

        if(gantt_chart)
        {
            print_gantt(gantt_chart);
            free_gantt(gantt_chart, true, true);
        }
        free_processes((process**)processes_buffer, size, true);
    }
}

FILE *get_pfile()
{
    char* fname = malloc(MAX_FILENAME);
    puts("enter file name containing processes data:");
    fgets(fname, MAX_FILENAME, stdin);
    size_t len = strlen(fname);
    fname[len - 1] = '\0';
    fname = realloc(fname, len);
    FILE* file = fopen(fname, "r");
    free(fname);
    return file;
}

