#include <stdio.h>

struct process{
    int name;
    int burst;
    int waitingTime;
    int burstTotal;
};

struct processRR processo[20];

void executaProcesso(int,int);
void contaWaitingTime(int,int);

int main(){
    int n, quantum,tat[20],avwt=0,avtat=0,i,j;
    printf("\nEntre com o numero de processos (maximum 20): \n");  //Entrada de numero de processos
    scanf("%d", &n);
    printf("\nDigite o Quantum de tempo da CPU: \n");
    scanf("%d", &quantum);

    for(i=0;i<n;i++){           //Preenchimento de burst dos processos
        printf("\nEntre com o  Burst Time do processo \n");
        printf("P[%d]:", i+1);
        processo[i].name = i+1;
        scanf("%d",&processo[i].burst); //Burst é gravado na struct do processo
        processo[i].waitingTime = 0; //Waiting Time de cada processo se inicia com 0;
        processo[i].burstTotal = processo[i].burst;
    }

    for(i=0; i<n; i++){  //Enquanto tiver processo para ser processado, ele executara
        if(processo[i].burst > 0){
            executaProcesso(quantum,n);
            i = 0;
        }
    }


    printf("\nProcess\t\tBurst time\tWaiting Time\tTurnaround Time"); //Cabeçalho

    for(i=0;i<n;i++){
        tat[i]=processo[i].burstTotal+processo[i].waitingTime; //TurnAroundTime = BurstTime + WaitingTime
        avwt+=processo[i].waitingTime;  //AverageWaitingTime = AverageWaitingTime + WaitingTime
        avtat+=tat[i]; //AverageTurnAroundTime = AverageTurnAroundTime + TurnAroundTime

        printf("\nP[%d]\t\t%d\t\t%d\t\t%d", processo[i].name,processo[i].burstTotal,processo[i].waitingTime,tat[i]); //Apresetação da linha de dados da tabela
    }

    avwt/=i; //AverageWaitingTime = AverageWaitingTime / numero de processos
    avtat/=i; //AverageTurnAroundTime = AverageTurnAroundTime / numero de processos
    printf("\n\nAverage Waiting Time: %d", avwt);
    printf("\nAverage Turnaround Time: %d\n\n", avtat);
    return 0;
}


void executaProcesso(int quantum, int n){
    int i,j;
    for(i=0; i<n; i++){ //percorre processos
        if(processo[i].burst > 0){
            for(j=0; j!=quantum; j++){  //processo sendo executado no tempo do quantum
                if( processo[i].burst != 0){
                    processo[i].burst -= 1;
                    contaWaitingTime(i,n);
                }else{
                    break;
                }
            } //Close second for
        } //Close if
    } //Close first for
}

void contaWaitingTime(int atual, int n){
    int i, j;
    for(i=0; i<n; i++){ //Percorre lista de processos
        if(i != atual){
            if(processo[i].burst > 0){
                processo[i].waitingTime += 1;  //Conta o tempo de espera do processo
            }
        }
    }
}
