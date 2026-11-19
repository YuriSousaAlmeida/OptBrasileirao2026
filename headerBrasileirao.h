#ifndef HEADERBRASILEIRAO_H_INCLUDED
#define HEADERBRASILEIRAO_H_INCLUDED

#define NUM_TIMES 20
#define NUM_RODADAS 38

float matrizDistancia[NUM_TIMES][NUM_TIMES];

typedef struct{
    int matJogos[NUM_TIMES][NUM_RODADAS];
    int confrontos[NUM_TIMES][NUM_TIMES];
    int locAtual[NUM_TIMES];
} brasileirao;

////////////////

void guardarDistancias(char *arq);
void imprimirMatJogos(brasileirao *brStruct);
void imprimirMatConfrontos(brasileirao *brStruct);
void gerarAleatoria(brasileirao *brStruct);
void calcularFo(brasileirao *brStruct);

#endif
