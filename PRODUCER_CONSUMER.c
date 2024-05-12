#include<stdio.h>
#include<stdlib.h>
#define n 8
int buffer [n];
int in = -1;
int out = -1;
int s = 1;
int itemp = 0;
int itemc = 0;
int empty = n;
int full = 0;

int wait(int s){
    s--;
    while(s < 0){
        s--;
    }
    return s;
}

int signal(int s){
    s++;
    return s;
}

void producer(){
    s = wait(s);
    if(full == n){
        printf("Buffer is full\n");
    }
    else if(in == -1 && out == -1){
        empty = wait(empty);
        in = 0;
        out = 0;
        itemp++;
        buffer[in] = itemp;
        printf("Producer produces item %d\n", itemp);
        full = signal(full);
    }
    else{
        empty = wait(empty);
        in = (in + 1) % n;
        itemp++;
        buffer[in] = itemp;
        printf("Producer produces item %d\n", itemp);
        full = signal(full);
    }
    s = signal(s);
}

void consumer(){
    s = wait(s);
    if(in == -1 && out == -1){
        printf("Buffer is empty\n");
    }
    else if(in == out){
        full = wait(full);
        itemc = buffer[out];
        printf("Consumer consumes item %d\n", itemc);
        buffer[out] = -1;
        in = -1;
        out = -1;
        empty = signal(empty);
    }
    else{
        full = wait(full);
        itemc = buffer[out];
        printf("Consumer consumes item %d\n", itemc);
        buffer[out] = -1;
        out = (out + 1) % n;
        empty = signal(empty);
    }
    s = signal(s);
}

void display(){
    int i;
    if(in == -1 && out == -1){
        printf("Buffer is empty\n");
    }
    else{
        for(i = 0; i < n; i++){
            if(buffer[i] == -1){
                printf("- ");
            }
            else{
                printf("%d ", buffer[i]);
            }
        }
        printf("\n");
    }
}

int main(){
    int i;
    for(i = 0; i < n; i++){
        buffer[i] = -1;
    }
    do{
        printf("1.Producer | 2.Consumer | 3.Display | 4.Exit: ");
        scanf("%d", &i);
        switch(i){
            case 1:
            producer();
            break;
            case 2:
            consumer();
            break;
            case 3:
            display();
            break;
            case 4:
            printf("Exiting...");
            break;
            default:
            printf("Invalid input. Try again!\n");
            break;
        }
    }while(i != 4);
    return 0;
}