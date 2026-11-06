#include <stdio.h>
#include <stdlib.h>
#include "headerBrasileirao.h"
#include <math.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    guardarDistancias("C:\\Users\\Yuri\\Desktop\\Metodos\\Projects\\TrabalhoOptBrasileirao\\matDist.csv");

    brasileirao brasileirao2026;

    gerarAleatoria(&brasileirao2026);
    gerarSolJogos(&brasileirao2026);

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
    for(int coluna = 0; coluna < 19  ; coluna++) {
            int vetAuxTimes[20];
            for(int i=0; i<20; i++){
                vetAuxTimes[i]=i;
            }
        for(int linha = 0; linha < 20; linha++) {
            int num;
            do{
                num = rand() % 20;
            }while(vetAuxTimes[num] == -1);

            brStruct->matJogos[linha][coluna]=num;
            brStruct->matJogos[linha][coluna+19]=num;
            vetAuxTimes[num] = -1;
        }
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

void gerarSolJogos(brasileirao *brStruct){
    printf("Time |");
    for(int j = 0; j < NUM_JOGOS; j++) {
        printf(" R%02d", j + 1);
    }
    printf("\n-----+");
    for (int j = 0; j < NUM_JOGOS; j++) {
        printf("----");
    }
    printf("\n");

    for(int i = 0; i < NUM_TIMES; i++) {
        printf(" %2d  |", i);
        for(int j = 0; j < NUM_JOGOS; j++) {
            printf(" %3d", brStruct->matJogos[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
