#include <stdio.h>

struct processM{
    int name;
    int burst;
    int waitingTime;
    int burstTotal;
    int tipoEscalonamento;
};

struct processM processoM[20];

struct processRR{
    int name;
    int burst;
    int waitingTime;
    int burstTotal;
};

struct processRR processoRR[20];

struct processSRTF{
    int name;
    int burst;
    int waitingTime;
    int burstTotal;
    int chegada;
};

struct processSRTF processoSRTF[20];

void fcfs();
void sjf();
void srtf();
void roundrobin();
void multinivel();

int verificaEntradaSRTF(int,int);
void executarProcessoSRTF(int,int,int);
void verificaWaitingTimeSRTF(int,int,int);
int selecionaNovoProcessoSRTF(int);
int verificaFimSRTF(int);

void executaProcessoRR(int,int);
void contaWaitingTimeRR(int,int);

void executaProcessoRRM(int,int);
void executaProcessoJSFM(int);
void contaWaitingTimeRRM(int,int);


int main (void )
{
  int valor;

  printf ("Digite um escalonamento: \n\n");
  printf ("1) FCFS \n");
  printf ("2) SJF \n");
  printf ("3) SRTF \n");
  printf ("4) ROUND ROBIN \n");
  printf ("5) MULTINIVEL \n");
  printf ("6) SAIR \n\n");
  scanf("%d", &valor);

  switch ( valor )
  {
     case 1 :
       fcfs();
     break;

     case 2 :
       sjf();;
     break;

     case 3 :
        srtf();;
     break;

     case 4 :
        roundrobin();
     break;

     case 5 :
        multinivel();
     break;

     case 6 :
        printf ("\nFim.\n");
     break;

     default :
       printf ("Valor invalido!\n");
  }

  return 0;
}

//********************************************************************************************************
//********************************************************************************************************
//                                ESCALONAMENTO FCFS
//*******************************************************************************************************
//********************************************************************************************************

void fcfs(){
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
}

//********************************************************************************************************
//********************************************************************************************************
//                                ESCALONAMENTO SJF
//*******************************************************************************************************
//********************************************************************************************************

void sjf(){
    int n, bt[20],wt[20],tat[20],avwt=0,avtat=0,i,j;
    int lista_bt_ord[20],aux = 0,k=0,procura_processo=0;
    printf("Entre com o numero de processos (maximum 20):");  //Entrada de numero de processos
    scanf("%d", &n);
    printf("\nEntre com o  Burst Time do processo \n");

    for(i=0;i<n;i++){           //Preenchimento de burst dos processos
        printf("P[%d]:", i+1);
        scanf("%d",&bt[i]); //Burst é gravado em bt[]
    }

    lista_bt_ord[0] = bt[0];  //Insere o primeiro burst na lista ordenada
    for(i=1; i<n; i++){ //Leitura do vetor de burst
        for(j=0; j<=i; j++){ //Leitura de inserção na lista ordenada
            if(bt[i] < lista_bt_ord[j]){ // Verifica o burst for menor que algum que ja estiver na lista ele entra no lugar
                for(k=i; k>j; k--){  //Organiza a lista
                    lista_bt_ord[k] = lista_bt_ord[k-1];
                }
                lista_bt_ord[j] = bt[i];
                break;
            }else if(j==i){
                lista_bt_ord[j] = bt[i]; //Insere no fim do vetor se for o maior
                break;
            }
        } // Close second for
    } //Close first for

    wt[0]=0; //O tempo de espera para o primeiro processo é 0

    for(i=1;i<n;i++){
        wt[i]=0;
        for(j=0;j<i;j++){
            wt[i]+=lista_bt_ord[j];  //Somatório do tempo de Waiting Time
        }
    }



    printf("\nProcess\t\tBurst time\tWaiting Time\tTurnaround Time"); //Cabeçalho

    for(i=0;i<n;i++){
        tat[i]=lista_bt_ord[i]+wt[i]; //TurnAroundTime = BurstTime + WaitingTime
        avwt+=wt[i];  //AverageWaitingTime = AverageWaitingTime + WaitingTime
        avtat+=tat[i]; //AverageTurnAroundTime = AverageTurnAroundTime + TurnAroundTime
        procura_processo = lista_bt_ord[i];
        for(j=0; j<n; j++){   //verifica o processo que contem esse tempo de burst
            if(procura_processo == bt[j]){
                procura_processo = j;
                break;
            }
        }
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d", procura_processo+1,lista_bt_ord[i],wt[i],tat[i]); //Apresetação da linha de dados da tabela
    }

    avwt/=i; //AverageWaitingTime = AverageWaitingTime / numero de processos
    avtat/=i; //AverageTurnAroundTime = AverageTurnAroundTime / numero de processos
    printf("\n\nAverage Waiting Time: %d", avwt);
    printf("\nAverage Turnaround Time: %d\n\n", avtat);
}

