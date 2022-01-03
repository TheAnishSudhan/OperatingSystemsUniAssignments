#include <stdio.h>
int num_process, processes[10], waiting_times[10], arrival_times[10], completion_times[10], burst_times[10], turnAround_times[10];


int waitingTime(int burst_time, int i){
  if (i==0)
    return 0;
  return (burst_times[i-1] + waiting_times[i-1]);
}

int completion_time(int i){
  return waiting_times[i] + burst_times[i];
}

int turnAround_time(int i){
  return completion_times[i]-arrival_times[i];
}

void avgTime(){
  int totalWaitingTime=0, totalTurnAroundTime=0;
  for (int i = 0; i < num_process; i++) {
    totalWaitingTime+=waiting_times[i];
    totalTurnAroundTime+=turnAround_times[i];
  }
  float avgWaitingTime= (float)totalWaitingTime/(float)num_process;
  float avgTurnAroundTime=(float)totalTurnAroundTime/(float)num_process;

  printf("\n\nThe Average Waiting Time is: %.2f\n",avgWaitingTime );
  printf("The Average Turn Around Time is: %.2f", avgTurnAroundTime );
}

void main(){

  printf("Enter the number of processes: " );
  scanf("%d",&num_process);


  for (int i = 0; i < num_process; i++) {
    printf("Enter the burst time for process %d: ",i+1 );
    scanf("%d", &burst_times[i] );

    printf("Enter the arrival time for process %d: ",i+1 );
    scanf("%d", &arrival_times[i] );

    waiting_times[i]=waitingTime(burst_times[i], i);

    completion_times[i]=completion_time(i);

    turnAround_times[i]=turnAround_time(i);
  }

  avgTime();

}
