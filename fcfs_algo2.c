#include <stdio.h>
int num_process, processes[10], exit_times[10], arrival_times[10], completion_times[10], burst_times[10], turnAround_times[10], temp[10], temp2[10];


int exitTime(int burst_time, int i){
  if (i==0)
    return 0;
  return (burst_times[i-1] + exit_times[i-1]);
}

int completion_time(int i){
  return exit_times[i] + burst_times[i];
}

int turnAround_time(int i){
  return completion_times[i]-arrival_times[i];
}

// void avgTime(){
//   int totalWaitingTime=0, totalTurnAroundTime=0;
//   for (int i = 0; i < num_process; i++) {
//     totalWaitingTime+=waiting_times[i];
//     totalTurnAroundTime+=turnAround_times[i];
//   }
//   float avgWaitingTime= (float)totalWaitingTime/(float)num_process;
//   float avgTurnAroundTime=(float)totalTurnAroundTime/(float)num_process;
//
//   printf("\n\nThe Average Waiting Time is: %.2f\n",avgWaitingTime );
//   printf("The Average Turn Around Time is: %.2f", avgTurnAroundTime );
// }

void reorderArrivalTime(){
  for (int i = 1; i < num_process; i++) {
    if (arrival_times[i]<arrival_times[i-1]) {
      temp[i]=arrival_times[i-1];
      arrival_times[i-1]=arrival_times[i];
      arrival_times[i]=temp[i];

      temp2[i]=burst_times[i-1];
      burst_times[i-1]=burst_times[i];
      burst_times[i]=temp2[i];
      /* code */
    }/* code */
  }
}

void main(){

  printf("Enter the number of processes: " );
  scanf("%d",&num_process);


  for (int i = 0; i < num_process; i++) {
    printf("Enter the burst time for process %d: ",i+1 );
    scanf("%d", &burst_times[i] );

    printf("Enter the arrival time for process %d: ",i+1 );
    scanf("%d", &arrival_times[i] );

  }

  reorderArrivalTime();

  for (int i = 0; i < num_process; i++) {

    exit_times[i]=exitTime(burst_times[i], i);

    completion_times[i]=completion_time(i);

    turnAround_times[i]=turnAround_time(i);
  }

  for (int i = 0; i < num_process; i++) {
    printf("Exit Times\n" );
    printf("%d\n", exit_times[i]);

  }

  for (int i = 0; i < num_process; i++) {
    printf("Completion Times\n" );
    printf("%d\n", completion_times[i]);

  }

  for (int i = 0; i < num_process; i++) {
    printf("Turn Around Times\n" );
    printf("%d\n", turnAround_times[i]);
  }

  //avgTime();

//average waiting time and waiting time
//completion time
//turn around time = completion time - arrival time
// arrival time

//pt 3
// exit time = burst times of all thise ahead
// for exit time, order as per lower range, then thsat would wait  time
//ta time = exit time - arrival time
//waiting time = ta time - burst time
//

//need to create a dummy set of arrays to do the computation and then input values in the og arrays

}
