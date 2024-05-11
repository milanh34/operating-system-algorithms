#include<stdio.h>
#include<stdlib.h>
#define n 100

struct process{
    int pid, arr, bt, ct, turn, wt, r, flag;
};

struct chart{
    int pid, timet;
};

void printLines(struct chart c[], int m, int l){
    int i, j, t = 0;
    printf(" ");
    for(i = 0 ; i < l + 1 ; i++){
        for(j = 0 ; j < c[i].timet - t ; j++){
            printf("--");
        }
        t = c[i].timet;
        printf(" ");
    }
    printf("\n");
}

int main(){
    struct process p[n], temp, p_temp[n];
    struct chart c[n];
    int i, j, k, l = 0, m, timet, t = 0, completed = 0, count = 0;
    double avgtt, avgwt, ttt = 0, twt = 0;
    printf("Enter no. of processes: ");
    scanf("%d", &m);
    printf("Enter Process ID, Arrival Time and Burst Time for each process :\n");
    for(i = 0 ; i < m ; i++){
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].pid, &p[i].arr, &p[i].bt);
        p[i].r = p[i].bt;
        p[i].flag = 0;
    }
    for(i = 0 ; i < m ; i++){
        for(j = i + 1 ; j < m ; j++){
            if(p[j].arr < p[i].arr){
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    for(timet = 0 ; completed < m ; timet++){
        k = 0;
        for(i = 0 ; i < m ; i++){
            if(p[i].arr <= timet && p[i].flag != 1){
                p_temp[k] = p[i];
                k++;
            }
        }
        if(k > 0){
            for(i = 0 ; i < k ; i++){
                for(j = i + 1 ; j < k ; j++){
                    if(p_temp[j].r < p_temp[i].r){
                        temp = p_temp[i];
                        p_temp[i] = p_temp[j];
                        p_temp[j] = temp;
                    }
                }
            }
            if(p_temp[0].flag != 1){
                p_temp[0].r = p_temp[0].r - 1;
            }
            for(i = 0 ; i < m ; i++){
                if(p[i].pid == p_temp[0].pid){
                    p[i] = p_temp[0];
                    if(p[i].r == 0 && p[i].flag != 1){
                        p[i].flag = 1;
                        p[i].ct = timet + 1;
                        p[i].turn = p[i].ct - p[i].arr;
                        p[i].wt = p[i].turn - p[i].bt;
                        completed++;
                    }
                    break;
                }
            }
            if(timet == 0){
                c[l].pid = p_temp[0].pid;
                c[l].timet = timet + 1;
            }
            else{
                if(c[l].pid != p_temp[0].pid){
                    l++;
                    c[l].pid = p_temp[0].pid;
                }
                c[l].timet = timet + 1;
            }
        }
        else{
            if(timet == 0){
                c[l].pid = 0;
                c[l].timet = timet + 1;
            }
            else{
                if(c[l].pid != 0){
                    l++;
                    c[l].pid = 0;
                }
                c[l].timet = timet + 1;
            }
        }
    }
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for(i=0;i<m;i++){
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arr, p[i].bt, p[i].ct, p[i].turn, p[i].wt);
        ttt += p[i].turn;
        twt += p[i].wt;
    }
    avgtt = ttt / m;
    avgwt = twt / m;
    printf("\nGantt chart\n");
    printLines(c, m, l);
    printf("|");
    for(i = 0 ; i < l + 1 ; i++) {
        if(c[i].pid == 0){
            for(j = 0 ; j < c[i].timet - t; j++){
                printf("//");
            }
            t = c[i].timet;
            printf("|");
        }
        else{
            for(j = 0 ; j < c[i].timet - t - 1; j++){
                printf(" ");
            }
            printf("P%d", c[i].pid);
            for(j = 0 ; j < c[i].timet - t - 1 ; j++){
                printf(" ");
            }
            t = c[i].timet;
            printf("|");
        }
    }
    printf("\n");
    printLines(c, m, l);
    printf("0");
    t = 0;
    for(i = 0 ; i < l + 1 ; i++) {
        for(j = 0 ; j < c[i].timet - t ; j++){
            printf("  ");
        }
        t = c[i].timet;
        printf("%d", c[i].timet);
    }
    printf("\n\nTotal turnaround time : %.3lf\nTotal Waiting time : %.3lf", avgtt, avgwt);
    return 0;
}