#include <stdio.h>

int main() {
    int p = 11; 
    int f = 3;  

    int pages[] = {1, 2, 1, 5, 3, 4, 5, 3, 4, 8, 1};
    int memory[] = {-1, -1, -1};      
    int frequency[] = {0, 0, 0};      
    int page_faults = 0;

    for (int i = 0; i < p; i++) {
        int found = 0;

        
        for (int j = 0; j < f; j++) {
            if (memory[j] == pages[i]) {
                frequency[j]++;
                found = 1;
                break;
            }
        }

        if (found == 0) {
            int min_frequency = frequency[0];
            int index = 0;

            
            for (int k = 1; k < f; k++) {
                if (frequency[k] < min_frequency || memory[k] == -1) {
                    index = k;
                    min_frequency = frequency[k];
                }
            }

            memory[index] = pages[i];
            frequency[index] = 1;
            page_faults++;
        }

        printf("After accessing %d: ", pages[i]);
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
