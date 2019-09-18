#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tipos_Dados.h"
#include "Funcoes_Baralho.h"
#include "Mesa_Jogadores.h"
#include "Funcoes_Impressao.h"
#include "Funcoes_Jogo.h"
#include "Alocar.h"
#include "Simbolos.h"

Carta escolher_carta(Seq_cartas **pont_seq){
    int carta_escolhida, contador=1;
    Carta retornar;
    Seq_cartas *inicio = (*pont_seq);

    do{
        limpa_buffer();
        printf("Qual carta vai escolher? \n");
        scanf("%d", &carta_escolhida);
        if(carta_escolhida < 1 || carta_escolhida > (*pont_seq)->qtd_cartas)
            printf("Carta inválida.\n");
    }while(carta_escolhida < 1 || carta_escolhida > (*pont_seq)->qtd_cartas);

    while(contador < carta_escolhida){
        (*pont_seq) = (*pont_seq)->proxima;
        contador++;
    }
    retornar = (*pont_seq)->dados_carta;
    (*pont_seq) = inicio;

    return retornar;
}

void avaliar_todos_jogadores_regra(Mesa_Jogadores *pont_mesa, regra avaliacao, Jogador **vencedor){
    Mesa_Jogadores *inicio = pont_mesa;

    avaliacao(pont_mesa->dados_jogador);
    pont_mesa = pont_mesa->proximo_jogador;
    while(pont_mesa != inicio){
        avaliacao(pont_mesa->dados_jogador);
        pont_mesa = pont_mesa->proximo_jogador;
    }
    pont_mesa = inicio;
    definir_vencedor(pont_mesa, &(*vencedor));
}

void definir_vencedor(Mesa_Jogadores *pont_mesa, Jogador **vencedor){
    Mesa_Jogadores *inicio = pont_mesa;

    comparar_paletas_jogadores(&pont_mesa->dados_jogador, &(*vencedor));
    pont_mesa = pont_mesa->proximo_jogador;
    while(pont_mesa != inicio){
        comparar_paletas_jogadores(&pont_mesa->dados_jogador, &(*vencedor));
        pont_mesa = pont_mesa->proximo_jogador;
    }
    pont_mesa = inicio;
}

void avaliar_carta_mais_alta_paleta(Jogador *jogador_atual){
    Seq_cartas *inicio = jogador_atual->paleta;

    while(jogador_atual->paleta->proxima != NULL)
        jogador_atual->paleta = jogador_atual->paleta->proxima;
    jogador_atual->pontuacao_na_regra = jogador_atual->paleta->dados_carta.numero_carta;
    jogador_atual->carta_mais_alta_na_regra = jogador_atual->paleta->dados_carta;
    jogador_atual->paleta = inicio;
}

void avaliar_mais_mesmo_numero(Jogador *jogador_atual){
    int contador_cartas=0, maximo_cartas=0, numero_carta=1;
    Seq_cartas *inicio = jogador_atual->paleta;
    jogador_atual->pontuacao_na_regra = 0;
    jogador_atual->carta_mais_alta_na_regra = zerar_carta();

    while(jogador_atual->paleta != NULL){
        if(jogador_atual->paleta->dados_carta.numero_carta == numero_carta){
            contador_cartas++;

            if(contador_cartas >= maximo_cartas){
                maximo_cartas = contador_cartas;
                jogador_atual->pontuacao_na_regra = maximo_cartas;
                jogador_atual->carta_mais_alta_na_regra = jogador_atual->paleta->dados_carta;
            }
            jogador_atual->paleta = jogador_atual->paleta->proxima;
        }
        else{
            contador_cartas=0;
            numero_carta++;
        }
    }
    jogador_atual->paleta = inicio;
}

void avaliar_cartas_mesma_cor(Jogador *jogador_atual){   //Preciso ordenar pela cor.
    Seq_cartas *inicio = jogador_atual->paleta;
    int cores[7] = {0,0,0,0,0,0,0};
    jogador_atual->pontuacao_na_regra = 0;
    jogador_atual->carta_mais_alta_na_regra = zerar_carta();

    while(jogador_atual->paleta != NULL){
        cores[jogador_atual->paleta->dados_carta.id_cor-1]++;
        jogador_atual->paleta = jogador_atual->paleta->proxima;
    }

    jogador_atual->paleta = inicio;
    for(int i=0; i<7; i++){
        if(cores[i] > jogador_atual->pontuacao_na_regra) {
            jogador_atual->pontuacao_na_regra = cores[i];
        }
    }

    while(jogador_atual->paleta != NULL){
        if(cores[jogador_atual->paleta->dados_carta.id_cor-1] == jogador_atual->pontuacao_na_regra)
            jogador_atual->carta_mais_alta_na_regra = jogador_atual->paleta->dados_carta;
        jogador_atual->paleta = jogador_atual->paleta->proxima;
    }
    jogador_atual->paleta = inicio;
}

