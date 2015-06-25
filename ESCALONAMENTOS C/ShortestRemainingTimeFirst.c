#include <stdio.h>

struct process{
    int name;
    int burst;
    int waitingTime;
    int burstTotal;
    int chegada;
};

struct process processo[20];

int verificaEntrada(int,int);
void executarProcesso(int,int,int);
void verificaWaitingTime(int,int,int);
int selecionaNovoProcesso(int);
int verificaFim(int);

int aguardando[20];

int main(){
    int n, tat[20],avwt=0,avtat=0,i,j;
    int pronto=0,aux_pronto=0;

    printf("Enter total number od processes (maximum 20):");  //Entrada de numero de processos
    scanf("%d", &n);

    for(i=0;i<n;i++){           //Preenchimento de burst dos processos
        printf("\nEntre com o Burst time do processo\n");
        printf("P[%d]:", i+1);
        processo[i].name = i+1;
        scanf("%d",&processo[i].burst); //Burst é gravado
        processo[i].burstTotal = processo[i].burst;
        printf("\nEntre com o tempo de chegada do processo");
        scanf("%d",&processo[i].chegada); //Tempo de entrada dos processos

    }

    for(i=0; i<100; i++){
        aux_pronto = verificaEntrada(i,n);
        if(aux_pronto > 0){ //Se aux_pronto for maior que 0, algum processo entrou nesse tempo de chegada
            if(pronto!=0 && processo[aux_pronto-1].burst < processo[pronto-1].burst){ //Se ja existe um processo sendo executado mas o que esta entrando tem burst menor
                pronto = aux_pronto; //muda o processo que entrou para ser executado
                executarProcesso(pronto,i,n); //executa processo que entrou
            }else if(pronto!=0 && processo[aux_pronto-1].burst >= processo[pronto-1].burst){//Se ja existe um processo sendo executado mas o que entrou tem burst maior ou igual
                if(processo[pronto-1].burst!=0){ //Verifica se o processo sendo executado ainda tem burst para ser processado
                    executarProcesso(pronto,i,n);
                }else{
                    pronto = selecionaNovoProcesso(n);// se acabou o burst do processo, seleciona um novo
                    if(pronto == 0){
                        continue;
                    }else{
                        executarProcesso(pronto,i,n);
                    }
                }

            }else{
                pronto = aux_pronto;
                executarProcesso(pronto,i,n);
            }
        }else if(aux_pronto == 0 && pronto != 0){
            if(processo[pronto-1].burst!=0){ //Verifica se o processo sendo executado ainda tem burst para ser processado
                executarProcesso(pronto,i,n);
            }else{
                pronto = selecionaNovoProcesso(n);// se acabou o burst do processo, seleciona um novo
                if(pronto == 0){
                        break;
                }else{
                        executarProcesso(pronto,i,n);
                }
            }
        }
        if(verificaFim(n) == 0){
            break;
        }
    }

    printf("\nProcess\t\tTempo de Entrada\tBurst time\tWaiting Time\tTurnaround Time"); //Cabeçalho

    for(i=0;i<n;i++){
        tat[i]=processo[i].burstTotal+processo[i].waitingTime; //TurnAroundTime = BurstTime + WaitingTime
        avwt+=processo[i].waitingTime;  //AverageWaitingTime = AverageWaitingTime + WaitingTime
        avtat+=tat[i]; //AverageTurnAroundTime = AverageTurnAroundTime + TurnAroundTime
        printf("\nP[%d]\t\t%d\t\t\t%d\t\t%d\t\t%d", processo[i].name,processo[i].chegada,processo[i].burstTotal,processo[i].waitingTime,tat[i]); //Apresetação da linha de dados da tabela
    }

    avwt/=i; //AverageWaitingTime = AverageWaitingTime / numero de processos
    avtat/=i; //AverageTurnAroundTime = AverageTurnAroundTime / numero de processos
    printf("\n\nAverage Waiting Time: %d", avwt);
    printf("\nAverage Turnaround Time: %d", avtat);
    return 0;
}

int verificaFim(int n){
    int i,cont=0;
    for(i=0; i<n; i++){
        if(processo[i].burst != 0){
            cont++;
        }
    }
    if(cont>0){
        return 1;
    }else{
        return 0;
    }
}

int selecionaNovoProcesso(int n){
    int i,j,burst=0,name=0;
    for(i=0; i<n ; i++){
        if(processo[i].burst != 0 ){//Verifica algum processo com burst para ser processado
            name = processo[i].name;
            burst = processo[i].burst;
            for(j=i; j<n; j++){
                if(processo[j].burst > 0 && processo[j].burst < burst){
                    name = processo[j].name;
                    burst = processo[j].burst;
                }
            }
            return name;
        }
    }
    return burst;
}

void verificaWaitingTime(int tempoAtual,int n,int id){
    int i;
    for(i=0; i<n; i++){
        if(i != id-1 && processo[i].chegada <= tempoAtual && processo[i].burst!=0){
         //Se o processo tem o tempo de chegada menor que o tempo atual e não esta sendo executado e tem o burst diferente de  0
            processo[i].waitingTime = processo[i].waitingTime + 1;
        }
    }
}

void executarProcesso(int id, int tempo, int n){
    processo[id-1].burst = processo[id-1].burst - 1; //Diminui um tempo no burst do processo sendo executado
    verificaWaitingTime(tempo, n, id);
}

int verificaEntrada(int tempo, int n){
    int pronto = 0,i;
    for(i=0; i<n; i++){ //percorre processos
        if(processo[i].chegada == tempo){ //Verifica se algum processo tem a CHEGADA nesse TEMPO
            pronto = processo[i].name;
        }
    }
    return pronto;
}
