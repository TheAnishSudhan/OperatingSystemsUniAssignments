#include <stdio.h>
int num_process, processes[10], exit_times[10], arrival_times[10], waiting_times[10];
int burst_times[10], turnAround_times[10], priority[10];
int temp, temp2;
//priority

int exitTime(int i){
  if ((i==0) || (arrival_times[i]>exit_times[i-1]))
    return (arrival_times[i] + burst_times[i]);
  else
    return (exit_times[i-1] + burst_times[i]);
}

int turnAroundTime(int i){
  return exit_times[i]-arrival_times[i];
}

int waitingTime(int i){
  return turnAround_times[i] - burst_times[i];
}


void avgTime(){
  int totalWaitingTime=0, totalTurnAroundTime=0;
  for (int i = 0; i < num_process; i++) {
    totalWaitingTime+=waiting_times[i];
    totalTurnAroundTime+=turnAround_times[i];
  }
  float avgWaitingTime= (float)totalWaitingTime/(float)num_process;
  float avgTurnAroundTime=(float)totalTurnAroundTime/(float)num_process;

  printf("\n\nThe Average Turn Around Time is: %.2f\n", avgTurnAroundTime );
  printf("The Average Waiting Time is: %.2f",avgWaitingTime );
}

int main(){

  printf("Enter the number of processes: " );
  scanf("%d",&num_process);


  for (int i = 0; i < num_process; i++) {
    printf("Enter the burst time for process %d: ",i+1 );
    scanf("%d", &burst_times[i] );

    printf("Enter the arrival time for process %d: ",i+1 );
    scanf("%d", &arrival_times[i] );

    printf("Enter priority for process %d \n(Enter 1 in case of no same arrival time) ",i+1 );
    scanf("%d", &priority[i] );

  }

for (int j = 0; j < num_process; j++) {
  for (int i = j; i < num_process; i++) {
    if (arrival_times[i]<arrival_times[j]) {
      temp=arrival_times[i];
      arrival_times[i]=arrival_times[j];
      arrival_times[j]=temp;

      temp2=burst_times[i];
      burst_times[i]=burst_times[j];
      burst_times[j]=temp2;
    }
    if ((arrival_times[i]==arrival_times[j])&&priority[i]<priority[j]) {
      temp=arrival_times[i];
      arrival_times[i]=arrival_times[j];
      arrival_times[j]=temp;

      temp2=burst_times[i];
      burst_times[i]=burst_times[j];
      burst_times[j]=temp2;

      temp2=priority[i];
      priority[i]=priority[j];
      priority[j]=temp2;
    }
  }
}

  for (int i = 0; i < num_process; i++) {

    exit_times[i]=exitTime(i);

    turnAround_times[i]=turnAroundTime(i);

    waiting_times[i]=waitingTime(i);
  }
  //
  // for (int i = 0; i < num_process; i++) {
  //   printf("Exit Times: " );
  //   printf("%d\n", exit_times[i]);
  //
  //   printf("Turn Around Times: " );
  //   printf("%d\n", turnAround_times[i]);
  //
  //   printf("Waiting Times: " );
  //   printf("%d\n", waiting_times[i]);
  //
  //   printf("Burst times for process %d: ",i+1 );
  //   printf("%d\n", burst_times[i] );
  //
  //   printf("Arrival times for process %d: ",i+1 );
  //   printf("%d\n", arrival_times[i] );
  //
  //   printf("Priority for process %d: ",i+1 );
  //   printf("%d\n", priority[i] );
  //
  // }

  avgTime();

  return 0;
}
