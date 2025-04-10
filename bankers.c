#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int n, m; // Number of processes and resources
int Max[MAX][MAX], Allocation[MAX][MAX], Need[MAX][MAX], Available[MAX];

void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
}

bool isSafe() {
    int Work[MAX];
    bool Finish[MAX] = {false};
    int safeSequence[MAX];
    int count = 0;

    // Copy available to Work
    for (int i = 0; i < m; i++)
        Work[i] = Available[i];

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];

                    safeSequence[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");

    return true;
}

bool requestResources(int process, int request[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > Need[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
        if (request[i] > Available[i]) {
            printf("Resources not available. Process must wait.\n");
            return false;
        }
    }

    // Pretend to allocate
    for (int i = 0; i < m; i++) {
        Available[i] -= request[i];
        Allocation[process][i] += request[i];
        Need[process][i] -= request[i];
    }

    if (isSafe()) {
        printf("Request granted to P%d.\n", process);
        return true;
    } else {
        // Rollback
        for (int i = 0; i < m; i++) {
            Available[i] += request[i];
            Allocation[process][i] -= request[i];
            Need[process][i] += request[i];
        }
        printf("Request leads to unsafe state. Request denied.\n");
        return false;
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("\nEnter Max Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Max[i][j]);

    printf("\nEnter Available Resources (%d values):\n", m);
    for (int i = 0; i < m; i++)
        scanf("%d", &Available[i]);

    calculateNeed();
    isSafe();

    char choice;
    printf("\nDo you want to make a resource request? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        int process, request[MAX];
        printf("Enter process number (0 to %d): ", n - 1);
        scanf("%d", &process);
        printf("Enter resource request of P%d (%d values): ", process, m);
        for (int i = 0; i < m; i++)
            scanf("%d", &request[i]);

        requestResources(process, request);
    }

    return 0;
}