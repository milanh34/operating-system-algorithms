#include<stdio.h>
int n = 10;

int main() {
  int p_no, r_no, c = 0, i, j, allocation[n][n], max[n][n], need[n][n], safe_seq[n], available[n], completed[n], t = 0;
  printf("Enter no. of processes : ");
  scanf("%d", &p_no);
  printf("Enter no. of resources : ");
  scanf("%d", &r_no);
  printf("Enter allocation and max resources for all processes\n");
  for(i = 0 ; i < p_no ; i++){
      printf("Allocated resources of Process %d : ", i);
      for(j = 0 ; j < r_no ; j++){
          scanf("%d", &allocation[i][j]);
      }
      printf("Max resources of Process %d : ", i);
      for(j = 0 ; j < r_no ; j++){
          scanf("%d", &max[i][j]);
      }
      for(j = 0 ; j < r_no ; j++){
          need[i][j] = max[i][j] - allocation[i][j];
      }
      completed[i] = 0;
  }
  printf("\nEnter available resources : ");
  for(i = 0 ; i < r_no ; i++){
      scanf("%d", &available[i]);
  }
  while(c < p_no){
    for(i = 0 ; i < p_no ; i++){
      if(completed[i] != 1){
        for(j = 0 ; j < r_no ; j++){
          if(need[i][j] > available[j]){
              break;
          }
        }
        if(j == r_no) {
          safe_seq[c] = i;
          completed[i] = 1;
          for(j = 0 ; j < r_no ; j++){
            available[j] = available[j] + allocation[i][j];
          }
          c++;
          t = 0;
        }
        else{
          t++;
        }
      }
    }
    if(t == (p_no - 1)){
      printf("\nSafe sequence does not exist !\n");
      break;
    }
  }
  
  if(t != (p_no - 1)){
      printf("-------------------------------------------------\n");
  printf("|  Process\t|Allocation\t|\tMax\t\t|\tNeed\t|\n");
  printf("-------------------------------------------------\n");
  for(i = 0 ; i < p_no ; i++){
      printf("|\tP%d\t\t|\t", i + 1);
      for(j = 0 ; j < r_no ; j++){
          printf("%d ", allocation[i][j]);
      }
      printf("\t|\t");
      for(j = 0 ; j < r_no ; j++){
          printf("%d ", max[i][j]);
      }
      printf("\t|\t");
      for(j = 0 ; j < r_no ; j++){
          printf("%d ", need[i][j]);
      }
      printf("\t|\n");
  }
  printf("-------------------------------------------------\n");
    printf("\nAvailable resources after completion : ");
    for(i = 0 ; i < r_no ; i++) {
      printf("%d ", available[i]);
    }
    printf("\nSafe sequence : < ");
    for(i = 0 ; i < p_no ; i++) {
      printf("P%d ", safe_seq[i]);
    }
    printf(" >");
  }
  return 0;
}