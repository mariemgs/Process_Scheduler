#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../process.h"
#include "../../FileManager.h"

// Function to display the Gantt chart
void displayGanttChart(Process processes[], int n, int gantt[], int size) {
    printf("\nThe Gantt chart is:\n");
    int i;

    // Display the horizontal bars for each process
    for (i = 0; i < size-1; i += 2) {
        printf(" ¤---¤  ");
    }
    printf("\n");

    // Display the process IDs
    for (i = 0; i < size-1; i += 2) {
        printf("|   %s\t", processes[gantt[i] - 1].pid);
    }
    printf("|\n");

    // Display the horizontal bars for each process
    for (i = 0; i < size-1; i += 2) {
        printf(" ¤---¤  ");
    }
    printf("|\n");

    // Display the start time of each process
    for (i = 1; i < size; i += 2) {
        printf("%-4d\t", gantt[i]);
    }
    printf("%-4d\t", gantt[size-1]);
    printf("\n\n");
}

// Function to perform Round Robin scheduling
void roundRobin(Process processes[], int n, int quantum) {
    int time = processes[0].t_arv; // Initialize time with the arrival time of the first process
    int completedProcesses = 0;    // Number of processes completed
    int i;
    int j;
    int ganttIndex = 0;
    int *gantt = (int *)malloc(n * 2 * sizeof(int)+1); // Array to store Gantt chart information

    // Sort processes based on arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].t_arv > processes[j + 1].t_arv) {
                // Swap processes
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    time = processes[0].t_arv;

    // Initialize remaining burst time (rnt) to burst time (t_exec) for all processes
    for (i = 0; i < n; i++) {
        processes[i].rnt = processes[i].t_exec;
    }

    // Print the Gantt chart header
    printf("\nGantt Chart:\n");
    printf("-------------------------------------------------\n");

    // Loop until all processes are completed
   // gantt[ganttIndex++] = time;
    while (completedProcesses < n) {
        for (i = 0; i < n; i++) {
            // Check if the process has arrived and not completed
            if (processes[i].rnt > 0 && processes[i].t_arv <= time) {

                // Execute the process for the given quantum or its remaining time, whichever is smaller
                int executionTime = (processes[i].rnt < quantum) ? processes[i].rnt : quantum;

                // Update arrival time to be equal to the current time
                processes[i].t_arv = time;

                // Execute the process
                processes[i].rnt -= executionTime;

                // Store Gantt chart information
                
                
                gantt[ganttIndex++] = i + 1;   // Process index
                // Check if the process is completed
                gantt[ganttIndex++] = time;
                time += executionTime;
                if (processes[i].rnt == 0) {
                    completedProcesses++;
                }
            }
        }
    }

    // Print the Gantt chart footer
    printf("|\n");
    printf("-------------------------------------------------\n");
    
    gantt[ganttIndex++] = time;
    // Display the Gantt chart
    displayGanttChart(processes, n, gantt, ganttIndex);
    

    // Free the Gantt chart memory
    free(gantt);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the number of processes
    int n;
    n = getProcessnbFromFile(argv[1]);

    // Allocate memory for processes
    Process *processes = (Process *)malloc(n * sizeof(Process));

    // Read processes from the file
    int i;
    for (i = 0; i < n; i++) {
        fscanf(file, "%s %d %d %d", processes[i].pid, &processes[i].t_arv, &processes[i].t_exec, &processes[i].priorite);
        processes[i].rnt = processes[i].t_exec;
        // Initialize priority to 0; you may modify this based on your requirements
    }

    // Close the file
    fclose(file);

    // Get the time quantum from the user with validation
    int quantum;
    do {
        printf("Enter Time Slice OR Quantum Number : ");
        scanf("%d", &quantum);
        if (quantum <= 0) {
            printf("Time quantum must be greater than 0. Please enter a valid value.\n");
        }
    } while (quantum <= 0);

    // Perform Round Robin scheduling
    roundRobin(processes, n, quantum);

    // Free allocated memory
    free(processes);

    return 0;
}