//********************************************************************************************************
//********************************************************************************************************
//                                ESCALONAMENTO SRTF
//*******************************************************************************************************
//********************************************************************************************************

void srtf(){
    int n, tat[20],avwt=0,avtat=0,i,j;
    int pronto=0,aux_pronto=0;

    printf("Enter total number od processes (maximum 20):");  //Entrada de numero de processos
    scanf("%d", &n);

    for(i=0;i<n;i++){           //Preenchimento de burst dos processos
        printf("\nEntre com o Burst time do processo\n");
        printf("P[%d]:", i+1);
        processoSRTF[i].name = i+1;
        scanf("%d",&processoSRTF[i].burst); //Burst é gravado
        processoSRTF[i].burstTotal = processoSRTF[i].burst;
        printf("\nEntre com o tempo de chegada do processo");
        scanf("%d",&processoSRTF[i].chegada); //Tempo de entrada dos processos

    }

    for(i=0; i<100; i++){
        aux_pronto = verificaEntradaSRTF(i,n);
        if(aux_pronto > 0){ //Se aux_pronto for maior que 0, algum processo entrou nesse tempo de chegada
            if(pronto!=0 && processoSRTF[aux_pronto-1].burst < processoSRTF[pronto-1].burst){ //Se ja existe um processo sendo executado mas o que esta entrando tem burst menor
                pronto = aux_pronto; //muda o processo que entrou para ser executado
                executarProcessoSRTF(pronto,i,n); //executa processo que entrou
            }else if(pronto!=0 && processoSRTF[aux_pronto-1].burst >= processoSRTF[pronto-1].burst){//Se ja existe um processo sendo executado mas o que entrou tem burst maior ou igual
                if(processoSRTF[pronto-1].burst!=0){ //Verifica se o processo sendo executado ainda tem burst para ser processado
                    executarProcessoSRTF(pronto,i,n);
                }else{
                    pronto = selecionaNovoProcessoSRTF(n);// se acabou o burst do processo, seleciona um novo
                    if(pronto == 0){
                        continue;
                    }else{
                        executarProcessoSRTF(pronto,i,n);
                    }
                }

            }else{
                pronto = aux_pronto;
                executarProcessoSRTF(pronto,i,n);
            }
        }else if(aux_pronto == 0 && pronto != 0){
            if(processoSRTF[pronto-1].burst!=0){ //Verifica se o processo sendo executado ainda tem burst para ser processado
                executarProcessoSRTF(pronto,i,n);
            }else{
                pronto = selecionaNovoProcessoSRTF(n);// se acabou o burst do processo, seleciona um novo
                if(pronto == 0){
                        break;
                }else{
                        executarProcessoSRTF(pronto,i,n);
                }
            }
        }
        if(verificaFimSRTF(n) == 0){
            break;
        }
    }

    printf("\nProcess\t\tTempo de Entrada\tBurst time\tWaiting Time\tTurnaround Time"); //Cabeçalho

    for(i=0;i<n;i++){
        tat[i]=processoSRTF[i].burstTotal+processoSRTF[i].waitingTime; //TurnAroundTime = BurstTime + WaitingTime
        avwt+=processoSRTF[i].waitingTime;  //AverageWaitingTime = AverageWaitingTime + WaitingTime
        avtat+=tat[i]; //AverageTurnAroundTime = AverageTurnAroundTime + TurnAroundTime
        printf("\nP[%d]\t\t%d\t\t\t%d\t\t%d\t\t%d", processoSRTF[i].name,processoSRTF[i].chegada,processoSRTF[i].burstTotal,processoSRTF[i].waitingTime,tat[i]); //Apresetação da linha de dados da tabela
    }

    avwt/=i; //AverageWaitingTime = AverageWaitingTime / numero de processos
    avtat/=i; //AverageTurnAroundTime = AverageTurnAroundTime / numero de processos
    printf("\n\nAverage Waiting Time: %d", avwt);
    printf("\nAverage Turnaround Time: %d", avtat);
}

