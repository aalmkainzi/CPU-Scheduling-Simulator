#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "scheduling/scheduling.h"
#include "processfiles.h"

FILE *get_pfile();

//TODO insert processes in sorted order (by AT) instead of insertion order
int main()
{
    while(true)
    {
        FILE *pfile = get_pfile();
        if(pfile == NULL)
        {
            puts("file not found");
            continue;
        }

        int size;
        process* processes_buffer = process_buffer_from(pfile, &size);
        fclose(pfile);

        puts("algorithm to simulate:\n"
             "1) FCFS\n"
             "2) non-Preemptive Priority\n"
             "3) Preemptive Priority\n"
             "4) Round-Robin\n"
             "5) SJF\n"
             "6) SRTF");

        char input = getc(stdin);
        getc(stdin); //to eat the '\n' after inserting into "char input"

        gantt_c gantt_chart;
        switch (input)
        {
            case '1':
            {
                fcfs_gantt_of(processes_buffer, size);
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
            default:
            {
                free(processes_buffer);
                continue;
            }
        }
        print_gantt(&gantt_chart);
        //free_gantt(&gantt_chart, true, true);
        free(processes_buffer);
    }
}

#define MAX_FILENAME 256
FILE* get_pfile()
{
    char fname[MAX_FILENAME] = {0};
    puts("enter file name containing processes list:");
    fgets(fname, MAX_FILENAME, stdin);
    FILE* file = fopen(fname, "r");
    return file;
}

