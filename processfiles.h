#ifndef CPUSCHEDULERSIMULATOR_PROCESSFILES_H
#define CPUSCHEDULERSIMULATOR_PROCESSFILES_H
#include "scheduling/scheduling.h"
#include "data structs/dynamic array/array.h"

void print_processes(process*, size_t);
process* process_buffer_from(FILE*,int*);

#endif