int verificaFimSRTF(int n){
    int i,cont=0;
    for(i=0; i<n; i++){
        if(processoSRTF[i].burst != 0){
            cont++;
        }
    }
    if(cont>0){
        return 1;
    }else{
        return 0;
    }
}

int selecionaNovoProcessoSRTF(int n){
    int i,j,burst=0,name=0;
    for(i=0; i<n ; i++){
        if(processoSRTF[i].burst != 0 ){//Verifica algum processo com burst para ser processado
            name = processoSRTF[i].name;
            burst = processoSRTF[i].burst;
            for(j=i; j<n; j++){
                if(processoSRTF[j].burst > 0 && processoSRTF[j].burst < burst){
                    name = processoSRTF[j].name;
                    burst = processoSRTF[j].burst;
                }
            }
            return name;
        }
    }
    return burst;
}

void verificaWaitingTimeSRTF(int tempoAtual,int n,int id){
    int i;
    for(i=0; i<n; i++){
        if(i != id-1 && processoSRTF[i].chegada <= tempoAtual && processoSRTF[i].burst!=0){
         //Se o processo tem o tempo de chegada menor que o tempo atual e não esta sendo executado e tem o burst diferente de  0
            processoSRTF[i].waitingTime = processoSRTF[i].waitingTime + 1;
        }
    }
}

void executarProcessoSRTF(int id, int tempo, int n){
    processoSRTF[id-1].burst = processoSRTF[id-1].burst - 1; //Diminui um tempo no burst do processo sendo executado
    verificaWaitingTimeSRTF(tempo, n, id);
}

int verificaEntradaSRTF(int tempo, int n){
    int pronto = 0,i;
    for(i=0; i<n; i++){ //percorre processos
        if(processoSRTF[i].chegada == tempo){ //Verifica se algum processo tem a CHEGADA nesse TEMPO
            pronto = processoSRTF[i].name;
        }
    }
    return pronto;
}

//********************************************************************************************************
//********************************************************************************************************
//                                ESCALONAMENTO ROUND ROBIN
//*******************************************************************************************************
//********************************************************************************************************
void roundrobin(){
    int n, quantum,tat[20],avwt=0,avtat=0,i,j;
    printf("\nEntre com o numero de processos (maximum 20): \n");  //Entrada de numero de processos
    scanf("%d", &n);
    printf("\nDigite o Quantum de tempo da CPU: \n");
    scanf("%d", &quantum);

    for(i=0;i<n;i++){           //Preenchimento de burst dos processos
        printf("\nEntre com o  Burst Time do processo \n");
        printf("P[%d]:", i+1);
        processoRR[i].name = i+1;
        scanf("%d",&processoRR[i].burst); //Burst é gravado na struct do processo
        processoRR[i].waitingTime = 0; //Waiting Time de cada processo se inicia com 0;
        processoRR[i].burstTotal = processoRR[i].burst;
    }

    for(i=0; i<n; i++){  //Enquanto tiver processo para ser processado, ele executara
        if(processoRR[i].burst > 0){
            executaProcessoRR(quantum,n);
            i = 0;
        }
    }


    printf("\nProcess\t\tBurst time\tWaiting Time\tTurnaround Time"); //Cabeçalho

    for(i=0;i<n;i++){
        tat[i]=processoRR[i].burstTotal+processoRR[i].waitingTime; //TurnAroundTime = BurstTime + WaitingTime
        avwt+=processoRR[i].waitingTime;  //AverageWaitingTime = AverageWaitingTime + WaitingTime
        avtat+=tat[i]; //AverageTurnAroundTime = AverageTurnAroundTime + TurnAroundTime

        printf("\nP[%d]\t\t%d\t\t%d\t\t%d", processoRR[i].name,processoRR[i].burstTotal,processoRR[i].waitingTime,tat[i]); //Apresetação da linha de dados da tabela
    }

    avwt/=i; //AverageWaitingTime = AverageWaitingTime / numero de processos
    avtat/=i; //AverageTurnAroundTime = AverageTurnAroundTime / numero de processos
    printf("\n\nAverage Waiting Time: %d", avwt);
    printf("\nAverage Turnaround Time: %d\n\n", avtat);
}

