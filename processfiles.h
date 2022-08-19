#ifndef CPUSCHEDULERSIMULATOR_PROCESSFILES_H
#define CPUSCHEDULERSIMULATOR_PROCESSFILES_H
#include "scheduling/scheduling.h"
#include "data structs/growable array/growable_array.h"

void print_processes(process**processes, size_t size);
process** process_buffer_from(FILE*f,int*);

#endif
