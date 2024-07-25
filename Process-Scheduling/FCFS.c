/* FCFS */

#include<stdio.h>
#include<stdlib.h>

/* a[i][0] = bt
   a[i][1] = wt
   a[i][2] = tat
   a[i][3] = id
   a[i][4] = ct
*/

void Fcfs(int n , int a[10][4]){

int i = 0 ;
float atat = 0 , awt = 0;

a[i][1] = 0;

a[i][2] = a[i][0] + a[i][1];
atat = a[0][2];
awt = a[0][1];
for(i = 1 ; i < n ; i++){
a[i][1] = a[i-1][0] + a[i-1][1];
a[i][2] = a[i][0] + a[i][1];
awt = awt + a[i][1];
atat = atat + a[i][2];

}
awt = awt/n;
atat = atat/n;

printf("\nProcess ID | BT | WT | TAT\n");
for(int i = 0; i<n ; i++ ){
printf("P%d\t     %d     %d\t%d\n",a[i][3],a[i][0],a[i][1],a[i][2]);
}

printf("\nGantt\nP1 ");
for(int i = 1 ; i < n ; i++){
printf("-> P%d ",i+1);
}


printf("\nAverage Waiting Time = %f\n",awt);
printf("Average Turnaroundtime = %f\n",atat);

}

void main(){
int n , a[10][4] ,ct = 0 , awt =0 ,atat = 0 ;
printf("Enter the number of process : ");
scanf("%d",&n);

for(int i = 0 ; i < n ; i++){
printf("Enter the burst time of P%d ",i+1);
scanf("%d",&a[i][0]);
a[i][3] = i+1;
}

Fcfs(n,a);


}
