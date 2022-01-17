#include <stdio.h>
int num_process, processes[10], exit_times[10], arrival_times[20], waiting_times[20];
int burst_times[20], turnAround_times[20], priority[20], new_priority[20], process_id[20];
int original_burst_times[10], original_arrival_times[10], original_exit_times[10];
int temp, temp2;
//priority

int exitTime(int i){
  if ((i==0) || (original_arrival_times[i]>original_exit_times[i-1]))
    return (original_arrival_times[i] + original_burst_times[i]);
  else
    return (exit_times[i-1] + original_burst_times[i]);
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

void makeSpace(int* array, int count){

  int temp=array[count];

  for (int i = count+1; i < 20; i++) {
    temp2=array[i];
    array[i]=temp;
    temp=temp2;
  }
}

int main(){

  printf("Enter the number of processes: " );
  scanf("%d",&num_process);


  for (int i = 0; i < num_process; i++) {

    printf("Enter the burst time for process %d: ",i+1 );
    scanf("%d", &original_burst_times[i] );

    printf("Enter the arrival time for process %d: ",i+1 );
    scanf("%d", &original_arrival_times[i] );

    printf("Enter priority for process %d: \n",i+1 );
    scanf("%d", &priority[i] );

    process_id[i]=i+1;

  }

// for (int j = 0; j < num_process; j++) {
//   for (int i = j; i < num_process; i++) {
//     if (arrival_times[i]<arrival_times[j]) {
//       temp=arrival_times[i];
//       arrival_times[i]=arrival_times[j];
//       arrival_times[j]=temp;
//
//       temp2=burst_times[i];
//       burst_times[i]=burst_times[j];
//       burst_times[j]=temp2;
//     }
//     if ((arrival_times[i]==arrival_times[j])&&priority[i]<priority[j]&&i<j) {
//       printf("Change happening\n" );
//       temp=arrival_times[i];
//       arrival_times[i]=arrival_times[j];
//       arrival_times[j]=temp;
//
//       temp2=burst_times[i];
//       burst_times[i]=burst_times[j];
//       burst_times[j]=temp2;
//     }
//   }
// }


for (int j = 0; j < num_process; j++) {
  for (int i = j; i < num_process; i++) {
    if (arrival_times[i]<arrival_times[j]) {
      temp=original_arrival_times[i];
      original_arrival_times[i]=original_arrival_times[j];
      original_arrival_times[j]=temp;

      temp2=original_burst_times[i];
      original_burst_times[i]=original_burst_times[j];
      original_burst_times[j]=temp2;
    }
    if ((arrival_times[i]==arrival_times[j])&&priority[i]<priority[j]) {
      temp=original_arrival_times[i];
      original_arrival_times[i]=original_arrival_times[j];
      original_arrival_times[j]=temp;

      temp2=original_burst_times[i];
      original_burst_times[i]=original_burst_times[j];
      original_burst_times[j]=temp2;

      temp2=priority[i];
      priority[i]=priority[j];
      priority[j]=temp2;
    }
  }
}

for (int i = 0; i < num_process; i++) {

  original_exit_times[i]=exitTime(i);
  exit_times[i]=original_exit_times[i];
  printf("Exit time: %d\n", original_exit_times[i]);

  arrival_times[i]=original_arrival_times[i];

  new_priority[i]=priority[i];

  original_burst_times[i]=burst_times[i];

}

for (int i = 0; i < 20; i++) {
    if ((exit_times[i]>original_arrival_times[i+1])&&(new_priority[i]<new_priority[i+1])) {

      makeSpace(&original_burst_times, i+2);
      makeSpace(&exit_times, i+2);
      makeSpace(&original_arrival_times, i+2);
      makeSpace(&new_priority, i+2);
      makeSpace(&process_id, i+2);

      original_burst_times[i+2]=exit_times[i]-arrival_times[i]+1;
      original_arrival_times[i+2]=original_arrival_times[i];
      new_priority[i+2]=new_priority[i];
      process_id[i+2]=process_id[i];
      exit_times[i+2]=exitTime(i+2);

      printf("Process %d runs now\n",process_id[i] );
      printf("The i running now is: %d \n",i );


  }
}

//print the process getting executed-> maybe ccreate a process_id[] array
//create a new set of arrays for burst time etc and then use them for computing averages


for (int i = 0; i < num_process; i++) {

  printf("Exit time: %d\n", exit_times[i]);

  arrival_times[i];

  new_priority[i];

  original_burst_times[i];

}


  for (int i = 0; i < num_process; i++) {

    exit_times[i]=exitTime(i);

    turnAround_times[i]=turnAroundTime(i);

    waiting_times[i]=waitingTime(i);
  }

  for (int i = 0; i < num_process; i++) {
    printf("Exit Times: " );
    printf("%d\n", exit_times[i]);

    printf("Turn Around Times: " );
    printf("%d\n", turnAround_times[i]);

    printf("Waiting Times: " );
    printf("%d\n", waiting_times[i]);

    printf("Burst times for process %d: ",i+1 );
    printf("%d\n", burst_times[i] );

    printf("Arrival times for process %d: ",i+1 );
    printf("%d\n", arrival_times[i] );

  }

  avgTime();

  return 0;
}
