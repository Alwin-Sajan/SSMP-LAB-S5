#include <stdio.h>

void main() {
    int i, j, n, f, in[20], pf = 0, out[10], freq[10];
   
    // Input size of the input string
    printf("Enter the size of input string:\t");
    scanf("%d", &n);
   
    // Input string elements
    printf("Enter the string elements:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &in[i]);
    }
   
    // Input number of frames
    printf("Enter the number of frames:");
    scanf("%d", &f);
   
   
    printf("\nREFERENCE STRING PAGE NUMBER STATUS\n\n");
   
    // Initialize frames to -1 (indicating empty) and frequency to 0
    for(j = 0; j < f; j++) {
        out[j] = -1;
        freq[j] = 0;
    }
   
    // Page replacement process
    for(i = 0; i < n; i++) {
    printf("%d\t\t",in[i]);
        int found = 0;
        int fd = 0;
       
        // Check if the page is already in any frame
        for(j = 0; j < f; j++) {
            if(out[j] == in[i]) {
            //
                freq[j]++;  // Increment frequency count
                found = 1;
                break;
            }
        }
       
        // If the page is not found in any frame
        if(!found) {
            int min_freq = freq[0], min_index = 0;
           

            for(j = 1; j < f; j++) {
                if(freq[j] < min_freq) {
                    min_freq = freq[j];
                    min_index = j;
                }
            }
           

            out[min_index] = in[i];
            freq[min_index] = 1;  
            pf++;  
        }
       
       
        for(j = 0; j < f; j++) {
        if (out[j] != -1) {
                printf("%d   ",  out[j]);
            }
            else{
            printf("  ");
            }
        }
        if(found){
        printf("\t HIT \n");
        }else{
           printf("\t MISS \n");
        }
    }
    printf("\tTotal page faults: %d\n", pf);
}
