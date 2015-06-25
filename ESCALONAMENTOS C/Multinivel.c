#include <stdio.h>

struct process{
    int name;
    int burst;
    int waitingTime;
    int burstTotal;
    int tipoEscalonamento;
};

struct process processo[20];

void executaProcessoRR(int,int);
void executaProcessoJSF(int);
void contaWaitingTimeRR(int,int);

int main(){
    int n, quantum,tat[20],avwt=0,avtat=0,i,j;
    printf("\nEntre com o numero de processos (maximum 20): \n");  //Entrada de numero de processos
    scanf("%d", &n);
    printf("\nDigite o Quantum de tempo da CPU para o Round Robin: \n");
    scanf("%d", &quantum);

    for(i=0;i<n;i++){           //Preenchimento de burst dos processos
        printf("\nEntre com o  Burst Time do processo \n");
        printf("P[%d]:", i+1);
        processo[i].name = i+1;
        scanf("%d",&processo[i].burst); //Burst é gravado na struct do processo
        processo[i].waitingTime = 0; //Waiting Time de cada processo se inicia com 0;
        processo[i].burstTotal = processo[i].burst;
        processo[i].tipoEscalonamento = 0; //Tipo de escalonamento 0 é para round robin e 1 para JSF
    }

    for(i=0; i<n; i++){  //Enquanto tiver processo para ser processado, ele executara
        if(processo[i].burst > 0){
            if(processo[i].tipoEscalonamento == 0){ //Primeiro processo de todos é o RoundRobin
                executaProcessoRR(quantum,n);
            }else if(processo[i].tipoEscalonamento == 1){ //Os processos que tiverem o burst maior que o quantum, sao terminados no JSF
                executaProcessoJSF(n);
            }
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

void executaProcessoJSF(int n){
    int lista_JSF[20],lista_JSF_ord[20],i,j,k;
    int insere=0;

    for(i=0; i<n; i++){
        if(processo[i].burst > 0 && processo[i].tipoEscalonamento == 1){
            lista_JSF[insere] = processo[i].burst;
            insere++;
        }
    }

    lista_JSF_ord[0] = lista_JSF[0];

    for(i=1; i<insere; i++){ //Leitura do vetor de burst
        for(j=0; j<=i; j++){ //Leitura de inserção na lista ordenada
            if(lista_JSF[i] < lista_JSF_ord[j]){ // Verifica o burst for menor que algum que ja estiver na lista ele entra no lugar
                for(k=i; k>j; k--){  //Organiza a lista
                    lista_JSF_ord[k] = lista_JSF_ord[k-1];
                }
                lista_JSF_ord[j] = lista_JSF[i];
                break;
            }else if(j==i){
                lista_JSF_ord[j] = lista_JSF[i]; //Insere no fim do vetor se for o maior
                break;
            }
        } // Close second for
    } //Close first for


    for(i=0;i<insere;i++){ //ListaOrdenada
        for(j=0;j<n;j++){ //Lista de processos
            if(processo[j].burst == lista_JSF_ord[i]){ //Encontra o primeiro processo da lista ordenada
                while(processo[j].burst > 0){
                    processo[j].burst -= 1;
                    for(k=0; k<n; k++){
                        if(processo[k].tipoEscalonamento == 1 && processo[k].name != processo[j].name && processo[k].burst > 0){
                            processo[k].waitingTime += 1;
                        }
                    }
                }
                break;
            }
        }
    }
}


void executaProcessoRR(int quantum, int n){
    int i,j;
    for(i=0; i<n; i++){ //percorre processos
        if(processo[i].burst > 0){
            if(processo[i].burst > quantum){
                processo[i].tipoEscalonamento = 1;
            }
            for(j=0; j!=quantum; j++){  //processo sendo executado no tempo do quantum
                if( processo[i].burst != 0){
                    processo[i].burst -= 1;
                    contaWaitingTimeRR(i,n);
                }else{
                    break;
                }
            } //Close second for
        } //Close if
    } //Close first for
}

void contaWaitingTimeRR(int atual, int n){
    int i, j;
    for(i=0; i<n; i++){ //Percorre lista de processos
        if(i != atual){
            if(processo[i].tipoEscalonamento == 0 && processo[i].burst > 0){
                processo[i].waitingTime += 1;  //Conta o tempo de espera do processo
            }
        }
    }
}
