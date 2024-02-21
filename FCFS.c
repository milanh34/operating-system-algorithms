#include<stdio.h>
#include<stdlib.h>
#define n 10

struct process{
    int pid, arr, bt, ct, turn, wt;
};

void printLines(struct process p[], int m){
    int i, j, gap_c;
    printf(" ");
    for(i=0;i<m;i++) {
        if(p[i].arr>0 && i==0){
            gap_c=p[0].arr;
            for(j=0;j<gap_c;j++){
                printf("--");
            }
            printf(" ");
        }
        for (j=0;j<p[i].bt;j++) {
            printf("--");
        }
        printf(" ");
        if(p[i].ct<p[i+1].arr && i<m-1){
            gap_c=p[i+1].arr-p[i].ct;
            for(j=0;j<gap_c;j++){
                printf("--");
            }
            printf(" ");
        }
    }
    printf("\n");
}

int main(){
    struct process p[n], temp;
    int i, j, m, gap=0, gap_c;
    double avgtt, avgwt, ttt=0, twt=0;
    printf("Enter no. of processes: ");
    scanf("%d",&m);
    printf("Enter Process ID, Arrival Time and Burst Time for each process :\n");
    for(i=0;i<m;i++){
        printf("Process %d: ",i+1);
        scanf("%d %d %d", &p[i].pid, &p[i].arr, &p[i].bt);
    }
    for(i=0;i<m;i++){
        for(j=i+1;j<m;j++){
            if(p[j].arr<p[i].arr){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    for(i=0;i<m;i++){
        if(i==0){
            p[i].ct=p[i].bt+p[i].arr;
        }
        else{
            if(p[i-1].ct<p[i].arr){
                p[i].ct=p[i].arr+p[i].bt;
            }
            else{
                p[i].ct=p[i-1].ct+p[i].bt;
            }
        }
        p[i].turn=p[i].ct-p[i].arr;
        p[i].wt=p[i].turn-p[i].bt;
    }
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for(i=0;i<m;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d\n",p[i].pid,p[i].arr,p[i].bt,p[i].ct,p[i].turn,p[i].wt);
        ttt+=p[i].turn;
        twt+=p[i].wt;
    }
    avgtt=ttt/m;
    avgwt=twt/m;
    printf("\nGantt chart\n");
    printLines(p,m);
    printf("|");
    for (i=0;i<m;i++) {
        if(p[i].arr>0 && i==0){
            gap_c=p[i].arr;
            for(j=0;j<gap_c;j++){
                printf("//");
            }
            printf("|");
        }
        for (j=0;j<p[i].bt-1;j++) {
            printf(" ");
        }
        printf("P%d", p[i].pid);
        for (j=0;j<p[i].bt-1;j++) {
            printf(" ");
        }
        printf("|");
        if(p[i].ct<p[i+1].arr && i<m-1){
            gap_c=p[i+1].arr-p[i].ct;
            for(j=0;j<gap_c;j++){
                printf("//");
            }
            printf("|");
        }
    }
    printf("\n");
    printLines(p,m);
    printf("0");
    for (i=0;i<m;i++) {
        if(p[i].arr>0 && i==0){
            gap_c=p[0].arr;
            for(j=0;j<gap_c;j++){
                printf("  ");
            }
            gap+=gap_c;
            printf("%d", gap_c);
        }
        for (j=0;j<p[i].bt;j++) {
            printf("  ");
            gap++;
        }
        printf("%d",gap);
        if(p[i].ct<p[i+1].arr && i<m-1){
            gap_c=p[i+1].arr-p[i].ct;
            for(j=0;j<gap_c;j++){
                printf("  ");
            }
            gap+=gap_c;
            printf("%d", gap);
        }
    }
    printf("\n\nTotal turnaround time : %lf\nTotal Waiting time : %lf",avgtt, avgwt);
    return 0;
}