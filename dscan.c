#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j]) {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
}

int main() {
    int n, head, max = 199, direction;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter disk request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size (max track number, default 199): ");
    scanf("%d", &max);

    printf("Enter direction (0 = left, 1 = right): ");
    scanf("%d", &direction);

    sort(requests, n);
    int seek = 0;
    int start = head;

    printf("\nSCAN Order: %d", head);

    if (direction == 1) {
        // Move right first
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                seek += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }

        // Go to the end if not already there
        if (head != max) {
            seek += abs(head - max);
            head = max;
            printf(" -> %d", head);
        }

        // Move left now
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < start) {
                seek += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }

    } else if (direction == 0) {
        // Move left first
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                seek += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }

        // Go to the start (track 0) if not already there
        if (head != 0) {
            seek += abs(head - 0);
            head = 0;
            printf(" -> %d", head);
        }

        // Move right now
        for (int i = 0; i < n; i++) {
            if (requests[i] > start) {
                seek += abs(head - requests[i]);
                head = requests[i];
                printf(" -> %d", head);
            }
        }
    }

    printf("\nTotal Seek Time: %d\n", seek);
    return 0;
}
