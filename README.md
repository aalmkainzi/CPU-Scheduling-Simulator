# CPU-Scheduling-Simulator
C program to simulate scheduling algorithms (FCFS, non-preemptive priority, preemptive priority, RR, SJF, SRTF)

the input file format is:

name,arrival time,burst time,priority
  
name must be no more than 3 characters. If no priority is provided then it will be 0

for example:

P1,0,4,3
P2,11,5,1
P3,5,2,1
Z99,21,30,0

in the last line we could instead say:
Z99,21,30
since omitting the priority will result in priority being 0
