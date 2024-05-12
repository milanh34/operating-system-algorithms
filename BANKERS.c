#include<stdio.h>
#include<stdlib.h>
#define n 10

int main(){
    int allocation[n][n], max[n][n], need[n][n], available[n], completed[n], safe_seq[n], i, j, count = 0, p, r, c, t = 0;
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);
    printf("Enter allocation and max resources for all processe\n");
    for(i = 0; i < p; i++){
        printf("Allocated resources for Process %d: ", i+1);
        for(j = 0; j < r; j++){
            scanf("%d", &allocation[i][j]);
        }
        printf("Max resources for Process %d: ", i+1);
        for(j = 0; j < r; j++){
            scanf("%d", &max[i][j]);
        }
        for(j = 0; j < r; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
        completed[i] = 0;
    }
    printf("Enter available resources: ");
    for(i = 0; i < r; i++){
        scanf("%d", &available[i]);
    }
    while(count < p){
        for(i = 0; i < p; i++){
            c = 0;
            if(completed[i] != 1){
                for(j = 0; j < r; j++){
                    if(need[i][j] <= available[j]){
                        c++;
                    }
                }
                if(c == r){
                    for(j = 0; j < r; j++){
                        available[j] += allocation[i][j];
                    }
                    safe_seq[count] = i;
                    count++;
                    t = 0;
                    completed[i] = 1;
                }
                else{
                    t++;
                }
            }
        }
        if(t == p - 1){
            printf("Safe sequnce does not exist");
            break;
        }
    }
    if(t != p - 1){
        printf("\n\nProcess\tAllocation\tMax\t\tNeed\n");
        for(i = 0; i < p; i++){
            printf("P%d\t", i+1);
            for(j = 0; j < r; j++){
                printf("%d ", allocation[i][j]);
            }
            printf("\t\t");
            for(j = 0; j < r; j++){
                printf("%d ", max[i][j]);
            }
            printf("\t\t");
            for(j = 0; j < r; j++){
                printf("%d ", need[i][j]);
            }
            printf("\n");
        }
        printf("\nTotal available resources: ");
        for(i = 0; i < r; i++){
            printf("%d ", available[i]);
        }
        printf("\nSafe sequence: < ");
        for(i = 0; i < p; i++){
            printf("P%d ", safe_seq[i]);
        }
        printf(">");
    }
    return 0;
}