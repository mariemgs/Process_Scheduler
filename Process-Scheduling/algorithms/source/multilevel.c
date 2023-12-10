#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a structure for Process is defined as follows:
typedef struct {
    char pid[10];     // Process ID
    int t_arv;        // Arrival Time
    int t_exec;       // Total Execution Time
    int priorite;     // Priority
    int rnt;          // Remaining Time to Execute
} Process;

int getProcessnbFromFile(const char *filename) {
    // Dummy implementation, replace with actual file reading logic
    return 5; // Example: Return 5 processes
}

void readProcessesFromFile(const char *filename, Process *processes, int n) {
    // Dummy implementation, replace with actual file reading logic
    // Populate the 'processes' array with data from the file
}

int findHighestPriority(Process *processes, int n, int currentTime) {
    int highestPriority = 1000; // Assuming a larger number indicates lower priority
    for (int i = 0; i < n; i++) {
        if (processes[i].t_arv <= currentTime && processes[i].rnt > 0 && processes[i].priorite < highestPriority) {
            highestPriority = processes[i].priorite;
        }
    }
    return highestPriority;
}

void roundRobin(Process *processes, int n, int highestPriority, int quantum, int *currentTime) {
    int allCompleted = 1;
    for (int i = 0; i < n; i++) {
        if (processes[i].priorite == highestPriority && processes[i].rnt > 0) {
            allCompleted = 0;
            if (processes[i].rnt > quantum) {
                processes[i].rnt -= quantum;
                *currentTime += quantum;
            } else {
                *currentTime += processes[i].rnt;
                processes[i].rnt = 0;
            }
            printf("Process %s executed from %d to %d\n", processes[i].pid, *currentTime - quantum, *currentTime);
            if (processes[i].rnt == 0) {
                printf("Process %s completed at time %d\n", processes[i].pid, *currentTime);
            }
        }
    }
    if (allCompleted) {
        *currentTime += 1; // Increment time if no processes were executed in this cycle
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int n = getProcessnbFromFile(filename);
    Process *processes = (Process *)malloc(n * sizeof(Process));

    readProcessesFromFile(filename, processes, n);

    for (int i = 0; i < n; i++) {
        processes[i].rnt = processes[i].t_exec; // Initialize remaining time
    }

    int quantum = 4; // Set the time quantum for round-robin
    int currentTime = 0;

    while (1) {
        int highestPriority = findHighestPriority(processes, n, currentTime);
        if (highestPriority == 1000) { // No more processes to schedule
            break;
        }
        roundRobin(processes, n, highestPriority, quantum, &currentTime);
    }

    free(processes);
    return 0;
}
