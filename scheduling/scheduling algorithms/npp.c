#include <stdlib.h>
#include "../scheduling.h"
#include "../../data structs/dynamic array/array.h"
#include "../../data structs/priority queue BST/priorityqueuebst.h"
#include <string.h>


//TAT = CT - AT
//WT = TAT - BT
//RT = WT
gantt_c* npp_gantt_of(process*a, int n)
{
    int (*cmp)(const process**, const process**) = &cmp_processes_at;
    msort(a, n, sizeof(process*), cmp);
    priority_queue_bst* arrived_processes = init_pqbst();
    array* gantt_rects = init_array(n);

    process_metadata** pmd = calloc(n, sizeof(process_metadata*));

    for (int i = 0, p = 0, time_passed = 0; p < n; )
    {
        if(i < n && a[i]->AT <= time_passed)
        {
            pqbst_add_p(arrived_processes, a[i], a[i]->P);
            i++;
            if(i < n && a[i+1]->AT <= time_passed)
                continue;
        }
        if(!pqbst_empty(arrived_processes))
        {
            process* job = pqbst_poll(arrived_processes);
            gantt_p* gp = malloc(sizeof(gantt_p));
            gp->len = job->BT;
            gp->name = job->name;
            gp->last = true;
            arr_add(gantt_rects, gp);
            time_passed = time_passed + gp->len;

            pmd[p] = malloc(sizeof(process_metadata));
            pmd[p]->name = gp->name;
            pmd[p]->ct = time_passed;
            pmd[p]->tat = pmd[p]->ct - job->AT;
            pmd[p]->wt = pmd[p]->tat - job->BT;
            pmd[p]->rt = pmd[p]->wt;
            p++;
        }
        else
        {
            if(!arr_empty(gantt_rects) && (((gantt_p*) arr_get_last(gantt_rects))->name[0]) == '\0')
            {
                ((gantt_p*) arr_get_last(gantt_rects))->len++;
            }
            else
            {
                gantt_p *gp = malloc(sizeof(gantt_p));
                gp->len = 1;
                gp->name = "";
                gp->last = false;
                arr_add(gantt_rects, gp);
            }
            time_passed++;
        }
    }
    shrink_to_fit(gantt_rects);

    gantt_c* gantt_chart = malloc(sizeof(gantt_c));
    gantt_chart->gp = (gantt_p**) gantt_rects->arr;
    gantt_chart->n_gp = gantt_rects->size;
    gantt_chart->pmd = pmd;
    gantt_chart->n_pmd = n;

    free_pqbst(arrived_processes, false);
    free(gantt_rects);

    return gantt_chart;
}