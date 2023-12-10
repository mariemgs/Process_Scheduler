#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct processData {
    int id;
    int arrivaltime;
    int runningtime;
    int priority;
};

void displayFileContent(const char *filename) 
{
    FILE *pFile;
    pFile = fopen(filename, "r");

    if (pFile == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }

    printf("+----------------+------------------+------------------+----------+\n");
    printf("| Pid de process | Temps d'arrivée   | Temps d'exécution | Priorité | \n");
    printf("+----------------+------------------+------------------+----------+\n");

    struct processData pData;

    // Lire et afficher chaque ensemble de données du fichier
    while (fscanf(pFile, "P%d %d %d %d", &pData.id, &pData.arrivaltime, &pData.runningtime, &pData.priority) == 4) {
        printf("| %-14d | %-16d | %-16d | %-8d |\n", pData.id, pData.arrivaltime, pData.runningtime, pData.priority);
        // Ignorer la virgule après chaque ensemble de données
        fseek(pFile, 1, SEEK_CUR);
    }

    printf("+----------------+------------------+------------------+----------+\n");
    fclose(pFile);
}

void generateParams(int no, int maxArrivalTime, int maxRunningTime, int maxPriority)
{
    FILE *pFile;
    pFile = fopen("params.txt", "w");

    if (pFile == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }

    struct processData pData;

    srand(time(NULL));

    for (int i = 1; i <= no; i++) {
        pData.id = i;
        pData.arrivaltime = rand() % (maxArrivalTime) + 1;
        pData.priority = rand() % (maxPriority) + 1;

        // Ensure runningtime is strictly greater than zero
        do {
            pData.runningtime = rand() % (maxRunningTime) + 1;
        } while (pData.runningtime <= 0);

        // Données de la tâche avec le format spécifié
        fprintf(pFile, "P%d %d %d %d\n", pData.id, pData.arrivaltime, pData.runningtime, pData.priority);
    }

    fclose(pFile);
    printf("Les données ont été générées avec succès et enregistrées dans le fichier 'params.txt'.\n\n");
}

int main()
{
    int no, maxRunningTime, maxArrivalTime, maxPriority;

    printf("Veuillez entrer le nombre de tâches que vous souhaitez générer : ");
    scanf(" %d", &no);

    printf("Veuillez entrer l'intervalle d'arrivée maximale pour les tâches : ");
    scanf(" %d", &maxArrivalTime);

    printf("Veuillez entrer la durée d'exécution maximale pour les tâches : ");
    scanf(" %d", &maxRunningTime);

    printf("Veuillez entrer l'intervalle de priorité maximale pour les tâches : ");
    scanf(" %d", &maxPriority);

    generateParams(no, maxArrivalTime, maxRunningTime, maxPriority);
    displayFileContent("params.txt");

    return 0;
}