void avaliar_cartas_pares(Jogador *jogador_atual){ //ordenar por número
    Seq_cartas *inicio = jogador_atual->paleta;
    jogador_atual->pontuacao_na_regra = 0;
    jogador_atual->carta_mais_alta_na_regra = zerar_carta();

    while(jogador_atual->paleta != NULL){
        if(jogador_atual->paleta->dados_carta.numero_carta % 2 == 0){
            jogador_atual->pontuacao_na_regra++;
            jogador_atual->carta_mais_alta_na_regra = jogador_atual->paleta->dados_carta;
        }
        jogador_atual->paleta = jogador_atual->paleta->proxima;
    }
    jogador_atual->paleta = inicio;
}

void avaliar_menores_quatro(Jogador *jogador_atual){
    Seq_cartas *inicio = jogador_atual->paleta;
    jogador_atual->pontuacao_na_regra = 0;
    jogador_atual->carta_mais_alta_na_regra = zerar_carta();

    while(jogador_atual->paleta != NULL){
        if(jogador_atual->paleta->dados_carta.numero_carta < 4){
            jogador_atual->pontuacao_na_regra++;
            jogador_atual->carta_mais_alta_na_regra = jogador_atual->paleta->dados_carta;
        }
        jogador_atual->paleta = jogador_atual->paleta->proxima;
    }
    jogador_atual->paleta = inicio;
}

void avaliar_mais_cartas_sequencia(Jogador *jogador_atual){
    Seq_cartas *inicio = jogador_atual->paleta;
    jogador_atual->pontuacao_na_regra = 0;
    int contador_cartas=0;
    Carta vetor[7];
    for(int i=0; i<7; i++)
        vetor[i] = zerar_carta();

    jogador_atual->carta_mais_alta_na_regra = zerar_carta();

    while(jogador_atual->paleta != NULL){
        vetor[jogador_atual->paleta->dados_carta.numero_carta-1] = jogador_atual->paleta->dados_carta;
        jogador_atual->paleta = jogador_atual->paleta->proxima;
    }
    jogador_atual->paleta = inicio;
    for(int i=0; i<7; i++){
        if(vetor[i].numero_carta != 0){
            contador_cartas++;
            if(contador_cartas >= jogador_atual->pontuacao_na_regra){
                jogador_atual->pontuacao_na_regra = contador_cartas;
                jogador_atual->carta_mais_alta_na_regra = vetor[i];
            }
        }
        else{
            contador_cartas = 0;
        }
    }
}

void avaliar_cores_diferentes(Jogador *jogador_atual){
    int vetor[7] = {0,0,0,0,0,0,0};
    Seq_cartas *inicio = jogador_atual->paleta;
    jogador_atual->pontuacao_na_regra = 0;
    jogador_atual->carta_mais_alta_na_regra = zerar_carta();

    while(jogador_atual->paleta != NULL){
        if(vetor[jogador_atual->paleta->dados_carta.id_cor - 1] == 0){
            vetor[jogador_atual->paleta->dados_carta.id_cor - 1] = 1;
            jogador_atual->pontuacao_na_regra++;
        }
        jogador_atual->paleta = jogador_atual->paleta->proxima;
    }
    jogador_atual->paleta = inicio;
    while(jogador_atual->paleta->proxima != NULL)
        jogador_atual->paleta = jogador_atual->paleta->proxima;
    jogador_atual->carta_mais_alta_na_regra = jogador_atual->paleta->dados_carta;
    jogador_atual->paleta = inicio;
}

int desempatar(Jogador **atual, Jogador **vencedor){
    if(((*atual)->carta_mais_alta_na_regra.numero_carta > (*vencedor)->carta_mais_alta_na_regra.numero_carta) ||
       ((*atual)->carta_mais_alta_na_regra.numero_carta == (*vencedor)->carta_mais_alta_na_regra.numero_carta &&
        (*atual)->carta_mais_alta_na_regra.id_cor > (*vencedor)->carta_mais_alta_na_regra.id_cor)){
        return 1;
       }
    else{
        return 0;
    }
}

