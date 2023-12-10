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
    int *turnaroundTimes = NULL; // Ajout du tableau pour stocker les temps de rotation

    // checking if the configuration file exists or not
    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    // get the total number of processes
    n = getProcessnbFromFile(argv[1]);

    // allocating memory for the tables used
    p = (Process *)malloc(sizeof(Process) * n);
    turnaroundTimes = (int *)malloc(sizeof(int) * n); // Allocation pour les temps de rotation

    // print all information about the different processes
    printf("\t     Welcome to Priority Scheduling Algorithm\n");
    puts("\t¤_____¤______________¤____________¤__________¤");
    printf("\t| %-2s | %-12s | %-10s | %-8s |\n", "PID", "Arrival Time", "Burst Time", "Priority");
    puts("\t¤_____¤______________¤____________¤__________¤");

    while (fgets(line, sizeof(line), file)) {
        // first character of the line
        char firstChar = line[0];
        // check if line is empty or is a comment
        if ((firstChar != '#') && (strlen(line) > 2)) {
            // separator
            char d[] = " ";
            // Save process details in "p"
            strcpy(p[i].pid, strtok(line, d));
            p[i].t_arv = atoi(strtok(NULL, d));
            p[i].t_exec = atoi(strtok(NULL, d));
            p[i].priorite = atoi(strtok(NULL, d));
            // initialization of the remaining burst time
            p[i].rnt = p[i].t_exec;
            printf("\t| %-3s | %-12d | %-10d | %-8d |\n", p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
            i++;
        }
    }

    puts("\t¤_____¤______________¤_____________¤_________¤");
    fclose(file);

    // save the name of the process in the first column and the time in the next
    // gantt[n][2] 2 columns to save name + starting time, n number of processes
    gantt = (int *)malloc(n * 2 * sizeof(int));

    // displaying the gantt chart
    int total_exec = 0;
    for (i = 0; i < n; i++) {
        total_exec = total_exec + p[i].t_exec;
    }
    while (j < n) {
        int minPriority = 1000; // set an initial value for minPriority
        if (count == total_exec) {
            break;
        }

        // find the process with the highest priority among the arrived processes
        for (i = 0; i < n; i++) {
            if (p[i].t_arv <= count && p[i].rnt > 0) {
            if (p[i].priorite < minPriority || (p[i].priorite == minPriority && p[i].t_arv < p[ind].t_arv)) {
                ind = i;
                minPriority = p[i].priorite;
            }
            // If two processes have the same priority,
            else if (p[i].t_arv <= count && p[i].rnt > 0 && p[i].priorite == minPriority) {
       
        }
        }
           
        }

        // checking if we have a process's index already stored
        if (ind != -1) {
            // updating the remaining execution time
            p[ind].rnt -= 1;
            // checking if the currently indexed process is not the previous one executed
            if (ind != prev) {
                // saving the index of the process
                gantt[e * 2 + 0] = ind + 1;
                // saving the starting time
                gantt[((e++) * 2) + 1] = count;
            }
        }

        // update the next starting time for the next process
        count++;
        // if the indexed process has finished all of its burst time, move to the next one
        if (p[ind].rnt == 0 && ind != -1) {
            // move one to the next process
            j++;

            // Calculate turnaround time for the completed process (au moment où il termine son dernier burst)
if (ind != -1) {
    turnaroundTimes[ind] = count - p[ind].t_arv;
}
        }
        // the previously executed process becomes the current one
        prev = ind;
    }






    // displaying the gantt chart
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
    // display the name of each process
    for (i = 0; i < e; i++) {
        printf("|  P%d\t", gantt[i * 2 + 0]);
    }

    printf("|\n ");
    for (i = 0; i < e; i++) {
        printf(" ¤---¤  ");
    }
    printf("|\n ");
    // display the (start, end) time of each process
    for (i = 0; i <= e; i++) {
        printf("%d\t", gantt[i * 2 + 1]);
    }

    // Display Turnaround and Wait Times
    printf("\n\n");
    printf("\t¤_____¤______________¤____________¤________________¤______________¤\n");
    printf("\t| %-2s | %-12s | %-10s | %-14s | %-14s |\n", "PID", "Arrival Time", "Burst Time", "Turnaround Time", "Wait Time");
    printf("\t¤_____¤______________¤____________¤________________¤______________¤\n");

    int totalTurnaroundTime = 0;
    int totalWaitTime = 0;

    for (i = 0; i < n; i++) {
        int waitTime = turnaroundTimes[i] - p[i].t_exec; // Calculer le temps d'attente
        totalTurnaroundTime += turnaroundTimes[i];
        totalWaitTime += waitTime;

        printf("\t| %-3s | %-12d | %-10d | %-14d | %-14d |\n", p[i].pid, p[i].t_arv, p[i].t_exec, turnaroundTimes[i], waitTime);

        // Affiche la ligne de séparation seulement si ce n'est pas le dernier processus
        if (i < n - 1) {
            printf("\t¤_____¤______________¤____________¤________________¤______________¤\n");
        }
    }

    // Calculate and display average turnaround time and average wait time
    double avgTurnaroundTime = (double)totalTurnaroundTime / n;
    double avgWaitTime = (double)totalWaitTime / n;

    printf("\n\nAverage Turnaround Time: %.2f", avgTurnaroundTime);
    printf("\nAverage Wait Time: %.2f\n", avgWaitTime);

    // Free allocated memory
    free(p);
    free(gantt);
    free(turnaroundTimes);

    return 0;
}

