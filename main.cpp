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
    reinicio:
    int vetBase[NUM_TIMES]={0};
    int vetAuxTimes[NUM_TIMES]={0};
    int vetSolucaoTemp[NUM_TIMES];
    memset(vetSolucaoTemp, -1, sizeof(vetSolucaoTemp));
    int tentativas=0;
    int contadorGeral=0; // Falta resolver problema de algumas rodadas falharem (loop por confrontos)
    int num;

    for(int i=0; i<20; i++){
        vetBase[i]=i;
    }

    for(int coluna = 0; coluna < (NUM_RODADAS/2)  ; coluna++) {
        inicio:
        memcpy(vetAuxTimes, vetBase, sizeof(vetBase));
        memset(vetSolucaoTemp, -1, sizeof(vetSolucaoTemp));
        tentativas=0;

        for(int linha = 0; linha < NUM_TIMES; linha++) {
            tentativas=0;

            volta:
            num = rand() % 20;
            tentativas++;
            if(tentativas>100){
                goto inicio;
            }
            if(vetAuxTimes[num] == -1){ // Se ja foi sorteado
                goto volta;
            }
            if(((linha%2)!=0)){ // Linhas pares
            if((brStruct->confrontos[vetSolucaoTemp[linha-1]][num])!=0){
                goto volta;
            }
            }

            vetSolucaoTemp[linha]=num;
            vetAuxTimes[num] = -1; // Tira a possibilidade de sortear novamente


        }

        for(int linha = 0; linha < NUM_TIMES; linha++){
            brStruct->matJogos[linha][coluna]=vetSolucaoTemp[linha];     // Set solucao na matriz de jogos
            brStruct->matJogos[linha][coluna+19]=vetSolucaoTemp[linha];  // Espelhamento na matriz de jogos (desordenado)
            if((linha%2)!=0){
                brStruct->confrontos[brStruct->matJogos[linha][coluna]][brStruct->matJogos[linha-1][coluna]]++;
                brStruct->confrontos[brStruct->matJogos[linha-1][coluna]][brStruct->matJogos[linha][coluna]]++;
            }
        }

        printf("Fim da rodada: %d\n", coluna);
    }

    for(int coluna = 19; coluna < 38  ; coluna++){  // Espelho do returno
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
