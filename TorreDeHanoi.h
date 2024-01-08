#include<stdio.h>
#include<stdlib.h>

typedef struct disco{
    struct disco *next; //Ponteiro para o próximo disco
    char tamDisco; //Tamanho do disco
} Disco;

typedef struct pino{
    struct disco *topo; //Ponteiro para o topo da pilha 
    char numDiscos; //Quantidade de discos
} Pino;

Pino* criarPino(); //Cria um pino, que contém o número de discos e um ponteiro para o primeiro disco.

Disco* criarDisco(int tam); //Cria um disco, que contem o tamanho do disco e um ponteiro para o proximo.

Disco* pop(Pino *pino); //Retira um disco, se existir, do pino e retorna seu endereço, e atualiza o índice de discos do dito pino.

void push(Pino *pino, Disco *disco); //Recebe um pino e um disco como parâmetro, e empilha ele no dito pino.

void excluirPino(Pino *pino); //Desaloca todos os discos presentes no pino, se existirem, e depois desaloca o pino.