void comparar_paletas_jogadores(Jogador **atual, Jogador **vencedor){

    if(*vencedor == NULL){
        (*vencedor) = (*atual);
        return;
    }

    if((*atual) == (*vencedor))
        return;
    if((*atual)->pontuacao_na_regra > (*vencedor)->pontuacao_na_regra ||
       ((*atual)->pontuacao_na_regra == (*vencedor)->pontuacao_na_regra && desempatar(&(*atual), &(*vencedor)))){
        (*vencedor) = (*atual);
    }
}

void escolher_jogada(Jogador **atual){

    if((*atual)->mao->qtd_cartas > 0){ //Valida se o jogador tem carta na mão pra jogar
        imprimir_opcoes_cartas(&(*atual));//chamar função que mostra as cartas
        do{
            (*atual)->jogada = opcoes_jogada();
            if((*atual)->jogada == 3 && (*atual)->mao->qtd_cartas < 2)
                printf("Você só tem uma carta na mão. Não pode escolher essa opção de jogada.\n");
        }while((*atual)->jogada == 3 && (*atual)->mao->qtd_cartas < 2);
    }
    else{
        printf("%s não tem mais cartas na mão para jogar.\n", (*atual)->nome);
        system("pause");
        (*atual)->jogada = 0;
    }
    if((*atual)->jogada == 1 || (*atual)->jogada == 3){
        jogar_carta_paleta(&(*atual));
    }else if((*atual)->jogada == 2){
        jogar_carta_regra(&(*atual));
    }
}

void jogar_carta_paleta(Jogador **atual){
    printf("Escolha uma carta pra pôr na paleta:\n");
    (*atual)->escolhida_paleta = escolher_carta(&(*atual)->mao);
    adicionar_carta_sequencia(&(*atual)->paleta, (*atual)->escolhida_paleta);
    if((*atual)->jogada == 3)
        jogar_carta_regra(&(*atual));
}

void jogar_carta_regra(Jogador **atual){
    printf("Escolha uma carta para trocar a regra:\n");
    if((*atual)->jogada == 3){
        do{
            (*atual)->escolhida_regra = escolher_carta(&(*atual)->mao);
            if((*atual)->escolhida_regra.numero_carta == (*atual)->escolhida_paleta.numero_carta && (*atual)->escolhida_regra.id_cor == (*atual)->escolhida_paleta.id_cor)
                printf("Voce já escolheu essa carta para pôr na paleta.\n");
        }while((*atual)->escolhida_regra.numero_carta == (*atual)->escolhida_paleta.numero_carta && (*atual)->escolhida_regra.id_cor == (*atual)->escolhida_paleta.id_cor);
    }
    else{
        (*atual)->escolhida_regra = escolher_carta(&(*atual)->mao);
    }
    regra_corrente = (*atual)->escolhida_regra.id_cor;
}

void tirar_cartas(Jogador **atual, int ganhou, Descritor_Jogo *pont_descritor, Baralho *pont_baralho){
    if(ganhou){
        printf("Você ganhou com essa jogada.\n");
        system("pause");
        if((*atual)->jogada == 1 || (*atual)->jogada == 3){
            desalocar_carta(&(*atual)->mao, (*atual)->escolhida_paleta);
        }
        if((*atual)->jogada == 2 || (*atual)->jogada == 3){
            desalocar_carta(&(*atual)->mao, (*atual)->escolhida_regra);
            if((*atual)->escolhida_regra.numero_carta == 1 || (*atual)->escolhida_regra.numero_carta == 3 || (*atual)->escolhida_regra.numero_carta == 5 || (*atual)->escolhida_regra.numero_carta == 7){ //Chama símbolos
                printf("Sua carta tem opção especial do símbolo.\n");
                system("pause");
                usar_simbolo(&(*atual), pont_descritor, pont_baralho);
            }
        }
    }
    else{
        if((*atual)->jogada == 1 || (*atual)->jogada == 3){
            desalocar_carta(&(*atual)->paleta, (*atual)->escolhida_paleta);
        }
    }
}

Carta zerar_carta(){
    Carta retornar_zerada;

    retornar_zerada.numero_carta = 0;
    retornar_zerada.id_cor = 0;
    retornar_zerada.cor_imprimir = 0;
    strcpy(retornar_zerada.regra, "");
    strcpy(retornar_zerada.regra, "");

    return retornar_zerada;
}
