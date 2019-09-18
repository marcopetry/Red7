#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Tipos_Dados.h"
#include "Funcoes_Baralho.h"
#include "Mesa_Jogadores.h"
#include "Funcoes_Impressao.h"
#include "Funcoes_Jogo.h"
#include "Alocar.h"
#include "Simbolos.h"
#include <windows.h>

void imprimir_inicio_jogo(Mesa_Jogadores *primeiro){
    printf("Quem joga primeiro �: %s\n\n", primeiro->dados_jogador->nome);
}

int opcoes_jogada(){
    int opcao;

    do{
        limpa_buffer();
        printf("Escolha uma op��o de jogada: \n");
        printf("1 - Colocar uma carta na paleta.\n");
        printf("2 - Trocar a regra.\n");
        printf("3 - Colocar uma carta na paleta e trocar a regra.\n");
        printf("0 - Passar a vez e perder.\n");
        scanf("%d", &opcao);
        if(opcao < 0 || opcao > 3)
            printf("Op��o Inv�lida.\n\n");
    }while(opcao < 0 || opcao > 3);

    return opcao;
}

void imprimir_opcoes_cartas(Jogador **atual){

    printf("\nSuas cartas da m�o s�o: \n");
    imprimir_sequencia_cartas((*atual)->mao);
    printf("\nSuas cartas da paleta s�o: \n");
    imprimir_sequencia_cartas((*atual)->paleta);
}

int imprimir_opcao_qtd_jogadores(){
    int qtd_jogadores = 0;

    do{
        limpa_buffer();
        printf("Quantos jogadores v�o jogar? \n");
        scanf("%d", &qtd_jogadores);
        if(qtd_jogadores < 2 || qtd_jogadores > 6)
            printf("Quantidade inv�lida.\n");
        //qtd_jogadores = (int) qtd_jogadores + 0;
    }while(qtd_jogadores < 2 || qtd_jogadores > 6);
    return qtd_jogadores;
}

int imprimir_opcao_inicio(){
    int opcao;

    do{
        limpa_buffer();
        printf("Escolha uma op��o: \n");
        printf("1 - Jogar uma partida.\n");
        printf("0 - Finalizar o jogo.\n");
        scanf("%d", &opcao);
        if(opcao != 0 && opcao != 1)
            printf("Op��o inv�lida.\n");
    }while(opcao != 0 && opcao != 1);
    return opcao;
}

void imprimir_regra(Jogador **vencedor){
    printf("Regra atual:\n");
    switch (regra_corrente){
    case 1:
        printf("Mais n�meros abaixo de quatro vencem.\n");
        break;
    case 2:
        printf("Mais n�meros em sequ�ncia vencem.\n");
        break;
    case 3:
        printf("Mais cores diferentes vencem.\n");
        break;
    case 4:
        printf("Mais n�meros pares vencem.\n");
        break;
    case 5:
        printf("Mais de uma mesma cor vence.\n");
        break;
    case 6:
        printf("Mais do mesmo n�mero vence.\n");
        break;
    case 7:
        printf("Carta mais alta vence.\n");
        break;
    }
    printf("\nO vencedor na regra � %s. Ele tem %d pontos.\n", (*vencedor)->nome, (*vencedor)->pontuacao_na_regra);
    printf("A carta mais alta dele que satisfaz a regra �: \n");
    imprimir_carta((*vencedor)->carta_mais_alta_na_regra);
    printf("\n\n");
}

void imprimir_paletas_jogadores(Mesa_Jogadores *pont_mesa){
    int numero_jogador=1;
    Mesa_Jogadores *primeiro = pont_mesa;
    pont_mesa = pont_mesa->proximo_jogador;

    while(pont_mesa != primeiro){
        if(pont_mesa->dados_jogador->jogada != 0){
            printf("\n%d - O jogador %s est� jogando e sua paleta �: \n", numero_jogador, pont_mesa->dados_jogador->nome);
            printf("    Ele tem %d cartas na m�o.\n\n", pont_mesa->dados_jogador->mao->qtd_cartas);
        }
        else
            printf("\n%d - O jogador %s j� perdeu e sua paleta �: \n\n", numero_jogador, pont_mesa->dados_jogador->nome);
        imprimir_sequencia_cartas(pont_mesa->dados_jogador->paleta);
        pont_mesa = pont_mesa->proximo_jogador;
        numero_jogador++;
        if(pont_mesa == primeiro)
            break;
    }
    printf("\n");
}

