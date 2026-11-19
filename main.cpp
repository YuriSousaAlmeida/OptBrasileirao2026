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
    int tentativas=0;
    int contadorGeral=0;
    int num;
    memset(vetSolucaoTemp, -1, sizeof(vetSolucaoTemp));
    memset(brStruct->confrontos, 0, sizeof(brStruct->confrontos));

    for(int i=0; i<NUM_TIMES; i++){
        vetBase[i]=i;
    }

    for(int coluna = 0; coluna < (NUM_RODADAS/2)  ; coluna++) {
        contadorGeral=0;
        inicio:
        memcpy(vetAuxTimes, vetBase, sizeof(vetBase));
        memset(vetSolucaoTemp, -1, sizeof(vetSolucaoTemp));
        tentativas=0;

        for(int linha = 0; linha < NUM_TIMES; linha++) {
            tentativas=0;

            volta:
            num = rand() % NUM_TIMES;
            tentativas++;
            contadorGeral++;
            if(contadorGeral>100000){ // OBS: Zerar matriz e reformular goto
                goto reinicio;
            }
            if(tentativas>1000){
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
            brStruct->matJogos[linha][coluna+(NUM_RODADAS/2)]=vetSolucaoTemp[linha];  // Espelhamento na matriz de jogos (desordenado)
            if((linha%2)!=0){
                brStruct->confrontos[brStruct->matJogos[linha][coluna]][brStruct->matJogos[linha-1][coluna]]++;
                brStruct->confrontos[brStruct->matJogos[linha-1][coluna]][brStruct->matJogos[linha][coluna]]++;
            }
        }

        printf("Fim da rodada: %d\n", coluna);
    }

    for(int coluna = NUM_RODADAS/2; coluna < NUM_RODADAS  ; coluna++){  // Espelho do returno
        for(int linha = 0; linha < NUM_TIMES; linha+=2){
            int numAux=brStruct->matJogos[linha+1][coluna];
            brStruct->matJogos[linha+1][coluna]=brStruct->matJogos[linha][coluna];
            brStruct->matJogos[linha][coluna]= numAux;
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

void calcularFo(brasileirao *brStruct){

}