void executaProcessoRR(int quantum, int n){
    int i,j;
    for(i=0; i<n; i++){ //percorre processos
        if(processoRR[i].burst > 0){
            for(j=0; j!=quantum; j++){  //processo sendo executado no tempo do quantum
                if( processoRR[i].burst != 0){
                    processoRR[i].burst -= 1;
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
            if(processoRR[i].burst > 0){
                processoRR[i].waitingTime += 1;  //Conta o tempo de espera do processo
            }
        }
    }
}

//********************************************************************************************************
//********************************************************************************************************
//                                ESCALONAMENTO MULTINIVEL
//*******************************************************************************************************
//********************************************************************************************************

void multinivel(){
    int n, quantum,tat[20],avwt=0,avtat=0,i,j;
    printf("\nEntre com o numero de processos (maximum 20): \n");  //Entrada de numero de processos
    scanf("%d", &n);
    printf("\nDigite o Quantum de tempo da CPU para o Round Robin: \n");
    scanf("%d", &quantum);

    for(i=0;i<n;i++){           //Preenchimento de burst dos processos
        printf("\nEntre com o  Burst Time do processo \n");
        printf("P[%d]:", i+1);
        processoM[i].name = i+1;
        scanf("%d",&processoM[i].burst); //Burst é gravado na struct do processo
        processoM[i].waitingTime = 0; //Waiting Time de cada processo se inicia com 0;
        processoM[i].burstTotal = processoM[i].burst;
        processoM[i].tipoEscalonamento = 0; //Tipo de escalonamento 0 é para round robin e 1 para JSF
    }

    for(i=0; i<n; i++){  //Enquanto tiver processo para ser processado, ele executara
        if(processoM[i].burst > 0){
            if(processoM[i].tipoEscalonamento == 0){ //Primeiro processo de todos é o RoundRobin
                executaProcessoRRM(quantum,n);
            }else if(processoM[i].tipoEscalonamento == 1){ //Os processos que tiverem o burst maior que o quantum, sao terminados no JSF
                executaProcessoJSFM(n);
            }
            i = 0;
        }
    }


    printf("\nProcess\t\tBurst time\tWaiting Time\tTurnaround Time"); //Cabeçalho

    for(i=0;i<n;i++){
        tat[i]=processoM[i].burstTotal+processoM[i].waitingTime; //TurnAroundTime = BurstTime + WaitingTime
        avwt+=processoM[i].waitingTime;  //AverageWaitingTime = AverageWaitingTime + WaitingTime
        avtat+=tat[i]; //AverageTurnAroundTime = AverageTurnAroundTime + TurnAroundTime

        printf("\nP[%d]\t\t%d\t\t%d\t\t%d", processoM[i].name,processoM[i].burstTotal,processoM[i].waitingTime,tat[i]); //Apresetação da linha de dados da tabela
    }

    avwt/=i; //AverageWaitingTime = AverageWaitingTime / numero de processos
    avtat/=i; //AverageTurnAroundTime = AverageTurnAroundTime / numero de processos
    printf("\n\nAverage Waiting Time: %d", avwt);
    printf("\nAverage Turnaround Time: %d\n\n", avtat);
}

void executaProcessoJSFM(int n){
    int lista_JSF[20],lista_JSF_ord[20],i,j,k;
    int insere=0;

    for(i=0; i<n; i++){
        if(processoM[i].burst > 0 && processoM[i].tipoEscalonamento == 1){
            lista_JSF[insere] = processoM[i].burst;
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
            if(processoM[j].burst == lista_JSF_ord[i]){ //Encontra o primeiro processo da lista ordenada
                while(processoM[j].burst > 0){
                    processoM[j].burst -= 1;
                    for(k=0; k<n; k++){
                        if(processoM[k].tipoEscalonamento == 1 && processoM[k].name != processoM[j].name && processoM[k].burst > 0){
                            processoM[k].waitingTime += 1;
                        }
                    }
                }
                break;
            }
        }
    }
}


void executaProcessoRRM(int quantum, int n){
    int i,j;
    for(i=0; i<n; i++){ //percorre processos
        if(processoM[i].burst > 0){
            if(processoM[i].burst > quantum){
                processoM[i].tipoEscalonamento = 1;
            }
            for(j=0; j!=quantum; j++){  //processo sendo executado no tempo do quantum
                if( processoM[i].burst != 0){
                    processoM[i].burst -= 1;
                    contaWaitingTimeRRM(i,n);
                }else{
                    break;
                }
            } //Close second for
        } //Close if
    } //Close first for
}

void contaWaitingTimeRRM(int atual, int n){
    int i, j;
    for(i=0; i<n; i++){ //Percorre lista de processos
        if(i != atual){
            if(processoM[i].tipoEscalonamento == 0 && processoM[i].burst > 0){
                processoM[i].waitingTime += 1;  //Conta o tempo de espera do processo
            }
        }
    }
}
