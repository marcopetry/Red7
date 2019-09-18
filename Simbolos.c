#include <stdio.h>
#include <stdlib.h>
#include "Tipos_Dados.h"
#include "Funcoes_Baralho.h"
#include "Mesa_Jogadores.h"
#include "Funcoes_Impressao.h"
#include "Funcoes_Jogo.h"
#include "Alocar.h"
#include "Simbolos.h"

void usar_simbolo(Jogador ** atual, Descritor_Jogo *pont_descritor, Baralho *pont_baralho){
    system("cls");
    imprimir_paletas_jogadores(pont_descritor->jogador_atual);
    imprimir_opcoes_cartas(&(*atual));
    int opcao_usar = escolher_usar_simbolo((*atual)->escolhida_regra.numero_carta);
    if(opcao_usar){
        if((*atual)->escolhida_regra.numero_carta == 1){
            executar_simbolo_1(&(*atual), pont_descritor, pont_baralho);
        }
        else if((*atual)->escolhida_regra.numero_carta == 3){
            executar_simbolo_3(&(*atual), pont_baralho);
        }
        else if((*atual)->escolhida_regra.numero_carta == 5){
            executar_simbolo_5(&(*atual), pont_descritor, pont_baralho);
        }
        else if((*atual)->escolhida_regra.numero_carta == 7){
            executar_simbolo_7(&(*atual), pont_descritor, pont_baralho);
        }
    }
    else{
        printf("Você não quis usar a função do símbolo da carta.\n");
    }
}

void executar_simbolo_1(Jogador **atual, Descritor_Jogo *pont_descritor, Baralho *pont_baralho){
    int numero_jogador_escolhido, sair = 1, tentativas = 0;
    Jogador *escolhido_tirar_carta_paleta;
    Carta tirada_paleta;
    do{
        limpa_buffer();
        imprimir_paletas_jogadores(pont_descritor->jogador_atual);
        imprimir_opcoes_cartas(&(*atual));
        numero_jogador_escolhido = selecionar_jogador();
        escolhido_tirar_carta_paleta = retornar_jogador_escolhido(pont_descritor->jogador_atual, numero_jogador_escolhido);
        if(escolhido_tirar_carta_paleta->paleta->qtd_cartas < (*atual)->paleta->qtd_cartas){
            tentativas++;
            printf("Jogador escolhido tem menos cartas que você na paleta.\n");
            do{
                limpa_buffer();
                printf("Você quer escolher outro jogador?\n");
                printf("1 - Sim.\n");
                printf("0 - Não.\n");
                scanf("%d", &sair);
                if(sair != 0 && sair != 1)
                    printf("Opção inválida.\n");
            }while(sair != 0 && sair != 1 && tentativas < 3);
            if(tentativas == 2 && sair == 1){
                printf("Se escolher um jogador com menos cartas que você novamente, perderá a ação.\n");
                system("pause");
            }
        }
    }while(escolhido_tirar_carta_paleta->paleta->qtd_cartas < (*atual)->paleta->qtd_cartas && sair == 1 && tentativas < 3);

    if(escolhido_tirar_carta_paleta->paleta->qtd_cartas >= (*atual)->paleta->qtd_cartas){
        printf("As opções de cartas na paleta do jogador escolhido são: \n");
        imprimir_sequencia_cartas(escolhido_tirar_carta_paleta->paleta);
        tirada_paleta = escolher_carta(&(escolhido_tirar_carta_paleta)->paleta);
        desalocar_carta(&(escolhido_tirar_carta_paleta)->paleta, tirada_paleta);
        empilhar_carta_baralho(pont_baralho, tirada_paleta);
        printf("Você tirou a carta : ");
        imprimir_carta(tirada_paleta);
        system("pause");
    }
}

void executar_simbolo_3(Jogador **atual, Baralho *pont_baralho){
    if(pont_baralho->topo > 0){
        Carta comprada = pegar_carta(pont_baralho);
        printf("A carta comprada foi: \n");
        imprimir_carta(comprada);
        adicionar_carta_sequencia(&(*atual)->mao, comprada);
    }
    else{
        printf("O baralho não tem cartas. Voce não pode usar o símbolo.\n");
    }
    system("pause");
}

void executar_simbolo_5(Jogador **atual, Descritor_Jogo *pont_descritor, Baralho *pont_baralho){
    int jogar;
    (*atual)->jogada = 1; //Fiz essa atribuição para quando for usar o símbolo não cair dentro das condicionais das jogadas convencionais
    if((*atual)->mao->qtd_cartas > 0){
        do{
            limpa_buffer();
            imprimir_opcoes_cartas(&(*atual));
            printf("Vai querer largar mais uma carta na paleta? \n");
            printf("1 - Sim.\n");
            printf("0 - Não.\n");
            scanf("%d", &jogar);
            if(jogar != 0 && jogar != 1)
                printf("Opção inválida.\n");
            if(jogar == 1){
                jogar_carta_paleta(&(*atual));
                desalocar_carta(&(*atual)->mao, (*atual)->escolhida_paleta);
            }
        } while(jogar != 0 && jogar != 1);
    }
    else{
        printf("Você não tem carta para pôr na paleta.\n");
        system("pause");
        return;
    }

    if((*atual)->mao->qtd_cartas > 0){
        printf("Sua paleta após usar o simbolo é:\n");
        imprimir_opcoes_cartas(&(*atual));

        do{
            limpa_buffer();
            printf("Vai querer largar mais uma carta na tela e mudar a regra? \n");
            printf("1 - Sim.\n");
            printf("0 - Não.\n");
            scanf("%d", &jogar);
            if(jogar != 0 && jogar != 1)
                printf("Opção inválida.\n");
            if(jogar == 1){
                (*atual)->escolhida_regra = escolher_carta(&(*atual)->mao);
                regra_corrente = (*atual)->escolhida_regra.id_cor;
                desalocar_carta(&(*atual)->mao, (*atual)->escolhida_regra);
                if((*atual)->escolhida_regra.numero_carta == 1 || (*atual)->escolhida_regra.numero_carta == 3 || (*atual)->escolhida_regra.numero_carta == 5 || (*atual)->escolhida_regra.numero_carta == 7){ //Chama símbolos
                    usar_simbolo(&(*atual), pont_descritor, pont_baralho);
                }
            }
        } while(jogar != 0 && jogar != 1);
    }
    else{
        printf("Você não tem carta pra largar na tela.\n");
        system("pause");
    }
}

void executar_simbolo_7(Jogador **atual, Descritor_Jogo *pont_descritor, Baralho *pont_baralho){
    printf("Escolha a carta da paleta que vai por na tela para mudar a regra.\n");
    imprimir_sequencia_cartas((*atual)->paleta);
    (*atual)->escolhida_regra = escolher_carta(&(*atual)->paleta);
    regra_corrente = (*atual)->escolhida_regra.id_cor;
    desalocar_carta(&(*atual)->paleta, (*atual)->escolhida_regra);
    if((*atual)->escolhida_regra.numero_carta == 1 || (*atual)->escolhida_regra.numero_carta == 3 || (*atual)->escolhida_regra.numero_carta == 5 || (*atual)->escolhida_regra.numero_carta == 7){ //Chama símbolos
        usar_simbolo(&(*atual), pont_descritor, pont_baralho);
    }
}
