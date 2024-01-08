#include<stdio.h>
#include<stdlib.h>
#include"TorreDeHanoi.h"

//Variavel global pois o prototipo nao me deixa colocar esse parametro na funcao de mover
int maxPinos;

void jogar();
Pino **criarPinos(int n);
int moverDisco(Pino **pinos, int pinoOrigem, int pinoDestino);
void imprimir(Pino **pinos, int numPinos, int numDiscos);
int verificarVitoria(Pino **pinos, int qtdPinos, int qtdDiscos);
void imprimirPinoCompletoVazio(int numDiscos);
void imprimirPinoParteVazio(int numDiscos);
void imprimirBaseDoPino(int numDiscos);
void imprimirDisco(int numDiscos, char tamDisco);
int charParaInt(char c);

int main(){
    jogar();
    return 0;
}

void jogar(){
    int origem, destino, cont;
    int jogadas = 0;
    int qtdPinos = 0;
    int qtdDiscos = 0;
    int vitoria = 0;
    //Pegar a quantidade de pinos
    while(!qtdPinos){
        printf("Insira a quantidade de pinos: [3..5]\n");
        scanf("%d", &qtdPinos);
        if(qtdPinos <= 5 && qtdPinos >= 3){
            break;
        }
        qtdPinos = 0;
        printf("Entrada invalida.\n");
    }
    maxPinos = qtdPinos;
    //Pegar a quantidade de discos
    while(!qtdDiscos){
        printf("Insira a quantidade de discos: [3..5]\n");
        scanf("%d", &qtdDiscos);
        if(qtdDiscos <= 5 && qtdDiscos >= 3){
            break;
        }
        qtdDiscos = 0;
        printf("Entrada invalida.\n");
    }
    //Vetor de pinos
    Pino **pinos = criarPinos(qtdPinos);
    //Coloca os discos no primeiro pino
    for(cont = qtdDiscos; cont > 0; cont--){
        push(pinos[0], criarDisco(cont));
    }
    while(!vitoria){
        //Impressao da situacao atual do jogo
        imprimir(pinos, qtdPinos, qtdDiscos);
        printf("Insira os pinos de origem e de destino: \n");
        scanf("%d %d", &origem, &destino);
        //Se o movimento for invalido, nao conta nas jogadas
        if(!moverDisco(pinos, origem, destino)){
            printf("Movimento invalido.\n\n");
            jogadas--;
        }
        //Verifica se ganhou
        if(verificarVitoria(pinos, qtdPinos, qtdDiscos)){
            vitoria = 1;
        }
        //Contador de jogadas
        jogadas++;

    }
    //Impressao final
    imprimir(pinos, qtdPinos, qtdDiscos);
    printf("PARABENS VOCE CONSEGUIU\n");
    printf("TOTAL DE JOGADAS: %d\n", jogadas);
    //Desalocar todos os pinos e discos
    for(cont = 0; cont < qtdPinos; cont++){
        excluirPino(pinos[cont]);
    }
}

Pino **criarPinos(int n){
    int cont;
    Pino **vetorPinos = malloc(n * sizeof(Pino *)); //Alocacao dinamica do vetor de pinos
    for(cont = 0; cont < n; cont++){ //For para criar n quantidade de pinos e inserior no vetor
        vetorPinos[cont] = criarPino();
    }
    return vetorPinos;

}

int moverDisco(Pino **pinos, int pinoOrigem, int pinoDestino){
    if(pinoOrigem <= 0 || pinoOrigem > maxPinos || pinoDestino <= 0 || pinoDestino > maxPinos){
        return 0;
    }
    //Se nao tiver nenhum disco no pino de origem, nao e possivel
    if(pinos[pinoOrigem - 1]->topo == NULL){
        return 0;
    }
    //Se nao tiver nenhum disco no pino de destino, a movimentacao e valida
    else if(pinos[pinoDestino - 1]->topo == NULL){
        push(pinos[pinoDestino - 1], pop(pinos[pinoOrigem - 1]));
        return 1;
    }
    //Se o disco presente no pino de destino for menor do que o de origem, nao e possivel
    else if(pinos[pinoOrigem - 1]->topo->tamDisco > pinos[pinoDestino - 1]->topo->tamDisco){
        return 0;
    }
    //Se passou por todas as verificacoes, o movimento e padrao
    else{
        push(pinos[pinoDestino - 1], pop(pinos[pinoOrigem - 1]));
        return 1;
    }
}

