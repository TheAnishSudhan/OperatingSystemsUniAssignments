#include <stdio.h>
#include <stdlib.h>
char array0[16];
int num=0;
int Total,sumTOT=0,sumWT=0;

struct processes{
    int process_id;
    int arrivalTime;
    int burstTime;
    int exitTime;
    int turnAroundTime;
    int waitingTime;
    int ogBurstTime;
}p1,p2,p3,p4,p5,process[10];

int OGBT(){
    for(int i=0;i<Total;i++){
        process[i].ogBurstTime=process[i].burstTime;
    }
    return 0;
}

int funct(int array1[Total],int i)
{
    for(int u=0;u<Total;u++){
            if(process[array1[u]].burstTime>0){
                process[array1[u]].burstTime--;
                if(process[array1[u]].burstTime==0){
                    process[array1[u]].exitTime=i+1;
                }
                return array1;
            }
            }
            return array1;
}

int main()
{
    printf("Enter number of processes: ");
    scanf("%d",&Total);
    for(int i=0;i<Total;i++)
    {
        printf("Enter Arrival time of process %d: ",i+1);
        scanf("%d",&process[i].arrivalTime);
        printf("Enter Burst time of process %d: ",i+1);
        scanf("%d",&process[i].burstTime);
        process[i].process_id=i+1;
    }

    OGBT();

        for(int i=0;i<6946;i++){
            int array1[Total],z=0;
            for(int a=0;a<Total;a++){
                if(process[a].arrivalTime<=i&&process[a].burstTime>0){
                    array1[z]=a;
                    z++;
                }
            for(int j=0;j<z;j++){
                for(int k=j+1;k<z;k++){
                    if (process[array1[j]].burstTime > process[array1[k]].burstTime)
                    {
                    int w;
                    w =  array1[j];
                    array1[j]=array1[k];
                    array1[k]=w;

                    }

                }
            }
            }
            funct(array1,i);

            array0[i]=process[array1[0]].process_id;
            num=num+1;
            if(process[0].burstTime+process[1].burstTime+process[2].burstTime+process[3].burstTime+process[4].burstTime==0){
                break;
            }
    }
    printf("\n");
    printf("Process \tExit Time \tTurn Around Time \tWaiting Time\n");
    for(int z=0;z<Total;z++)
    {

        process[z].turnAroundTime=process[z].exitTime-process[z].arrivalTime;
        process[z].waitingTime=process[z].turnAroundTime-process[z].ogBurstTime;
        sumTOT+=process[z].turnAroundTime;
        sumWT+=process[z].waitingTime;
        printf("%d\t\t\t",process[z].process_id);
        printf("%d\t\t\t",process[z].exitTime);
        printf("%d\t\t\t",process[z].turnAroundTime);
        printf("%d\n",process[z].waitingTime);
    }
    printf("\nAverage Turn Around time: %f",((float)sumTOT/Total));
    printf("\nAverage Waiting time: %f",((float)sumWT/Total));

}
