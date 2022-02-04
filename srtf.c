#include <stdio.h>
#include <stdbool.h>
int num_process, processes[10], exit_times[10], arrival_times[20], waiting_times[20];
int burst_times[20], turnAround_times[20], priority[20], new_priority[20], process_id[20];
int temp, temp2, og_burst_times[20], final_exit_times[20], og_arrival_times[20], iterator=0,length=0, length2=0, count=0;
//shortest remaining time first

int exitTime(int i){
  if ((i==0)||(arrival_times[i]>exit_times[i-1]))
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

void shiftSpace(int* array, int count, int index){

  int temp=array[count], temp2=0;

  for (int i = count+1; i < 20; i++) {
    temp2=array[i];
    array[i]=temp;
    temp=temp2;
  }

  array[count]=array[index];

  for (int i = index; i < (20-index); i++) {
    array[i]=array[i+1];
  }
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

bool burstTimer(int start){

  int m=burst_times[start], index=start;
  int retainValue = start;

  printf("VAl of m:%d\n",m );

  for (int i = start; i < num_process-1; i++) {
    if ((arrival_times[i]>arrival_times[retainValue])||(burst_times[i]==0)) {
      continue;
    }
    if (m>burst_times[i+1]) {
      m=burst_times[i+1];
      index=i+1;
      // start++;
    }
  }
  for (int i = start+1; i < num_process-1; i++) {
    if ((arrival_times[i]>arrival_times[retainValue])||(burst_times[i]==0))
      continue;
    if ((m==burst_times[i])&&(arrival_times[i]<arrival_times[start])) {
      printf("PRETTY WEIRD m:%d i:%d\n", m, i);
      m=burst_times[i];
      index=i;
    }
  }

  if (index!=start) {
    printf("TRUEEEE index:%d index vaql:%d num:%d\n", index, burst_times[index], num_process);
    return true;
  }
printf("FALSEEE\n");
  return false;
}

int burstTimerIndex(int start){

  int m=burst_times[start], index=start;
  int retainValue = start;

  for (int i = start; i < num_process-1; i++) {
    if ((arrival_times[i]>arrival_times[retainValue])||(burst_times[i]==0)) {
      continue;
    }
    if (m>burst_times[i+1]) {
      m=burst_times[i+1];
      index=i+1;
      // start++;
    }
  }
  for (int i = start+1; i < num_process-1; i++) {
    if ((arrival_times[i]>arrival_times[retainValue])||(burst_times[i]==0))
      continue;
    if ((m==burst_times[i])&&(arrival_times[i]<arrival_times[start])) {
      m=burst_times[i];
      index=i;
    }
  }

  return index;
} //returns index of least burst time

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

    process_id[i]=i+1;

  }

//Sorting as per arrival time

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

//calculating exit times

for (int i = 0; i < num_process; i++) {
  exit_times[i]=exitTime(i);
}

int timer=exit_times[num_process-1];

int og_burst_time=0, index=0, future_burst_time=0;
int k=1;

for (int i = 0; i < num_process; i++) {

  // if ((burstTimer(i,k))&&()) {
  //   /* code */
  // }
  //do stuff
  // for (int i2 = 0; i2 < i; i2++) {
  //   int maxArrTime=arrival_times[i2];
  //   int maxArrTimeIndex=0;
  //   if (maxArrTime<arrival_times[i2+1]) {
  //     maxArrTime=arrival_times[i2+1];
  //     maxArrTimeIndex=i2+1;
  //   }
  //   /* code */
  // }

  if ((exit_times[i]>arrival_times[i+1])&&(burstTimer(i))) {
    printf("RUNNNING \n");
    index=burstTimerIndex(i);
    // int tempAT = arrival_times[index];
    // int tempBT = burst_times[index];
    // int tempET = exit_times[index];
    // int tempPID = process_id[index];



    // arrival_times[i+1]=tempAT;
    // burst_times[i+1]=tempBT;
    // exit_times[i+1]=tempET;
    // process_id[i+1]=tempPID;

    //add theleftovertime in the end using addProcess from Round Robin

    og_burst_time=burst_times[i];
    if (arrival_times[index]>arrival_times[i]) {
      burst_times[i]=arrival_times[index]-arrival_times[i];
    }
    printf("OG Bt:%d, NW BT:%d\n",og_burst_time, burst_times[i]);
    printf("CU AT:%d, NT AT:%d\n",arrival_times[i], arrival_times[index] );
    future_burst_time=og_burst_time-burst_times[i];
    exit_times[i]=exitTime(i);

    // shiftSpace(&burst_times, i+1, index);
    // shiftSpace(&exit_times, i+1, index);
    // shiftSpace(&arrival_times, i+1, index);
    // shiftSpace(&process_id, i+1, index);
    //
    makeSpace(&burst_times, i+1);
    makeSpace(&exit_times, i+1);
    makeSpace(&arrival_times, i+1);
    makeSpace(&process_id, i+1);

    burst_times[i+1]=burst_times[index];
    exit_times[i+1]=exit_times[index];
    arrival_times[i+1]=arrival_times[index];
    process_id[i+1]=process_id[index];

    printf("bt next :%d\n",burst_times[i+1] );

    removeSpace(&burst_times, index);
    removeSpace(&exit_times, index);
    removeSpace(&arrival_times, index);
    removeSpace(&process_id, index);

    if(future_burst_time!=0){
      addProcess(&exit_times, i);
      addProcess(&arrival_times, i);
      addProcess(&process_id, i);
      addProcessBurst(&burst_times, future_burst_time);
    }

    num_process++;
    printf("THe bt:%d and the process:%d\n",future_burst_time, process_id[i] );
    for (int i = 0; i < num_process; i++) {
      printf("FIRST CHECK\n");

      printf("PROCESS RUNNING: %d\n",process_id[i] );

      printf("Exit Time: %d\n", exit_times[i]);

      printf("Burst time: %d\n",burst_times[i]);

      printf("Arrival time: %d\n",arrival_times[i]);

    }

    // REPLACEINDEXWITH i+1 or whatever is appropriate

    // if (burst_times[i]==0) {
    //   removeSpace(&burst_times, i);
    //   removeSpace(&exit_times, i);
    //   removeSpace(&arrival_times, i);
    //   // removeSpace(&priority, i);
    //   removeSpace(&process_id, i);
    //
    //   exit_times[i]=exitTime(i);
    // }
    // iterator++;
    k+=2;
  }
  else {
    k++;
    printf("ELSE Running\n");
    exit_times[i]=exitTime(i);
  }
}

for (int i = 0; i < num_process; i++) {
  for (int j = 0; j < 6; j++) {
    if (process_id[j]==(i+1)) {
      final_exit_times[i]=exit_times[j];
    }
  }
}

for (int i = 0; i < num_process; i++) {

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
