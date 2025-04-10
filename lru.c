#include <stdio.h>

int main() {
    int p = 11; // Number of pages
    int f = 3;  // Number of frames

    int pages[] = {1, 2, 1, 5, 3, 4, 5, 3, 4, 8, 1};
    int memory[] = {-1, -1, -1};      // Initial empty memory
    int counter[] = {0, 0, 0};        // Timestamps
    int time = 0;
    int page_faults = 0;

    for (int i = 0; i < p; i++) {
        int found = 0;

        for (int j = 0; j < f; j++) {
            if (memory[j] == pages[i]) {
                counter[j] = time++;
                found = 1;
                break;
            }
        }

        if (found == 0) {
            int min_time = counter[0], index = 0;

            for (int k = 1; k < f; k++) {
                if (counter[k] < min_time) {
                    index = k;
                    min_time = counter[k];
                }
            }

            memory[index] = pages[i];
            counter[index] = time++;
            page_faults++;
        }

        // Print current memory state
        printf("Memory: ");
        for (int j = 0; j < f; j++) {
            if (memory[j] == -1)
                printf("- ");
            else
                printf("%d ", memory[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}
