#include <stdio.h>

int main(){
    int n, bt[20],wt[20],tat[20],avwt=0,avtat=0,i,j;
    printf("Enter total number od processes (maximum 20):");  //Entrada de numero de processos
    scanf("%d", &n);
    printf("\nEnter Process Burst Time\n");

    for(i=0;i<n;i++){           //Preenchimento de burst dos processos
        printf("P[%d]:", i+1);
        scanf("%d",&bt[i]); //Burst é gravado em bt[]
    }

    wt[0]=0; //O tempo de espera para o primeiro processo é 0

    for(i=1;i<n;i++){
        wt[i]=0;
        for(j=0;j<i;j++){
            wt[i]+=bt[j];  //Somatório do tempo de Waiting Time
        }
    }

    printf("\nProcess\t\tBurst time\tWaiting Time\tTurnaround Time"); //Cabeçalho

    for(i=0;i<n;i++){
        tat[i]=bt[i]+wt[i]; //TurnAroundTime = BurstTime + WaitingTime
        avwt+=wt[i];  //AverageWaitingTime = AverageWaitingTime + WaitingTime
        avtat+=tat[i]; //AverageTurnAroundTime = AverageTurnAroundTime + TurnAroundTime
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d", i+1,bt[i],wt[i],tat[i]); //Apresetação da linha de dados da tabela
    }

    avwt/=i; //AverageWaitingTime = AverageWaitingTime / numero de processos
    avtat/=i; //AverageTurnAroundTime = AverageTurnAroundTime / numero de processos
    printf("\n\nAverage Waiting Time: %d", avwt);
    printf("\nAverage Turnaround Time: %d", avtat);
    return 0;
}
