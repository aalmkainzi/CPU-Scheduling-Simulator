#include <corecrt.h>
#include <string.h>
#include "../scheduling.h"
#include "../../data structs/dynamic array/array.h"
#include "../../data structs/priority queue BST/priorityqueuebst.h"
#include "../../data structs/hashmap/hashmap.h"


//TODO make a reusable function in scheduling.h that can is a generic priority member function =>
//priority_scheduling(process*a, int n, int offset) where offset is where the member to prioritize is in relation to the beginning of the process
gantt_c srtf_gantt_of(process*a, int n)
{
    msort(a, n, sizeof(process*), cmp_AT_func);

    priority_queue_bst* arrived_processes = init_pqbst();

    bool (*equals)(const void*, const void**) = &pmd_equals;
    size_t (*hash)(const void*) = &hash_pmd;
    hashmap* pmd_hm = init_hashmap(n, equals, hash);

    array* gantt_rects = init_array(n);

    process* current_job = NULL;
    for (int i = 0, time_passed = 0; !pqbst_empty(arrived_processes) || i < n || current_job; )
    {
        if(i < n && a[i]->AT <= time_passed)
        {
            pqbst_add_p(arrived_processes, a[i], a[i]->BT);
            i++;
            continue;
        }

        if((!pqbst_empty(arrived_processes) && !current_job) ||
           (!pqbst_empty(arrived_processes) && ((process*) pqbst_peek(arrived_processes))->BT < current_job->BT))
        {
            if(current_job)
                pqbst_add_p(arrived_processes, current_job, current_job->BT);
            current_job = pqbst_poll(arrived_processes);
        }

        if(current_job)
        {
            gantt_p* prev = (gantt_p *) arr_get_last(gantt_rects);
            if(prev && !strcmp(prev->name, current_job->name))
            {
                prev->len++;
                prev->last = current_job->BT == 1;
            }
            else
            {
                gantt_p* gp = malloc(sizeof(gantt_p));
                gp->name = current_job->name;
                gp->len = 1;
                gp->last = current_job->BT == 1;
                arr_add(gantt_rects, gp);
            }

            process_metadata* pmd;
            if(!hashmap_contains_key(pmd_hm, current_job->name))
            {
                pmd = malloc(sizeof(process_metadata));
                pmd->name = current_job->name;
                pmd->bt = current_job->BT;
                pmd->rt = time_passed;
                hashmap_add(pmd_hm, pmd->name, pmd);
            }
            else
            {
                pmd = hashmap_get_val_of(pmd_hm, current_job->name);
            }

            current_job->BT--;
            if(current_job->BT==0)
            {
                pmd->ct = time_passed+1;
                pmd->tat = pmd->ct - current_job->AT;
                pmd->wt = pmd->tat - pmd->bt;
                current_job = NULL;
            }
        }
        else
        {
            gantt_p* prev = arr_get_last(gantt_rects);
            if(prev && (prev->name[0])=='\0')
            {
                prev->len++;
            }
            else
            {
                gantt_p* gp = malloc(sizeof(gantt_p));
                gp->name = "";
                gp->last = false;
                gp->len = 1;
                arr_add(gantt_rects, gp);
            }
        }
        time_passed++;
    }

    free_pqbst(arrived_processes, false);
    gantt_c* gantt_chart = malloc(sizeof(gantt_c));
    shrink_to_fit(gantt_rects);
    gantt_chart->gp = gantt_rects->arr;
    gantt_chart->n_gp = gantt_rects->size;
    free(gantt_rects);
    process_metadata** pmd_arr = calloc(n, sizeof(process_metadata*));
    hashmap_to_arr(pmd_hm, pmd_arr);
    free_hashmap(pmd_hm, false, false);
    gantt_chart->pmd = pmd_arr;
    gantt_chart->n_pmd = n;

    return gantt_chart;
}