#include <stdlib.h>
#include <string.h>
#include "../scheduling.h"
#include "../../data structs/growable array/growable_array.h"

//TAT = WT + BT
//WT  = TAT - BT
//CT  = TAT + AT
//TAT = CT - AT we can use this
//RT  = TAT - BT
gantt_c* fcfs_gantt_of(process**a, int n)
{
    int (*cmp)(const process**, const process**) = &cmp_processes_at;
    msort(a, n, sizeof(process*), cmp);
    array* gantt_rects = init_array(n);
    process_metadata** pmd = calloc(n, sizeof(process_metadata*));

    for (int i = 0, time_passed = 0; i < n; ++i)
    {
        gantt_p* gp;
        if(a[i]->AT > time_passed)
        {
            if(!arr_empty(gantt_rects) && !strcmp(((gantt_p*)arr_get_last(gantt_rects))->name, ""))
            {
                ((gantt_p*)arr_get_last(gantt_rects))->len++;
            }
            else
            {
                gp = malloc(sizeof(gantt_p));
                gp->len = 1;
                gp->name = "";
                gp->last = false;
                arr_add(gantt_rects, gp);
            }
            i--;
            time_passed++;
        }
        else
        {
            gp = malloc(sizeof(gantt_p));
            gp->len = a[i]->BT;
            gp->name = a[i]->name;
            gp->last = true;
            arr_add(gantt_rects, gp);
            pmd[i] = malloc(sizeof(process_metadata));
            pmd[i]->ct = time_passed + a[i]->BT;
            pmd[i]->tat = pmd[i]->ct - a[i]->AT;
            pmd[i]->wt = pmd[i]->tat - a[i]->BT;
            pmd[i]->rt = pmd[i]->tat - a[i]->BT;
            pmd[i]->name = a[i]->name;

            time_passed = time_passed + a[i]->BT;
        }
    }

    shrink_to_fit(gantt_rects);

    gantt_c* gantt_chart = malloc(sizeof(gantt_c));
    gantt_chart->gp = (gantt_p**) gantt_rects->arr;
    gantt_chart->n_gp = gantt_rects->size;
    gantt_chart->pmd = pmd;
    gantt_chart->n_pmd = n;

    free(gantt_rects);
    return gantt_chart;
}