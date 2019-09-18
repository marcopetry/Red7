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
    printf("Quem joga primeiro é: %s\n\n", primeiro->dados_jogador->nome);
}

int opcoes_jogada(){
    int opcao;

    do{
        limpa_buffer();
        printf("Escolha uma opção de jogada: \n");
        printf("1 - Colocar uma carta na paleta.\n");
        printf("2 - Trocar a regra.\n");
        printf("3 - Colocar uma carta na paleta e trocar a regra.\n");
        printf("0 - Passar a vez e perder.\n");
        scanf("%d", &opcao);
        if(opcao < 0 || opcao > 3)
            printf("Opção Inválida.\n\n");
    }while(opcao < 0 || opcao > 3);

    return opcao;
}

void imprimir_opcoes_cartas(Jogador **atual){

    printf("\nSuas cartas da mão são: \n");
    imprimir_sequencia_cartas((*atual)->mao);
    printf("\nSuas cartas da paleta são: \n");
    imprimir_sequencia_cartas((*atual)->paleta);
}

int imprimir_opcao_qtd_jogadores(){
    int qtd_jogadores = 0;

    do{
        limpa_buffer();
        printf("Quantos jogadores vão jogar? \n");
        scanf("%d", &qtd_jogadores);
        if(qtd_jogadores < 2 || qtd_jogadores > 6)
            printf("Quantidade inválida.\n");
        //qtd_jogadores = (int) qtd_jogadores + 0;
    }while(qtd_jogadores < 2 || qtd_jogadores > 6);
    return qtd_jogadores;
}

int imprimir_opcao_inicio(){
    int opcao;

    do{
        limpa_buffer();
        printf("Escolha uma opção: \n");
        printf("1 - Jogar uma partida.\n");
        printf("0 - Finalizar o jogo.\n");
        scanf("%d", &opcao);
        if(opcao != 0 && opcao != 1)
            printf("Opção inválida.\n");
    }while(opcao != 0 && opcao != 1);
    return opcao;
}

void imprimir_regra(Jogador **vencedor){
    printf("Regra atual:\n");
    switch (regra_corrente){
    case 1:
        printf("Mais números abaixo de quatro vencem.\n");
        break;
    case 2:
        printf("Mais números em sequência vencem.\n");
        break;
    case 3:
        printf("Mais cores diferentes vencem.\n");
        break;
    case 4:
        printf("Mais números pares vencem.\n");
        break;
    case 5:
        printf("Mais de uma mesma cor vence.\n");
        break;
    case 6:
        printf("Mais do mesmo número vence.\n");
        break;
    case 7:
        printf("Carta mais alta vence.\n");
        break;
    }
    printf("\nO vencedor na regra é %s. Ele tem %d pontos.\n", (*vencedor)->nome, (*vencedor)->pontuacao_na_regra);
    printf("A carta mais alta dele que satisfaz a regra é: \n");
    imprimir_carta((*vencedor)->carta_mais_alta_na_regra);
    printf("\n\n");
}

void imprimir_paletas_jogadores(Mesa_Jogadores *pont_mesa){
    int numero_jogador=1;
    Mesa_Jogadores *primeiro = pont_mesa;
    pont_mesa = pont_mesa->proximo_jogador;

    while(pont_mesa != primeiro){
        if(pont_mesa->dados_jogador->jogada != 0){
            printf("\n%d - O jogador %s está jogando e sua paleta é: \n", numero_jogador, pont_mesa->dados_jogador->nome);
            printf("    Ele tem %d cartas na mão.\n\n", pont_mesa->dados_jogador->mao->qtd_cartas);
        }
        else
            printf("\n%d - O jogador %s já perdeu e sua paleta é: \n\n", numero_jogador, pont_mesa->dados_jogador->nome);
        imprimir_sequencia_cartas(pont_mesa->dados_jogador->paleta);
        pont_mesa = pont_mesa->proximo_jogador;
        numero_jogador++;
        if(pont_mesa == primeiro)
            break;
    }
    printf("\n");
}

void imprimir_carta(Carta dados_carta){
    //Trecho de código para mudar cor tirado da internet
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
    printf("Sua pontuação na regra é %d.\n", (*atual)->pontuacao_na_regra);
    printf("A sua carta mais alta que satisfaz a regra é : \n");
    imprimir_carta((*atual)->carta_mais_alta_na_regra);
    printf("\n");
    system("pause");
}

int escolher_usar_simbolo(int numero_carta){
    int quer_usar_simbolo;
    printf("\nVocê quer usar o símbolo? Abaixo a especificação da ação dele.\n\n");
    do{
        limpa_buffer();
        switch(numero_carta){
        case 1:
            printf("Você pode pegar uma carta da paleta de outro jogador e colocar em cima do baralho.\n");
            printf("Voce não poderá escolher alguém com menos carta que você na paleta.\n");
            break;
        case 3:
            printf("Comprar uma carta do baralho.\n");
            break;
        case 5:
            printf("Jogar mais uma carta da mão na paleta e/ou na tela.\n");
            break;
        case 7:
            printf("Jogar uma carta da paleta na tela.\n");
            break;
        }
        printf("\nDigite:\n");
        printf("1 - Usar símbolo.\n");
        printf("0 - Não usar símbolo.\n");
        scanf("%d", &quer_usar_simbolo);
        if((quer_usar_simbolo != 0 && quer_usar_simbolo != 1)){
            printf("Opção inválida.\n");
        }
    }while(quer_usar_simbolo != 0 && quer_usar_simbolo != 1);
    system("cls");
    return quer_usar_simbolo;
}

int selecionar_jogador(){
    int opcao_jogador;
    do{
        limpa_buffer();
        printf("Qual o jogador que você quer tirar a carta?\n");
        printf("Entre com o número que aparece antes das informações do jogador.\n");
        printf("Lembre-se que ele não pode ter menos cartas que você na paleta.\n");
        scanf("%d", &opcao_jogador);
        if(opcao_jogador < 1 || opcao_jogador > qtd_jogadores -1)
            printf("Jogador não existe.\n");
    }while(opcao_jogador < 1 || opcao_jogador > qtd_jogadores -1);
}



