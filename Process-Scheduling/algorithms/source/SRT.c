#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../FileManager.h"
#include "../../process.h"

int main(int argc, char *argv[]) {
    FILE *file;
    char line[256];
    int i = 0, j = 0, n, e = 0, count = 0, prev = -1, ind = -1;
    Process *p = NULL;
    int *gantt = NULL;
    int *turnaroundTimes = NULL;

    // checking if the configuration file exists or not
    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    // get the total number of processes
    n = getProcessnbFromFile(argv[1]);

    // allocating memory for the tables used
    p = (Process *)malloc(sizeof(Process) * n);
    turnaroundTimes = (int *)malloc(sizeof(int) * n);

    // print all information about the different processes
    printf("\t     Welcome to Shortest Remaining Time (SRT) Algorithm\n");
    puts("\t¤_____¤______________¤____________¤__________¤");
    printf("\t| %-2s | %-12s | %-10s | %-8s |\n", "PID", "Arrival Time", "Burst Time", "Priority");
    puts("\t¤_____¤______________¤____________¤__________¤");

    while (fgets(line, sizeof(line), file)) {
        char firstChar = line[0];
        if ((firstChar != '#') && (strlen(line) > 2)) {
            char d[] = " ";
            strcpy(p[i].pid, strtok(line, d));
            p[i].t_arv = atoi(strtok(NULL, d));
            p[i].t_exec = atoi(strtok(NULL, d));
            p[i].priorite = atoi(strtok(NULL, d));
            p[i].rnt = p[i].t_exec;
            printf("\t| %-3s | %-12d | %-10d | %-8d |\n", p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
            i++;
        }
    }

    puts("\t¤_____¤______________¤_____________¤_________¤");
    fclose(file);

    gantt = (int *)malloc(n * 2 * sizeof(int));

    int total_exec = 0;
    for (i = 0; i < n; i++) {
        total_exec = total_exec + p[i].t_exec;
    }

    while (j < n) {
        int minRemainingTime = 1000;
        if (count == total_exec) {
            break;
        }

        for (i = 0; i < n; i++) {
            if (p[i].t_arv <= count && p[i].rnt > 0 && p[i].rnt < minRemainingTime) {
                ind = i;
                minRemainingTime = p[i].rnt;
            }
        }

        if (ind != -1) {
            p[ind].rnt -= 1;

            if (ind != prev) {
                gantt[e * 2 + 0] = ind + 1;
                gantt[((e++) * 2) + 1] = count;
            }
        }

        count++;

        if (p[ind].rnt == 0 && ind != -1) {
    j++;
    if (ind != -1) {
    turnaroundTimes[ind] = count - p[ind].t_arv;
}
}

        prev = ind;
    }

    gantt[e * 2 + 1] = count;
    if (ind != -1) {
    turnaroundTimes[ind] = count - p[ind].t_arv;
}
    printf("\n\nThe Gantt chart is:\n");
    printf(" ");
    for (i = 0; i < e; i++) {
        printf(" ¤---¤  ");
    }
    printf("\n");

    for (i = 0; i < e; i++) {
        printf("|  P%d\t", gantt[i * 2 + 0]);
    }

    printf("|\n ");
    for (i = 0; i < e; i++) {
        printf(" ¤---¤  ");
    }
    printf("|\n ");

    for (i = 0; i <= e; i++) {
        printf("%d\t", gantt[i * 2 + 1]);
    }

    printf("\n\n");
    printf("\t¤_____¤______________¤____________¤________________¤______________¤\n");
    printf("\t| %-2s | %-12s | %-10s | %-14s | %-14s |\n", "PID", "Arrival Time", "Burst Time", "Turnaround Time", "Wait Time");
    printf("\t¤_____¤______________¤____________¤________________¤______________¤\n");

    int totalTurnaroundTime = 0;
    int totalWaitTime = 0;

    for (i = 0; i < n; i++) {
        int waitTime = turnaroundTimes[i] - p[i].t_exec;
        totalTurnaroundTime += turnaroundTimes[i];
        totalWaitTime += waitTime;

        printf("\t| %-3s | %-12d | %-10d | %-14d | %-14d |\n", p[i].pid, p[i].t_arv, p[i].t_exec, turnaroundTimes[i], waitTime);

        if (i < n - 1) {
            printf("\t¤_____¤______________¤____________¤________________¤______________¤\n");
        }
    }

    double avgTurnaroundTime = (double)totalTurnaroundTime / n;
    double avgWaitTime = (double)totalWaitTime / n;

    printf("\n\nAverage Turnaround Time: %.2f", avgTurnaroundTime);
    printf("\nAverage Wait Time: %.2f\n", avgWaitTime);

    free(p);
    free(gantt);
    free(turnaroundTimes);

    return 0;
}

