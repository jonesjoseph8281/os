#include <stdio.h>

int main() {
    int p = 5, r = 3;

    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int alloc[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int aval[3] = {3, 3, 2};
    int need[5][3];
    int finish[5] = {0};
    int work[3], safe[5], count = 0;

    // Calculate Need matrix
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize work = available
    for (int i = 0; i < r; i++) {
        work[i] = aval[i];
    }

    // Safety Algorithm
    for (int k = 0; k < p; k++) {
        for (int i = 0; i < p; i++) {
            if (finish[i] == 0) {
                int flag = 1;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    for (int j = 0; j < r; j++)
                        work[j] += alloc[i][j];

                    safe[count++] = i;
                    finish[i] = 1;
                }
            }
        }
    }

    // Check if system is safe
    if (count == p) {
        printf("System is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < p; i++) {
            printf("P%d ", safe[i]);
        }
        printf("\n");
    } else {
        printf("System is NOT in a safe state.\n");
    }

    return 0;
}
