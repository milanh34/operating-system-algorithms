#include<stdio.h>
#include<stdlib.h>
#define n 50

int main(){
    int seq[n], t1[n], t2[n], r1 = 0, r2 = 0, r, head, disks, req, total = 0, i, j, direction;
    printf("Enter the total number of disk tracks: ");
    scanf("%d", &disks);
    printf("Enter the number of requests in queue: ");
    scanf("%d", &req);
    printf("Enter the initial position of head: ");
    scanf("%d", &head);
    printf("Enter the sequence of requests: ");
    for(i = 0; i < req; i++){
        scanf("%d", &r);
        if(r >= head){
            t1[r1] = r;
            r1++;
        }
        else{
            t2[r2] = r;
            r2++;
        }
    }
    printf("Choose direction UP or DOWN (1 or 2): ");
    scanf("%d", &direction);
    for(i = 0; i < r1; i++){
        for(j = i + 1; j < r1; j++){
            if(t1[j] < t1[i]){
                r = t1[j];
                t1[j] = t1[i];
                t1[i] = r;
            }
        }
    }
    for(i = 0; i < r2; i++){
        for(j = i + 1; j < r2; j++){
            if(t2[j] < t2[i]){
                r = t2[j];
                t2[j] = t2[i];
                t2[i] = r;
            }
        }
    }
    r = 0;
    if(direction == 1){
        for(i = 0; i < r1; i++){
            seq[i] = t1[i];
            r++;
        }
        for(i = r, j = r2 - 1; j >= 0; i++, j--){
            seq[i] = t2[j];
            r++;
        }
    }
    else{
        for(i = r, j = r2 - 1; j >= 0; i++, j--){
            seq[i] = t2[j];
            r++;
        }
        for(i = 0; i < r1; i++){
            seq[r] = t1[i];
            r++;
        }
    }
    for(i = 0; i < r; i++){
        printf("\nHead moves from %d to %d", head, seq[i]);
        total += (head > seq[i])? (head - seq[i]) : (seq[i] - head);
        head = seq[i];
    }
    printf("\n\nTotal head movements: %d", total);
    printf("\nAverage seek time %f", (total/(float)req));
    return 0;
}