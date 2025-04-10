#include <stdio.h>

int main() {
    int p = 11;  // number of pages
    int f = 3;   // number of frames
    int pages[] = {1, 2, 1, 5, 3, 4, 5, 3, 4, 8, 1};  // page reference string
    int memory[f]; // memory to hold pages
    int pointer = 0; // FIFO pointer
    int pageFaults = 0;

    // Initialize memory with -1 (empty)
    for (int i = 0; i < f; i++) {
        memory[i] = -1;
    }

    printf("FIFO Page Replacement:\n\n");

    for (int i = 0; i < p; i++) {
        int found = 0;

        // Check if page is already in memory
        for (int j = 0; j < f; j++) {
            if (memory[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If not found, it's a page fault
        if (found == 0) {
            memory[pointer] = pages[i];
            pointer = (pointer + 1) % f;
            pageFaults++;

            // Print memory state with page fault indication
            for (int k = 0; k < f; k++) {
                if (memory[k] != -1)
                    printf("%d\t", memory[k]);
                else
                    printf("-\t");
            }
            printf(" <-- Page Fault\n");
        } else {
            // Print memory state (no page fault)
            for (int k = 0; k < f; k++) {
                if (memory[k] != -1)
                    printf("%d\t", memory[k]);
                else
                    printf("-\t");
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}
