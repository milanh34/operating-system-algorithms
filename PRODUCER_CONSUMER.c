#include<stdio.h>
#include<stdlib.h>
#define n 8
int buffer[n], in = -1, out = -1, s = 1, empty = n, full = 0, itemp, itemc;

int wait(int s)
{
    s--;
    while(s < 0){
        s--;
    }
    return s;
}

int signal(int s)
{
    s++;
    return s;
}

void producer()
{
    s = wait(s);
    itemp = rand() % 100;
    if(full == n)
    {
        printf("Buffer is full\n");
    }
    else if(in == -1 && out == -1)
    {
        empty = wait(empty);
        in = 0;
        out = 0;
        buffer[in] = itemp;
        printf("Produced item is : %d\n", itemp);
        full = signal(full);
    }
    else
    {
        empty = wait(empty);
        in = (in + 1) % n;
        buffer[in] = itemp;
         printf("Produced item is : %d\n", itemp);
        full = signal(full);
    }
    s = signal(s);
}

void consumer()
{
   s = wait(s);
   if(in == -1 && out == -1)
   {
       printf("Buffer is empty\n");
   }
   else if(in == out)
   {
        full = wait(full);
        itemc = buffer[out];
        buffer[out] = -1;
        in = -1;
        out = -1;
        printf("Consumed item is : %d\n", itemc);
        empty = signal(empty);
   }
   else
   {
        full = wait(full);
        itemc = buffer[out];
        buffer[out] = -1;
        out = (out + 1) % n;
        printf("Consumed item is : %d\n", itemc);
        empty = signal(empty);
   }
   s = signal(s);
}

void display()
{
    int i;
    if(in == -1)
    {
        printf("Buffer is empty\n");
    }
    else
    {
        for(i = 0 ; i < n ; i++)
        {
            if(buffer[i] == -1)
            printf("-\t");
            else
            printf("%d\t", buffer[i]);
        }
        printf("\n");    
    }
}


int main()
{
    int i, option = 4;
    for(i = 0 ; i < n ; i++){
        buffer[i] = -1;
    }
    do
    {
        printf("1. Produce  |  2. Consume  |  3. Display  |  4.Exit  : ");
        scanf("%d", &option);
        switch(option)
        {
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
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid input. Try again\n");
                break;
        }
    }while(option != 4);
    return 0;
}