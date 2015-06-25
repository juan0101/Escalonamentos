#include <stdio.h>

int main(){
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
    return 0;
}
