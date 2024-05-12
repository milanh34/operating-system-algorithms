#include<stdio.h>
#include<stdlib.h>
#define n 100

void lru(int frames, int p, int seq[]){
    int i, temp[frames], recent[frames], s, j, lru, page_fault = 0;
    for(i = 0; i < frames; i++){
        temp[i] = -1;
        recent[i] = 0;
    }
    printf("\nIncoming\t");
    for(i = 0; i < frames; i++){
        printf("Frame %d\t\t", i+1);
    }
    printf("\n");
    for(i = 0; i < p; i++){
        s = 0;
        for(j = 0; j < frames; j++){
            if(temp[j] == seq[i]){
                s++;
                recent[j] = i + 1;
                break;
            }
        }
        if(s == 0){
            page_fault++;
            lru = 0;
            for(j = 1; j < frames; j++){
                if(recent[j] < recent[lru]){
                    lru = j;
                }
            }
            temp[lru] = seq[i];
            recent[lru] = i + 1;
        }
        printf("%d\t\t", seq[i]);
        for(j = 0; j < frames; j++){
            if(temp[j] == -1){
                printf("-\t\t");
            }
            else{
                printf("%d\t\t", temp[j]);
            }
        }
        printf("\n");
    }
    printf("\nPage Faults: %d", page_fault);
    printf("\nTotal Hits: %d", p - page_fault);
}

int main(){
    int seq[n], frames, p, i;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of page references: ");
    scanf("%d", &p);
    printf("Enter the page references: ");
    for(i = 0; i < p; i++){
        scanf("%d", &seq[i]);
    }
    lru(frames, p, seq);
    return 0;
}