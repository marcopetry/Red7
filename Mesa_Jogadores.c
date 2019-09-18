#include <stdio.h>
#include <stdlib.h>
#include "Tipos_Dados.h"
#include "Funcoes_Baralho.h"
#include "Mesa_Jogadores.h"
#include "Alocar.h"

void inserir_jogador_mesa(Mesa_Jogadores *pont_mesa, Descritor_Jogo *pont_descritor, Baralho *pont_baralho){
    Jogador *novo_jogador;
    novo_jogador = criar_jogador(pont_baralho);
    Mesa_Jogadores *novo_membro;

    if(pont_descritor->qtd_jogador == 0){
        pont_mesa->dados_jogador = novo_jogador;
        pont_mesa->proximo_jogador = NULL;
        pont_descritor->primeiro_jogar = pont_mesa;
        pont_descritor->ultimo_jogar = pont_mesa;
    }
    else{
        novo_membro = alocar_mesa();
        novo_membro->dados_jogador = novo_jogador;
        novo_membro->proximo_jogador = pont_descritor->primeiro_jogar;
        pont_mesa = pont_descritor->ultimo_jogar;
        pont_mesa->proximo_jogador = novo_membro;
        pont_descritor->ultimo_jogar = novo_membro;
    }
    pont_descritor->qtd_jogador++;
}

void definir_primeiro_jogador_jogar(Mesa_Jogadores *pont_mesa, Descritor_Jogo *pont_descritor){
    pont_mesa = pont_descritor->primeiro_jogar;
    pont_mesa = pont_mesa->proximo_jogador;
    while(pont_mesa != pont_descritor->primeiro_jogar){
        if((pont_descritor->primeiro_jogar->dados_jogador->pontuacao_na_regra < pont_mesa->dados_jogador->pontuacao_na_regra) ||
           (pont_descritor->primeiro_jogar->dados_jogador->pontuacao_na_regra == pont_mesa->dados_jogador->pontuacao_na_regra &&
            pont_descritor->primeiro_jogar->dados_jogador->paleta->dados_carta.id_cor < pont_mesa->dados_jogador->paleta->dados_carta.id_cor)){
                pont_descritor->primeiro_jogar = pont_mesa;
        }
        pont_mesa = pont_mesa->proximo_jogador;
    }
    pont_descritor->ultimo_jogar = pont_descritor->primeiro_jogar;
    pont_descritor->primeiro_jogar = pont_descritor->ultimo_jogar->proximo_jogador;
    pont_descritor->jogador_atual = pont_descritor->primeiro_jogar;
}

Jogador* criar_jogador(Baralho* pont_baralho){
    Jogador *participante = aloca_jogador();
    Seq_cartas* mao_participante = aloca_sequencia_cartas();
    Seq_cartas* paleta_jogador = aloca_sequencia_cartas();
    int qtd_cartas=0;

    printf("Digite o nome do jogador: \n");
    scanf(" %[^\n]s", participante->nome);
    while(qtd_cartas < 7){
        adicionar_carta_sequencia(&mao_participante, pegar_carta(pont_baralho));
        qtd_cartas++;
    }

    adicionar_carta_sequencia(&paleta_jogador, pegar_carta(pont_baralho));
    participante->mao = mao_participante;
    participante->paleta = paleta_jogador;
    participante->pontuacao_na_regra = participante->paleta->dados_carta.numero_carta;
    participante->carta_mais_alta_na_regra = paleta_jogador->dados_carta;
    participante->jogada = 5; //Pro jogador não ficar sem jogar no início

    return participante;
}

Jogador* retornar_jogador_escolhido(Mesa_Jogadores *pont_mesa, int numero_jogador){
    int contador = 1;
    Mesa_Jogadores *atual = pont_mesa;
    pont_mesa = pont_mesa->proximo_jogador;
    Jogador *retornar;

    while(contador < numero_jogador){
        pont_mesa = pont_mesa->proximo_jogador;
        contador++;
    }
    retornar = pont_mesa->dados_jogador;
    pont_mesa = atual;
    return retornar;
}
