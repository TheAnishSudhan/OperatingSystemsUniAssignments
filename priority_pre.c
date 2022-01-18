#include <stdio.h>
#include <stdbool.h>
int num_process, processes[10], exit_times[10], arrival_times[20], waiting_times[20];
int burst_times[20], turnAround_times[20], priority[20], new_priority[20], process_id[20];
int temp, temp2, og_burst_times[20], final_exit_times[20], og_arrival_times[20], iterator=0;;
//pre-emtive priority scheduking

int exitTime(int i){
  if (i==0)
    return (arrival_times[i] + burst_times[i]);
  else{
    return (exit_times[i-1] + burst_times[i]);}
}

int turnAroundTime(int i){
  return final_exit_times[i]-og_arrival_times[i];
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
  printf("TOTAL WT TIME: %d\n", totalWaitingTime);
  printf("TOTAL TA TIME: %d\n", totalTurnAroundTime );
  float avgWaitingTime= (float)totalWaitingTime/(float)num_process;
  float avgTurnAroundTime=(float)totalTurnAroundTime/(float)num_process;

  printf("\n\nThe Average Turn Around Time is: %.2f\n", avgTurnAroundTime );
  printf("The Average Waiting Time is: %.2f",avgWaitingTime );
}

void makeSpace(int* array, int count){

  int temp=array[count], temp2=0;

  for (int i = count+1; i < 20; i++) {
    temp2=array[i];
    array[i]=temp;
    temp=temp2;
  }
}

void removeSpace(int* array, int count){

  for (int i = count; i < (20-count); i++) {
    array[i]=array[i+1];
  }
}

bool zeroes(int* array, int posn){
  int count=0;
  for (int i = 0; i < 3; i++) {
    if (array[i]==0) {
      count++;
    }
  }
  if (count==3) {
    return false;
  }
  return true;
}

int main(){

  printf("Enter the number of processes: " );
  scanf("%d",&num_process);


  for (int i = 0; i < num_process; i++) {

    printf("Enter the burst time for process %d: ",i+1 );
    scanf("%d", &burst_times[i] );

    og_burst_times[i]=burst_times[i];

    printf("Enter the arrival time for process %d: ",i+1 );
    scanf("%d", &arrival_times[i] );

    og_arrival_times[i]=arrival_times[i];

    printf("Enter priority for process %d: \n",i+1 );
    scanf("%d", &priority[i] );

    process_id[i]=i+1;

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
}

int og_burst_time=0;

for (int i = 0; i < 20; i++) {
    if ((exit_times[i]>arrival_times[i+1])&&(priority[i]>priority[i+1])&&(burst_times[i]!=0)&&(burst_times[i+1]!=0)) {

      makeSpace(&burst_times, i+2);
      makeSpace(&exit_times, i+2);
      makeSpace(&arrival_times, i+2);
      makeSpace(&priority, i+2);
      makeSpace(&process_id, i+2);

      og_burst_time=burst_times[i];
      if ((arrival_times[i+1]-exit_times[i-1])<0) {
        burst_times[i]=0;
      } else {
        burst_times[i]=arrival_times[i+1]-exit_times[i-1];
      }
      if (burst_times[i]==0) {
        burst_times[i+2]=og_burst_time;
      } else {
        burst_times[i+2]=og_burst_time-burst_times[i];
      }
      arrival_times[i+2]=arrival_times[i];
      priority[i+2]=priority[i];
      process_id[i+2]=process_id[i];
      exit_times[i]=exitTime(i);

      if (burst_times[i]==0) {
        removeSpace(&burst_times, i);
        removeSpace(&exit_times, i);
        removeSpace(&arrival_times, i);
        removeSpace(&priority, i);
        removeSpace(&process_id, i);

        exit_times[i]=exitTime(i);
      }
      iterator++;
  }
  else if((burst_times[i]!=0)){
    exit_times[i]=exitTime(i);
    iterator++;
  }
}

for (int i = 0; i < num_process; i++) {
  for (int j = 0; j < 6; j++) {
    if (process_id[j]==(i+1)) {
      final_exit_times[i]=exit_times[j];
    }
  }
}

for (int i = 0; i < iterator; i++) {

  printf("PROCESS RUNNING: %d\n",process_id[i] );

  printf("Exit Time: %d\n", exit_times[i]);

  printf("Burst time: %d\n",burst_times[i]);

  printf("Arrival time: %d\n",arrival_times[i]);

}

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
