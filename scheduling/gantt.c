#include <stdlib.h>
#include <string.h>
#include "scheduling.h"

void print_metadata(process_metadata**pmd, int n);

void print_gantt(gantt_c*gantt_chart)
{
    int n_of_rects = gantt_chart->n_gp;
    gantt_p**g_processes = gantt_chart->gp;

    int n_of_pmd = gantt_chart->n_pmd;
    puts("");
    int total_time = 0;

    char* total_gantt_str;
    const int n_of_chars_in_gantt_rect = 19; //the maximum characters a process rect can have (not including its len)
    int gstrlen = 1;
    for (int i = 0; i < gantt_chart->n_gp; ++i)
        gstrlen = gstrlen + (gantt_chart->gp[i]->len*3 + n_of_chars_in_gantt_rect);

    total_gantt_str = calloc(gstrlen, sizeof(char));
    strcat(total_gantt_str, "0 ");

    system("cls");
    for (unsigned int i = 0; i < n_of_rects; ++i)
    {
        int rect_len = g_processes[i]->len*3;
        int pname_left_pad = rect_len % 2 == 0 ? rect_len / 2 : rect_len / 2 + 1;
        int pname_right_pad = strlen(g_processes[i]->name)==3 && g_processes[i]->len==1 ? 0 : rect_len / 2;

        char* current_gantt_str = calloc(gantt_chart->gp[i]->len * 3 + n_of_chars_in_gantt_rect, sizeof(char));

        sprintf(current_gantt_str, "|%*s%-*s|%s %d ",
                pname_left_pad,
                g_processes[i]->name,
                pname_right_pad,
                "",
               g_processes[i]->last ? "!" : "",
               total_time+g_processes[i]->len);

        strcat(total_gantt_str, current_gantt_str);
        puts(total_gantt_str);

        getchar(); //for user to press enter and go to next rect
        if(i!=n_of_rects-1)
            system("cls");
        total_time = total_time + g_processes[i]->len;
        free(current_gantt_str);
    }
    free(total_gantt_str);
    puts("");
    print_metadata(gantt_chart->pmd, n_of_pmd);
}

void free_gantt(gantt_c*gantt_chart, bool free_gp, bool free_pmd)
{
    if(free_gp)
        for (int i = 0; i < gantt_chart->n_gp; ++i)
            free(gantt_chart->gp[i]);
    if(free_pmd)
        for (int i = 0; i < gantt_chart->n_pmd; ++i)
            free(gantt_chart->pmd[i]);
    free(gantt_chart);
}

void print_metadata(process_metadata**pmd, int n)
{
    float avg_wt = 0;
    float avg_tat = 0;
    float avg_rt = 0;
    for (int i = 0; i < n; ++i)
    {
        printf("process %s:\n", pmd[i]->name);
        printf("wt = %d\n", pmd[i]->wt);
        printf("rt = %d\n", pmd[i]->rt);
        printf("tat = %d\n", pmd[i]->tat);
        printf("ct = %d\n\n", pmd[i]->ct);
        avg_wt+=pmd[i]->wt;
        avg_rt+=pmd[i]->rt;
        avg_tat+=pmd[i]->tat;
    }
    printf("avg wt = %.2f\navg rt = %.2f\navg tat = %.2f\n\n", avg_wt/n, avg_rt/n, avg_tat/n);
}