#include<stdio.h>
#include<stdlib.h>
#define n 10

void best_fit(int block[], int b, int process[], int p, int total_mem){
    int allocated[p], i, j, mem = 0, x;
    for(i = 0; i < p; i++){
        allocated[i] = -1;
    }
    for(i = 0; i < p; i++){
        x = -1;
        for(j = 0; j < b; j++){
            if(block[j] >= process[i]){
                if(x == -1){
                    x = j;
                }
                else{
                    if(block[x] < block[j]){
                        x = j;
                    }
                }
            }
        }
        if(x != -1){
            allocated[i] = x + 1;
            block[x] -= process[i];
            mem += process[i];
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
    best_fit(block, b, process, p, total_mem);
    return 0;
}