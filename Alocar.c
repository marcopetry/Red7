#include <stdio.h>
#include <stdlib.h>
#include "Tipos_Dados.h"
#include "Funcoes_Baralho.h"
#include "Mesa_Jogadores.h"
#include "Funcoes_Impressao.h"
#include "Funcoes_Jogo.h"
#include "Alocar.h"
#include "Simbolos.h"

Seq_cartas* aloca_sequencia_cartas(){
    Seq_cartas* lista;
    do{
        lista = (Seq_cartas*) malloc(sizeof(Seq_cartas));
    }while(lista == NULL);
    lista->qtd_cartas = 0;

    return lista;
}

void adicionar_carta_sequencia(Seq_cartas** pont_seq, Carta carta_retirada){
    Seq_cartas* mais_carta, *inicio= (*pont_seq);

    do{
        mais_carta = (Seq_cartas*) malloc(sizeof(Seq_cartas));
    }while(mais_carta == NULL);

    mais_carta->dados_carta = carta_retirada;

    if((*pont_seq)->qtd_cartas == 0){
        (*pont_seq)->dados_carta = carta_retirada;
        (*pont_seq)->proxima = NULL;
    }
    else{
        Seq_cartas *anterior = *pont_seq, *atual = *pont_seq;
        while((atual != NULL && atual->dados_carta.numero_carta < carta_retirada.numero_carta) ||
              (atual != NULL && atual->dados_carta.numero_carta == carta_retirada.numero_carta &&
               atual->dados_carta.id_cor < carta_retirada.id_cor)){
            anterior = atual;
            atual = atual->proxima;
        }
        if(atual == *pont_seq){
            mais_carta->qtd_cartas = (*pont_seq)->qtd_cartas;
            mais_carta->proxima = *pont_seq;
            *pont_seq = mais_carta;
        } else{
            anterior->proxima = mais_carta;
            mais_carta->proxima = atual;
            (*pont_seq) = inicio; //inclui essa linha
        }
    }
    (*pont_seq)->qtd_cartas++;
}

Jogador* aloca_jogador(){
    Jogador *ponteiro;

    do{
        ponteiro = (Jogador*) malloc(sizeof(Jogador));
    } while(ponteiro == NULL);

    return ponteiro;
}

void desalocar_carta(Seq_cartas **pont_seq, Carta descartar){
    int qtd_cartas = (*pont_seq)->qtd_cartas;
    Seq_cartas *anterior = *pont_seq, *atual = *pont_seq, *inicio = *pont_seq;

    while(atual->dados_carta.numero_carta != descartar.numero_carta ||
          atual->dados_carta.id_cor != descartar.id_cor){
        anterior = atual;
        atual = atual->proxima;
    }
    if(atual == *pont_seq){
        *pont_seq = (*pont_seq)->proxima;
        free(atual);
    }
    else{
        anterior->proxima = atual->proxima;
        free(atual);
        (*pont_seq) = inicio; //inclui essa linha
    }
    if(qtd_cartas > 1){
        (*pont_seq)->qtd_cartas = qtd_cartas-1;
    }
    else{
        (*pont_seq) = aloca_sequencia_cartas();
        (*pont_seq)->dados_carta = zerar_carta();
    }
}

Descritor_Jogo* alocar_descritivo(){
    Descritor_Jogo *pont_descritivo;

    do{
        pont_descritivo = (Descritor_Jogo*) malloc(sizeof(Descritor_Jogo));
    }while(pont_descritivo == NULL);

    pont_descritivo->qtd_jogador = 0;

    return pont_descritivo;
}

Mesa_Jogadores* alocar_mesa(){
    Mesa_Jogadores *pont_mesa;

    do{
        pont_mesa = (Mesa_Jogadores*) malloc(sizeof(Mesa_Jogadores));
    }while(pont_mesa == NULL);

    return pont_mesa;
}
