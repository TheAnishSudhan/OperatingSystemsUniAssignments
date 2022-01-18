#include <stdio.h>
int num_process, time_slice, processes[10], exit_times[10], arrival_times[20], waiting_times[20];
int burst_times[20], turnAround_times[20], priority[20], new_priority[20], process_id[20], og_burst_times[20];
int temp, temp2, length=0, length2=0, count=0, temp_burst_times[20], final_exit_times[20];;
//round robin algorithm

int exitTime(int i){
  if (i==0)
    return (arrival_times[i] + burst_times[i]);
  else {
    return (exit_times[i-1] + burst_times[i]);}
}

int turnAroundTime(int i){
  return final_exit_times[i]-arrival_times[i];
}

int waitingTime(int i){
  return turnAround_times[i] - og_burst_times[i];
}

void avgTime(){
  int totalWaitingTime=0, totalTurnAroundTime=0;
  for (int i = 0; i < num_process; i++) {
    totalWaitingTime+=waiting_times[i];
    totalTurnAroundTime+=turnAround_times[i];
  }
  printf("\n\nTOTAL WT TIME: %d\n", totalWaitingTime);
  printf("TOTOAL TA TIME: %d\n", totalTurnAroundTime );
  float avgWaitingTime= (float)totalWaitingTime/(float)num_process;
  float avgTurnAroundTime=(float)totalTurnAroundTime/(float)num_process;

  printf("\n\nThe Average Turn Around Time is: %.2f\n", avgTurnAroundTime );
  printf("The Average Waiting Time is: %.2f",avgWaitingTime );
}

void addProcess(int* array, int i){
  array[num_process+length]=array[i];
  count++;
  length=count/3;
}

void addProcessBurst(int* array, int burst_time){
  array[num_process+length2]=burst_time;
  length2++;
}

int main(){

  printf("Enter the number of processes: " );
  scanf("%d",&num_process);

  printf("Enter the time slice: ");
  scanf("%d",&time_slice);


  for (int i = 0; i < num_process; i++) {

    printf("Enter the burst time for process %d: ",i+1 );
    scanf("%d", &burst_times[i] );

    og_burst_times[i]=burst_times[i];
    temp_burst_times[i]=burst_times[i];

    printf("Enter the arrival time for process %d: ",i+1 );
    scanf("%d", &arrival_times[i] );

    process_id[i]=i+1;

  }

//iterator calc

int iterator=0, temp_iterator=0;

for (int i = 0; i < num_process; i++) {
  while (temp_burst_times[i]>time_slice) {
    if (temp_burst_times[i]>time_slice) {
      temp_burst_times[i]-=time_slice;
      temp_iterator++;
    }
  }
}

iterator=num_process+temp_iterator;

int og_burst_time=0, future_burst_time=0;

for (int i = 0; i < iterator; i++) {
    if (burst_times[i]>time_slice) {

      og_burst_time=burst_times[i];
      burst_times[i]=time_slice;
      future_burst_time=og_burst_time-burst_times[i];
      exit_times[i]=exitTime(i);

      addProcessBurst(&burst_times, future_burst_time);
      addProcess(&arrival_times, i);
      addProcess(&priority, i);
      addProcess(&process_id, i);
  }
  else {
    exit_times[i]=exitTime(i);
  }

}

for (int i = 0; i < num_process; i++) {
  for (int j = 0; j < iterator; j++) {
    if (process_id[j]==(i+1)) {
      final_exit_times[i]=exit_times[j];
    }
  }
}

printf("\n\n");

  for (int i = 0; i < iterator; i++) {

    printf("PROCESS RUNNING: %d\n",process_id[i] );

    printf("Burst time: %d\n",burst_times[i]);

  }

  printf("\n\n");

    for (int i = 0; i < num_process; i++) {

      turnAround_times[i]=turnAroundTime(i);

      waiting_times[i]=waitingTime(i);

      printf("\nProcess %d\n",i+1);

      printf("Turn Around Time: %d\n", turnAround_times[i]);

      printf("Waiting Time: %d\n",waiting_times[i]);
    }


  avgTime();

  return 0;
}
