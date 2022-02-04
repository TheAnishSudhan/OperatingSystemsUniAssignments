#include <stdio.h>
int num_process, processes[10], exit_times[10], arrival_times[10], waiting_times[10];
int burst_times[10], turnAround_times[10];
int temp, temp2;
//shortest job first

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
    }
  }

  //make logic for sjf where arrival time is accounted for

for (int j = 0; j < num_process; j++) {
  for (int i = j; i < num_process; i++) {
    if ((exit_times[j]<arrival_times[i])&&(burst_times[i]<burst_times[j])) { //messed up logic
      temp=arrival_times[i];
      arrival_times[i]=arrival_times[j];
      arrival_times[j]=temp;

      temp2=burst_times[i];
      burst_times[i]=burst_times[j];
      burst_times[j]=temp2;
    }
  }
}

  for (int i = 0; i < num_process; i++) {

    exit_times[i]=exitTime(i);
    printf("Exit times: %d\n", exit_times[i] );

    turnAround_times[i]=turnAroundTime(i);

    waiting_times[i]=waitingTime(i);
    printf("Waiting times %d\n",waitingTime(i) );
      printf("TA times %d\n",turnAroundTime(i) );
  }

  avgTime();

  return 0;
}
