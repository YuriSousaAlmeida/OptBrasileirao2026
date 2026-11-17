#include <stdio.h>
#include <stdlib.h>
#include "headerBrasileirao.h"
#include <math.h>
#include <time.h>
#include <string.h>

int main()
{
    srand(time(NULL));

    guardarDistancias("C:\\Users\\Yuri\\Desktop\\Metodos\\Projects\\TrabalhoOptBrasileirao\\matDist.csv");

    brasileirao brasileirao2026;
    memset(brasileirao2026.confrontos, 0, sizeof(brasileirao2026.confrontos));

    gerarAleatoria(&brasileirao2026);
    imprimirMatConfrontos(&brasileirao2026);
    printf("");
    printf("");
    imprimirMatJogos(&brasileirao2026);

    return 0;
}

void guardarDistancias(char *arq){
    FILE *arquivo = fopen(arq, "r");
    if(arquivo==NULL){
        printf("Arquivo de distâncias do csv não foi encontrado!\n");
        exit(1);
    }

    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            if (fscanf(arquivo, "%f,", &matrizDistancia[i][j]) != 1) {
                break;
            }
        }
    }

    fclose(arquivo);

    /*printf("Matriz do csv em memória\n");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            printf("%8.2f ", matrizDistancia[i][j]);
        }
        printf("\n");
    }*/
}

void gerarAleatoria(brasileirao *brStruct){
    int vetBase[NUM_TIMES]={0};
    int vetAuxTimes[NUM_TIMES]={0};
    int vetSolucaoTemp[NUM_TIMES]={-1};
    for(int i=0; i<20; i++){
        vetBase[i]=i;
    }

    for(int coluna = 0; coluna < (NUM_RODADAS/2)  ; coluna++) {
        inicio:
        memcpy(vetAuxTimes, vetBase, sizeof(vetBase));

        for(int linha = 0; linha < 20; linha++) {
            int num;
            int tentativas=0;
            memset(vetSolucaoTemp, -1, NUM_TIMES*sizeof(int));

            volta:
            num = rand() % 20;
            tentativas++;
            if(tentativas>100){
                goto inicio;
            }
                if(vetAuxTimes[num] == -1){
                    goto volta;
                }
                if(((linha%2)!=0)){ // Mudar para ter todos os confrontos batendo == 1 (vet auxiliar, mesmo que o gasto seja grande)
                if((brStruct->confrontos[brStruct->matJogos[linha-1][coluna]][num])!=0){
                    goto volta;
                 }
                }

                vetSolucaoTemp[linha]=num;
                brStruct->matJogos[linha][coluna]=num;
                brStruct->matJogos[linha][coluna+19]=num;
                vetAuxTimes[num] = -1;


        }

        for(int linha = 0; linha < 20; linha++){
            if((linha%2)!=0){
                brStruct->confrontos[brStruct->matJogos[linha][coluna]][brStruct->matJogos[linha-1][coluna]]++; // Passível de otimização
                brStruct->confrontos[brStruct->matJogos[linha-1][coluna]][brStruct->matJogos[linha][coluna]]++; // Passível de otimização
            }
        }

        printf("Fim da rodada: %d\n", coluna);
    }

    for(int coluna = 19; coluna < 38  ; coluna++){
        for(int linha = 0; linha < 20; linha++){
            int numAux=brStruct->matJogos[linha+1][coluna];
            brStruct->matJogos[linha+1][coluna]=brStruct->matJogos[linha][coluna];
            brStruct->matJogos[linha][coluna]= numAux;
            linha++;
        }
    }

}

void imprimirMatJogos(brasileirao *brStruct){
    printf(" Pos  |");
    for(int j = 0; j < NUM_RODADAS; j++) {
        printf(" R%02d", j + 1);
    }
    printf("\n------");
    for (int j = 0; j < NUM_RODADAS; j++) {
        printf("----");
    }
    printf("\n");

    for(int i = 0; i < NUM_TIMES; i++) {
        printf(" %2d  |", i);
        for(int j = 0; j < NUM_RODADAS; j++) {
            printf(" %3d", brStruct->matJogos[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void imprimirMatConfrontos(brasileirao *brStruct){
    printf("Times |");
    for(int j = 0; j < NUM_TIMES; j++) {
        printf("  %02d", j);
    }
    printf("\n------");
    for (int j = 0; j < NUM_TIMES; j++) {
        printf("----");
    }
    printf("\n");

    for(int i = 0; i < NUM_TIMES; i++) {
        printf(" %2d  |", i);
        for(int j = 0; j < NUM_TIMES; j++) {
            printf(" %3d", brStruct->confrontos[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
