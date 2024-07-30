/* L R U */

#include<stdio.h>

void LRU(int pages[], int n, int frames) {
    int frame[50], recent[50];
    int page_faults = 0, i, j, k, lru, flag;

    for (i = 0; i < frames; i++) {
        frame[i] = -1;
        recent[i] = 0;
    }

printf("\nREFERENCE STRING\t PAGE NUMBER\t\t  STATUS\n");
    for (i = 0; i < n; i++) {
        flag = 0;

       
        for (j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                flag = 1;
                recent[j] = i + 1;
                break;
            }
        }
        if (flag == 0) {
            lru = 0;
            for (j = 1; j < frames; j++) {
                if (recent[j] < recent[lru]) {
                    lru = j;
                }
            }
            frame[lru] = pages[i];
            recent[lru] = i + 1;
            page_faults++;
        }

//printf("REFERENCE STRING: %d -> PAGE NUMBER: ", pages[i]);
        printf("\t\t%d\t\t", pages[i]);
        for (k = 0; k < frames; k++) {
            if (frame[k] == -1)
                printf("  |  ");
            else
                printf("%d | ", frame[k]);
        }
       
        //printf("STATUS: ");
       
        if (flag == 0) {
            printf("\t\tMISS\n");
        } else {
            printf("\t\tHIT\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

void main(){
int i, n, m, choice = 0, pg[100];
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter the page number %d: ", i + 1);
        scanf("%d", &pg[i]);
    }
    printf("Enter the number of frames: ");
    scanf("%d", &m);

LRU(pg, n, m);
}
