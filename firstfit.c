#include <stdio.h>
#include <stdlib.h>

struct block {
    int os;                 // Original size
    int rs;                 // Remaining size
    struct block *next;     // Next block pointer
};

void firstfit(struct block *head, int nb, int file[], int nf) {
    for (int i = 0; i < nf; i++) {
        struct block *temp = head;
        int allocated = 0;

        while (temp != NULL) {
            if (temp->rs >= file[i]) {
                printf("File %d of size %d is allocated to block of size %d\n", i + 1, file[i], temp->os);
                temp->rs -= file[i];
                allocated = 1;
                break;
            }
            temp = temp->next;
        }

        if (!allocated) {
            printf("File %d of size %d cannot be allocated\n", i + 1, file[i]);
        }
    }
}

void display(struct block *head, int nb) {
    struct block *temp = head;
    printf("\nBlock\tSize\tRemaining\n");
    for (int i = 0; i < nb; i++) {
        printf("%d\t%d\t%d\n", i + 1, temp->os, temp->rs);
        temp = temp->next;
    }
}

int main() {
    int i, nf, nb;
    struct block *head = NULL, *temp = NULL;

    printf("Enter the number of blocks: ");
    scanf("%d", &nb);

    for (i = 0; i < nb; i++) {
        struct block *newBlock = (struct block *)malloc(sizeof(struct block));
        printf("Enter the size of block %d: ", i + 1);
        scanf("%d", &newBlock->os);
        newBlock->rs = newBlock->os;
        newBlock->next = NULL;

        if (head == NULL) {
            head = newBlock;
        } else {
            temp->next = newBlock;
        }
        temp = newBlock;
    }

    printf("Enter the number of files: ");
    scanf("%d", &nf);
    int file[nf];

    for (i = 0; i < nf; i++) {
        printf("Enter the size of file %d: ", i + 1);
        scanf("%d", &file[i]);
    }

    // Call First Fit
    firstfit(head, nb, file, nf);

    // Display block status
    display(head, nb);

    return 0;
}