void imprimir_carta(Carta dados_carta){
    //Trecho de c�digo para mudar cor tirado da internet
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, dados_carta.cor_imprimir);

    printf("%d da cor %s   Regra: %s\n", dados_carta.numero_carta, dados_carta.cor, dados_carta.regra);
    /* Voltando ao estado original */
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void imprimir_sequencia_cartas(Seq_cartas* cartas_sequencia){
    int ordem_carta = 1;

    while(cartas_sequencia != NULL){
        printf("    Carta %d: ", ordem_carta);
        imprimir_carta(cartas_sequencia->dados_carta);
        cartas_sequencia = cartas_sequencia->proxima;
        ordem_carta++;
    }
    printf("\n");
}

void imprimir_baralho(Baralho* pont_baralho){
    int i=0;
    while(i<49){
        imprimir_carta(pont_baralho->pilha_cartas[i]);
        //printf("Carta %d: %d  %s id cor %d.\n", i+1, pont_baralho->pilha_cartas[i].numero_carta, pont_baralho->pilha_cartas[i].cor, pont_baralho->pilha_cartas[i].id_cor);
        //printf("Numero da cor: %d\n\n", pont_baralho->pilha_cartas[i].id_cor);
        i++;
    }
}

void limpa_buffer(){
    fseek(stdin, 0, SEEK_SET);
}

void explicar_jogada(Jogador **atual, Jogador **vencedor){
    printf("\n");
    imprimir_regra(&(*vencedor));
    printf("Sua pontua��o na regra � %d.\n", (*atual)->pontuacao_na_regra);
    printf("A sua carta mais alta que satisfaz a regra � : \n");
    imprimir_carta((*atual)->carta_mais_alta_na_regra);
    printf("\n");
    system("pause");
}

int escolher_usar_simbolo(int numero_carta){
    int quer_usar_simbolo;
    printf("\nVoc� quer usar o s�mbolo? Abaixo a especifica��o da a��o dele.\n\n");
    do{
        limpa_buffer();
        switch(numero_carta){
        case 1:
            printf("Voc� pode pegar uma carta da paleta de outro jogador e colocar em cima do baralho.\n");
            printf("Voce n�o poder� escolher algu�m com menos carta que voc� na paleta.\n");
            break;
        case 3:
            printf("Comprar uma carta do baralho.\n");
            break;
        case 5:
            printf("Jogar mais uma carta da m�o na paleta e/ou na tela.\n");
            break;
        case 7:
            printf("Jogar uma carta da paleta na tela.\n");
            break;
        }
        printf("\nDigite:\n");
        printf("1 - Usar s�mbolo.\n");
        printf("0 - N�o usar s�mbolo.\n");
        scanf("%d", &quer_usar_simbolo);
        if((quer_usar_simbolo != 0 && quer_usar_simbolo != 1)){
            printf("Op��o inv�lida.\n");
        }
    }while(quer_usar_simbolo != 0 && quer_usar_simbolo != 1);
    system("cls");
    return quer_usar_simbolo;
}

int selecionar_jogador(){
    int opcao_jogador;
    do{
        limpa_buffer();
        printf("Qual o jogador que voc� quer tirar a carta?\n");
        printf("Entre com o n�mero que aparece antes das informa��es do jogador.\n");
        printf("Lembre-se que ele n�o pode ter menos cartas que voc� na paleta.\n");
        scanf("%d", &opcao_jogador);
        if(opcao_jogador < 1 || opcao_jogador > qtd_jogadores -1)
            printf("Jogador n�o existe.\n");
    }while(opcao_jogador < 1 || opcao_jogador > qtd_jogadores -1);
}



