/* FIFO */

#include<stdio.h>

struct frames{
int content , ct;
}frame[20];

void main(){
int  n , m , i , j, Fnd, k = 0, pg[100], cnt = 0, fr[100];;
printf("Enter the no of pages : ");
scanf("%d",&n);

for(i = 0 ; i< n ; i++){
printf("Enter the page : ");
scanf("%d",&pg[i]);
}

printf("\nEnter the no of pages : ");
scanf("%d",&m);

for(i = 0 ; i < m ; i++){
fr[i] = -1;
}

printf("\nREFERENCE_STRING | PAGE_NUMBER | STATUS\n");

for(i =0 ; i < n ; i++){
Fnd = 0 ;
printf("%d\t\t  ",pg[i]);
for(j = 0 ; j < m ; j++){
if(fr[j] == pg[i]){
Fnd = 1;
}
}
    if (Fnd == 0) {
            fr[k] = pg[i];
            k = (k + 1) % m;
            cnt++;
        }
        for (j = 0; j < m; j++) {
            if (fr[j] != -1) {
                printf("%d   ", fr[j]);
            }
            else{
            printf("  ");
            }
        }
        if (Fnd == 1) {
            printf("\t HIT\n");
        } else {
            printf("\t MISS\n");
        }
    }
    printf("\nPAGE FAULT : %d\n", cnt);
}
