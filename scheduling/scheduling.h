#ifndef CPUSCHEDULERSIMULATOR_SCHEDULING_H
#define CPUSCHEDULERSIMULATOR_SCHEDULING_H

#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include "../data structs/hashmap/hashmath/hashmath.h"

#define MAX_PROCESS_NAME 4

typedef struct
{
    char name[MAX_PROCESS_NAME];
    int AT;
    int BT;
    int P;
} process;

typedef struct
{
    char name[MAX_PROCESS_NAME];
    int bt; //this is the bt that the process started with and shouldn't be updated, unlike process.BT
    int wt;
    int tat;
    int ct;
    int rt;
} process_metadata;

typedef struct
{
    char name[MAX_PROCESS_NAME];
    int len;
    bool last;
} gantt_p;

typedef struct
{
    gantt_p* gp;
    int n_gp;
    process_metadata* pmd;
    int n_pmd;
} gantt_c;

gantt_c* fcfs_gantt_of(process*, int);
gantt_c* npp_gantt_of(process*, int);
gantt_c* pp_gantt_of(process*, int);
gantt_c* rr_gantt_of(process*, int, int);
gantt_c* sjf_gantt_of(process*, int);
gantt_c* srtf_gantt_of(process*, int);
void print_gantt(gantt_c*);
void free_gantt(gantt_c*, bool, bool);

int cmp_processes_at(const process*a, const process*b)
{
    return a->AT - b->AT;
}

bool pmd_equals(const char*p1_name, const char*p2_name)
{
    return !strcmp(p1_name,p2_name);
}

int hash_pmd(const char*p_name)
{
    return hash_str(p_name);
}

#endif