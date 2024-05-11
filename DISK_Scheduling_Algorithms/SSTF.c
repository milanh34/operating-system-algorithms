#include<stdio.h>
#include<stdlib.h>
#define n 50

int main(){
    int seq[n], head, disks, req, total = 0, min, i, j, d, x;
    printf("Enter the total number of disk tracks: ");
    scanf("%d", &disks);
    printf("Enter the number of requests in queue: ");
    scanf("%d", &req);
    printf("Enter the initial position of head: ");
    scanf("%d", &head);
    printf("Enter the sequence of requests: ");
    for(i = 0; i < req; i++){
        scanf("%d", &seq[i]);
    }
    for(i = 0; i < req; i++){
        min = 1000;
        for(j = 0; j < req; j++){
            d = (head > seq[j])? (head - seq[j]) : (seq[j] - head);
            if(min > d){
                min = d;
                x = j;
            }
        }
        printf("\nHead moves from %d to %d", head, seq[x]);
        total += min;
        head = seq[x];
        seq[x] = 5000;
    }
    printf("\n\nTotal head movements: %d", total);
    printf("\nAverage seek time %f", (total/(float)req));
    return 0;
}