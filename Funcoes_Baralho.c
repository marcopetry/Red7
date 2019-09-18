#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "Tipos_Dados.h"
#include "Funcoes_Baralho.h"
#include "Mesa_Jogadores.h"
#include "Funcoes_Impressao.h"
#include "Funcoes_Jogo.h"
#include "Alocar.h"
#include "Simbolos.h"

Carta* iniciar_cartas(){
    Carta* pont_carta = (Carta*) malloc(49*sizeof(Carta));
    int i=0, j, k;

    while(i<49){
        for(j=0; j<7; j++){
            for(k=0; k<7; k++){
                pont_carta[i].id_cor = j+1;
                if(j==0){
                    pont_carta[i].cor_imprimir = 5;
                    strcpy(pont_carta[i].cor, "Violeta.   ");
                    strcpy(pont_carta[i].regra, "Mais números abaixo de quatro vence.");
                }
                else if(j==1){
                    pont_carta[i].cor_imprimir = FOREGROUND_INTENSITY + 5;
                    strcpy(pont_carta[i].cor, "Anil.      ");
                    strcpy(pont_carta[i].regra, "Mais números em sequencia vence.");
                }
                else if(j==2){
                    pont_carta[i].cor_imprimir = 9;
                    strcpy(pont_carta[i].cor, "Azul.      ");
                    strcpy(pont_carta[i].regra, "Mais cores diferentes vencem.");
                }
                else if(j==3){
                    pont_carta[i].cor_imprimir = FOREGROUND_GREEN;
                    strcpy(pont_carta[i].cor, "Verde.     ");
                    strcpy(pont_carta[i].regra, "Mais números pares vencem.");
                }
                else if(j==4){
                    pont_carta[i].cor_imprimir = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
                    strcpy(pont_carta[i].cor, "Amarelo.   ");
                    strcpy(pont_carta[i].regra, "Mais de uma mesma cor vence.");
                }
                else if(j==5){
                    pont_carta[i].cor_imprimir = 4;
                    strcpy(pont_carta[i].cor, "Laranja.   ");
                    strcpy(pont_carta[i].regra, "Mais do mesmo número vence.");
                }
                else{
                    pont_carta[i].cor_imprimir = FOREGROUND_INTENSITY | FOREGROUND_RED;
                    strcpy(pont_carta[i].cor, "Vermelho.  ");
                    strcpy(pont_carta[i].regra, "Carta mais alta vence.");
                }
                pont_carta[i].numero_carta = k+1;
                i++;
            }
        }
    }
    return pont_carta;
}

Baralho* colocar_cartas_baralho(Carta* pont_carta){
    Baralho *pont_baralho;
    int i=0;

    do{
       pont_baralho = (Baralho*) malloc(sizeof(Baralho));
    }while(pont_baralho==NULL);

    while(i<49){
        pont_baralho->pilha_cartas[i] = pont_carta[i];
        pont_baralho->topo=i+1;
        i++;
    }
    return pont_baralho;
}

void embaralhar_cartas(Baralho* pont_baralho){
    Baralho* auxiliar = (Baralho*) malloc(sizeof(Baralho));
    int i, repetido, k;

    srand((unsigned) time(NULL));
    auxiliar->pilha_cartas[0] = pont_baralho->pilha_cartas[rand()%49];
    for(i=1; i<49; i++){
        do{
                repetido = 0;
                auxiliar->pilha_cartas[i] = pont_baralho->pilha_cartas[rand()%49];
                for(k = i-1; k>= 0; k--){
                    if(auxiliar->pilha_cartas[i].id_cor == auxiliar->pilha_cartas[k].id_cor &&
                       auxiliar->pilha_cartas[i].numero_carta == auxiliar->pilha_cartas[k].numero_carta){
                            repetido++;
                            break;
                    }
                }
            } while(repetido);
    }
    for(i=0; i<49; i++)
        pont_baralho->pilha_cartas[i] = auxiliar->pilha_cartas[i];
    //*pont_baralho = *auxiliar;
    free(auxiliar);
}

Carta pegar_carta(Baralho* pont_baralho){
    pont_baralho->topo--;
    return pont_baralho->pilha_cartas[pont_baralho->topo];
}

Baralho *iniciar_baralho_jogo(){
    Carta *cartas_iniciais = iniciar_cartas();
    Baralho* baralho_jogar = colocar_cartas_baralho(cartas_iniciais);
    embaralhar_cartas(baralho_jogar);

    return baralho_jogar;
}

void empilhar_carta_baralho(Baralho *pont_baralho, Carta carta_empilhar){
    pont_baralho->pilha_cartas[pont_baralho->topo] = carta_empilhar;
    pont_baralho->topo++;
}
