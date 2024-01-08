#include<stdio.h>
#include<stdlib.h>
#include"TorreDeHanoi.h"

Pino* criarPino(){
    //Alocação dinâmica do pino.
    Pino *pin = (Pino *) malloc(sizeof(Pino));
    //Ponteiro que não aponta para nada.
    pin->topo = NULL;
    //O pino começa sem disco algum, então 0.
    pin->numDiscos = 0;
    return pin;
}

Disco* criarDisco(int tam){
    //Alocação dinâmica do disco.
    Disco *disc = (Disco *) malloc(sizeof(Disco));
    //Definido o tamanho desse disco.
    disc->tamDisco = tam;
    //Ponteiro que não aponta para nada.
    disc->next = NULL;
    return disc;
}

Disco* pop(Pino *pino){
    //Ponteiro para começar a percorrer os discos.
    Disco *disc = pino->topo;
    //Se não for nulo.
    if(disc){
        //Agora o ponteiro do pino aponta para o próximo disco.
        pino->topo = disc->next;
        //Para o disco removido, agora ele não aponta para nada.
        disc->next = NULL;
        //Atualiza o índice
        --pino->numDiscos;
    }
    //Retorna o endereço do disco removido.
    return disc;
}

void push(Pino *pino, Disco *disco){
    //O ponteiro do disco inserido aponta para o próximo, que era o primeiro.
    disco->next = pino->topo;
    //O ponteiro do pino agora aponta para novo esse disco.
    pino->topo = disco;
    //Atualiza o índice desse pino.
    ++pino->numDiscos;
}

void excluirPino(Pino *pino){
    //Ponteiro para começar a percorrer os discos.
    Disco *disco = pino->topo;
    //Se existirem discos nesse pino, todos serão liberados da memória
    while(disco != NULL){
        Disco* discoTemp = disco->next;
        free(disco);
        disco = discoTemp;
    }
    //E no final, o pino é liberado.
    free(pino);
}