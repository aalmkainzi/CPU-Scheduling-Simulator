#include <string.h>
#include "../scheduling.h"
#include "../../data structs/dynamic array/array.h"
#include "../../data structs/linked structs/linked queue/linkedqueue.h"
#include "../../data structs/hashmap/hashmap.h"

gantt_c* rr_gantt_of(process*a, int n, int tq)
{
    int (*cmp)(const process*, const process*) = &cmp_processes_at;

    msort(a, n, sizeof(process*), cmp);

    array* gantt_rects = init_array(n, sizeof(gantt_p), NULL);
    
    queue* arrived_processes = init_queue();

    bool (*equals)(const char*, const char*) = &pmd_equals;
    int (*hash)(const char*p_name) = &hash_str;
    hashmap pmd_hm;
    set_hashmap(&pmd_hm ,n, equals, hash, sizeof(char)*4, sizeof(process_metadata));
    for (int i = 0, time_passed = 0; !q_empty(arrived_processes) || i < n; )
    {
        if(i < n && a[i].AT <= time_passed)
        {
            enqueue(arrived_processes, a+i);
            i++;
            continue;
        }

        gantt_p gp;

        if(!q_empty(arrived_processes))
        {
            process* job = dequeue(arrived_processes);
            if(job->BT - tq <= 0)
            {
                if(hashmap_contains_key(&pmd_hm, job->name))
                {
                    process_metadata* pmd = hashmap_get_val_of(&pmd_hm, job->name);
                    pmd->ct = time_passed + job->BT;
                    pmd->tat = pmd->ct - job->AT;
                    pmd->wt = pmd->tat - pmd->bt;
                    time_passed = time_passed + job->BT;

                    if(!strcmp(((gantt_p*)arr_get_last(gantt_rects))->name, job->name))
                    {
                        ((gantt_p*)arr_get_last(gantt_rects))->len += job->BT;
                    }
                    else
                    {
                        memcpy(gp.name, job->name, MAXPNAME);
                        gp.len = job->BT;
                        gp.last = true;
                        arr_add(gantt_rects, &gp);
                    }
                }
                else
                {
                    process_metadata pmd;
                    memcpy(pmd.name, job->name, MAXPNAME);
                    pmd.rt = time_passed;
                    pmd.bt = job->BT;
                    pmd.ct = time_passed + pmd.bt;
                    pmd.tat = pmd.ct - job->AT;
                    pmd.wt = pmd.tat - pmd.bt;
                    hashmap_add(&pmd_hm, pmd.name, &pmd);
                    time_passed = time_passed + job->BT;
                    gp.len = job->BT;
                    gp.last = true;
                    memcpy(gp.name, job->name, MAXPNAME);
                    arr_add(gantt_rects, &gp);
                }
            }
            else
            {
                if(!hashmap_contains_key(&pmd_hm, job->name))
                {
                    process_metadata* pmd = calloc(1, sizeof(process_metadata));
                    memcpy(pmd->name, job->name, MAXPNAME);
                    pmd->rt = time_passed;
                    pmd->bt = job->BT;
                    hashmap_add(&pmd_hm, job->name, pmd);
                }

                if(!arr_empty(gantt_rects) && !strcmp(((gantt_p*)arr_get_last(gantt_rects))->name, job->name))
                {
                    ((gantt_p*)arr_get_last(gantt_rects))->len += tq;
                }
                else
                {
                    gp.last = false;
                    gp.len = tq;
                    memcpy(gp.name, job->name, MAXPNAME);
                    arr_add(gantt_rects, &gp);
                }

                time_passed = time_passed + tq;
                job->BT = job->BT - tq;

                while(i < n && a[i].AT <= time_passed)
                {
                    enqueue(arrived_processes, &a[i]);
                    i++;
                }
                enqueue(arrived_processes, job);
            }
        }
        else
        {
            if(!arr_empty(gantt_rects) && !strcmp(((gantt_p*)arr_get_last(gantt_rects))->name, "")) //if prev rect is empty, extend it
            {
                ((gantt_p*)arr_get_last(gantt_rects))->len++;
            }
            else
            {
                memset(gp.name, 0, MAXPNAME); //this instead? => gp.name[0] = 0;
                gp.last = false;
                gp.len = 1;
                arr_add(gantt_rects, &gp);
            }
            time_passed++;
        }
    }
    free_q(arrived_processes, false);
    process_metadata* pmd_arr = calloc(n, sizeof(process_metadata));
    hashmap_to_arr(&pmd_hm, pmd_arr);
    free_hashmap(&pmd_hm);
    gantt_c* gantt_chart = malloc(sizeof(gantt_c));
    shrink_to_fit(gantt_rects);
    gantt_chart->gp = (gantt_p*) gantt_rects->arr;
    gantt_chart->n_gp = gantt_rects->size;
    free(gantt_rects);
    gantt_chart->pmd = pmd_arr;
    gantt_chart->n_pmd = n;

    return gantt_chart;
}