#include <stdio.h>
#include <stdlib.h>

int main() {
    int disk[] = {1, 10, 55, 69, 92, 21, 77, 34};
    int head = 50;
    int size = sizeof(disk) / sizeof(disk[0]);
    int seek = 0;

    printf("Initial Head Position: %d\n", head);
    printf("Request Order and Movements:\n");

    for (int i = 0; i < size; i++) {
        printf("Move from %d to %d -> Seek: %d\n", head, disk[i], abs(head - disk[i]));
        seek += abs(head - disk[i]);
        head = disk[i];
    }

    printf("Total Seek Time: %d\n", seek);
    return 0;
}