void imprimir(Pino **pinos, int numPinos, int numDiscos){
    Disco *ptr;
    int cont, contAux, qtdPinos;
    //For para a quantidade de pinos
    for(cont = 0; cont < numPinos; cont++){
        //Se pino vazio
        if(pinos[cont]->numDiscos == 0){
           //Imprimir as partes do pino vazio
           imprimirPinoCompletoVazio(numDiscos);
        }
        //Senão, pino com discos
        else if(pinos[cont]->numDiscos != 0){
            //Partes do pino sem disco
            for(contAux = 0; contAux < (numDiscos - pinos[cont]->numDiscos); contAux++){
                 imprimirPinoParteVazio(numDiscos);
            }
            //Partes com disco
            for(ptr = pinos[cont]->topo; ptr != NULL; ptr = ptr->next){
                imprimirDisco(numDiscos, ptr->tamDisco);
            }
        }
        //Imprimir a base do pino
        imprimirBaseDoPino(numDiscos);
        //Indice do pino
        printf("\n");
        for(contAux = 0; contAux < numDiscos + 1; contAux++){
            printf(" ");
        }
        printf("%d\n", cont + 1);
        printf("\n");
    }

}

int verificarVitoria(Pino **pinos, int qtdPinos, int qtdDiscos){
    int cont;
    int vitoria = 0;
    Disco *ptr;
    //Todos os pinos menos o primeiro
    for(cont = 1; cont < qtdPinos; cont++){
        //Faz uma contagem dos discos
        for(ptr = pinos[cont]->topo; ptr != NULL; ptr = ptr->next){
           vitoria++;
        }
        //Se a vitoria nao tiver sido alcançada, recomeça
        if(vitoria != qtdDiscos){
            vitoria = 0;
        }
    }
    //Se algum pino tiver a quantidade de discos necessaria, vitoria
    if(vitoria == qtdDiscos){
        return 1;
    }
    //Senao, sem vitoria
    else{
        return 0;
    }
}

void imprimirPinoCompletoVazio(int numDiscos){
    //Imprime um pino completio sem a base, baseado no tamanho do pino
    switch(numDiscos){
        case 3:
           printf("    |\n    |\n    |\n");
           break;
        case 4:
           printf("     |\n     |\n     |\n     |\n");
           break;
        case 5:
           printf("      |\n      |\n      |\n      |\n      |\n");
           break;
    }
}

void imprimirPinoParteVazio(int numDiscos){
    //Imprime um pedaco, usado quando o pino tem discos
    switch(numDiscos){
        case 3:
           printf("    |\n");
           break;
        case 4:
           printf("     |\n");
           break;
        case 5:
           printf("      |\n");
           break;
    }
}

void imprimirBaseDoPino(int numDiscos){
    //A base do pino, baseado no tamanho do pino
    switch(numDiscos){
        case 3:
           printf("____|____\n");
           break;
        case 4:
           printf("_____|_____\n");
           break;
        case 5:
           printf("______|______\n");
           break;
    }
}

void imprimirDisco(int numDiscos, char tamDisco){
    //Imprime um disco, baseado no tamanho do pino e no tamanho do disco
    switch(numDiscos){
        case 3:
           switch(tamDisco){
              case 1:
                 printf("   _|_\n");
                 break;
              case 2:
                 printf("  __|__\n");
                 break;
              case 3:
                 printf(" ___|___\n");
                 break;
            
            }
            break;
        case 4:
           switch(tamDisco){
               case 1:
                 printf("    _|_\n");
                 break;
               case 2:
                 printf("   __|__\n");
                 break;
               case 3:
                 printf("  ___|___\n");
                 break;
               case 4:
                 printf(" ____|____\n");
                 break;
            }
            break;
        case 5:
           switch(tamDisco){
               case 1:
                 printf("     _|_\n");
                 break;
               case 2:
                 printf("    __|__\n");
                 break;
               case 3:
                 printf("   ___|___\n");
                 break;
               case 4:
                 printf("  ____|____\n");
                 break;
               case 5:
                 printf(" _____|_____\n");
                 break;
           }
           break;
    }
}

int charParaInt(char c){
   return c - '0';
}