#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pid[10];
    int t_arv;
    int t_exec;
    int priorite;
} Process;

void swap(Process *A, Process *B) {
    Process temp = *A;
    *A = *B;
    *B = temp;
}

// Function to get the total number of processes from the file
int getProcessnbFromFile(const char *filename) {
    int count = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error! Opening file");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char firstChar = line[0];
        if ((firstChar != '#') && (strlen(line) > 2)) {
            count++;
        }
    }

    fclose(file);
    return count;
}

int main(int argc, char* argv[]) {
    FILE *file;
    int i = 0, j, n, e = 0, token, start = 0;
    Process *p = NULL;
    int *gantt = NULL;
    char line[256];

    if ((file = fopen(argv[1], "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    n = getProcessnbFromFile(argv[1]);
    p = (Process *)malloc(sizeof(Process) * n);

    printf("\t Welcome to First In First Out Scheduling Algorithm\n");
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
            printf("\t| %-3s | %-12d | %-10d | %-8d |\n", p[i].pid, p[i].t_arv, p[i].t_exec, p[i].priorite);
            i++;
        }
    }

    puts("\t¤_____¤______________¤____________¤__________¤");
    fclose(file);

    gantt = (int *)malloc(n * 2 * sizeof(int));

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].t_arv > p[j].t_arv) {
                swap(&p[i], &p[j]);
            }
        }
    }

   // Display the Gantt chart
printf("\n\nThe Gantt chart is:\n");
printf(" ");
for (i = 0; i < n; i++) {
    printf(" ¤___¤   ");
}
printf("\n");

// Display the name of each process with additional spacing
for (i = 0; i < n; i++) {
    printf("|   %-5s", p[i].pid); // Ajustez la largeur en fonction de vos besoins
}
printf("|\n");
printf(" ");
for (i = 0; i < n; i++) {
    printf(" ¤___¤   ");
}
printf("\n");
// Display the (start, end) time of each process with additional spacing
start = p[0].t_arv;
for (i = 0; i < n; i++) {
    printf("%-9d", start); // Ajustez la largeur en fonction de vos besoins
    start += p[i].t_exec;

    // Check if it's not the last process to avoid printing an extra end time
    if (i < n - 1 && start < p[i + 1].t_arv) {
        printf("%-10d", start); // Ajustez la largeur en fonction de vos besoins
        start = p[i + 1].t_arv;
    }
}

// Print the termination time of the last process
printf("%-10d\n", start); // Ajustez la largeur en fonction de vos besoins

// Display the (start, end) time of each process with additional spacing
start = p[0].t_arv;
int totalTurnaroundTime = 0;
int totalWaitTime = 0;

printf("\n\t¤_____¤______________¤____________¤________________¤______________¤\n");
printf("\t| %-2s | %-12s | %-10s | %-10s | %-10s |\n", "PID", "Arrival Time", "Burst Time", "Turnaround Time", "Wait Time");
printf("\t¤_____¤______________¤____________¤______________¤______________¤\n");

for (i = 0; i < n; i++) {
    int turnaroundTime = start + p[i].t_exec - p[i].t_arv;
    int waitTime = turnaroundTime - p[i].t_exec;

    totalTurnaroundTime += turnaroundTime;
    totalWaitTime += waitTime;

    printf("\t| %-3s | %-12d | %-12d | %-12d | %-12d |\n", p[i].pid, p[i].t_arv, p[i].t_exec, turnaroundTime, waitTime);

    // Affiche la ligne de séparation seulement si ce n'est pas le dernier processus
    if (i < n - 1) {
        printf("\t¤_____¤______________¤____________¤______________¤______________¤\n");
    }

    // Met à jour la variable de début pour le prochain processus
    start += p[i].t_exec;
}

// Calculate and display average turnaround time and average wait time
double avgTurnaroundTime = (double)totalTurnaroundTime / n;
double avgWaitTime = (double)totalWaitTime / n;

printf("\n\nAverage Turnaround Time: %.2f", avgTurnaroundTime);
printf("\nAverage Wait Time: %.2f\n", avgWaitTime);

    free(p);
    free(gantt);

    return 0;
}

