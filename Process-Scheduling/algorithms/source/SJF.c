#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Process structure
typedef struct {
    char pid[5];
    int t_arv;
    int t_exec;
    int priorite;
} Process;

void swap(Process *A, Process *B) {
    Process temp = *A;
    *A = *B;
    *B = temp;
}

int main(int argc, char *argv[]) {
    FILE *file;
    int i, j, n, token, start, e = 0;
    Process *p = NULL;
    int *gantt = NULL;
    char line[256];

    // Checking if the config file exists or not
    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    // Get the total number of processes
    n = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#' && strlen(line) > 2) {
            n++;
        }
    }

    // Reset file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    // Allocate memory for processes and Gantt chart
    gantt = (int *)malloc(n * 2 * sizeof(int));
    p = (Process *)malloc(sizeof(Process) * n);

    // Read process details from the file
    i = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#' && strlen(line) > 2) {
            sscanf(line, "%s%d%d%d", p[i].pid, &p[i].t_arv, &p[i].t_exec, &p[i].priorite);
            i++;
        }
    }

    // Print information about the processes
    printf("\t  Welcome to Shortest Job First Scheduling Algorithm\n");
    puts("\t¤_____¤______________¤____________¤__________¤");
    printf("\t| %-2s | %-12s | %-10s | %-8s |\n", "PID", "Arrival Time", "Burst Time", "Priority");
    puts("\t¤_____¤______________¤____________¤__________¤");

    for (i = 0; i < n; i++) {
        printf("\t| %-3s | %-12d | %-10d | %-8d |\n", p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
    }

    puts("\t¤_____¤______________¤_____________¤_________¤");

    // Sorting the processes according to their arrival time and burst time
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].t_arv > p[j].t_arv || (p[i].t_arv == p[j].t_arv && p[i].t_exec > p[j].t_exec)) {
                swap(&p[i], &p[j]);
            }
        }
    }

    // Initialize start time to the first process arrival time
    start = p[0].t_arv;

    for (i = 0; i < n; i++) {
       char tempPid[5];
	strcpy(tempPid, p[i].pid);
	token = atoi(strtok(tempPid, "P"));


        if (start < p[i].t_arv) {
            gantt[e * 2 + 0] = -1;
            gantt[e++ * 2 + 1] = start;
            start = p[i].t_arv;
        }

        // Choix du processus avec le temps d'exécution le plus court
        int shortest = i;
        for (j = i + 1; j < n && p[j].t_arv <= start; j++) {
            if (p[j].t_exec < p[shortest].t_exec) {
                shortest = j;
            }
        }

        char tempPidShortest[5];
	strcpy(tempPidShortest, p[shortest].pid);
	gantt[e * 2 + 0] = atoi(strtok(tempPidShortest, "P"));

        gantt[e++ * 2 + 1] = start;
        start += p[shortest].t_exec;

        // Mettre à jour le tableau des processus après l'exécution
        swap(&p[shortest], &p[i]);
    }

    // Displaying the Gantt chart
    gantt[e * 2 + 1] = start;
    printf("\n\nThe Gantt chart is:\n");
    printf(" ");
    for (i = 0; i < e; i++) {
        printf(" ¤___¤  ");
    }
    printf("\n");

    for (i = 0; i < e; i++) {
        if (gantt[i * 2 + 0] == -1) {
            printf("|  -   ");
        } else {
            printf("|  P%d\t", gantt[i * 2 + 0]);
        }
    }

    printf("|\n ");
    for (i = 0; i < e; i++) {
        printf(" ¤___¤  ");
    }
    printf("\n");

    for (i = 0; i <= e; i++) {
        printf("%d\t", gantt[i * 2 + 1]);
    }

    printf("\n ");
    for (i = 0; i < e; i++) {
        if (gantt[i * 2 + 0] != -1) {
            printf("  %d\t  %d  ", p[gantt[i * 2 + 0] - 1].t_arv, gantt[i * 2 + 1] - 1);
        }
    }

    // Free allocated memory
    free(gantt);
    free(p);

    fclose(file);
    return 0;
}

