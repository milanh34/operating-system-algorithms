#include<stdio.h>
#include<stdlib.h>
#define n 10

void next_fit(int block[], int b, int process[], int p, int total_mem){
    int allocated[p], i, j = 0, mem = 0;
    for(i = 0; i < p; i++){
        allocated[i] = -1;
    }
    for(i = 0; i < p; i++){
        while(j < b){
            if(block[j] >= process[i]){
                allocated[i] = j + 1;
                block[j] -= process[i];
                mem += process[i];
                break;
            }
            j = (j + 1) % b;
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for(i = 0; i < p; i++){
        printf("%d\t\t%d\t\t", i+1, process[i]);
        if(allocated[i] == -1){
            printf("Not alloted\n");
        }
        else{
            printf("%d\n", allocated[i]);
        }
    }
    printf("Memory utilized: %f", (float)mem/total_mem * 100);
}

int main(){
    int process[n], block[n], p, b, i, total_mem = 0;
    printf("Enter no. of blocks: ");
    scanf("%d", &b);
    printf("Enter the size of blocks: ");
    for(i = 0; i < b; i++){
        scanf("%d", &block[i]);
        total_mem += block[i];
    }
    printf("Enter no. processes: ");
    scanf("%d", &p);
    printf("Enter the size of processes: ");
    for(i = 0; i < p; i++){
        scanf("%d", &process[i]);
    }
    next_fit(block, b, process, p, total_mem);
    return 0;
}