#ifndef PROCESS_H
#define PROCESS_H

#define True 1
#define False 0
typedef struct _process{
    char pid[5];    //process name
    int t_arv;      // arrival time
    int t_exec;     // burst time
    int priorite;   // priority value ; needed for priority scheduling (lower the value higher the priority)
    int rnt;        // remaining burst time ; needed for SRT and RR
}Process;
typedef int quantum;
#endif