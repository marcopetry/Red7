#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include "Tipos_Dados.h"
#include "Funcoes_Baralho.h"
#include "Mesa_Jogadores.h"
#include "Funcoes_Impressao.h"
#include "Funcoes_Jogo.h"
#include "Alocar.h"
#include "Simbolos.h"

int main()
{
    setlocale(LC_ALL, "");

    while(imprimir_opcao_inicio()){
        Baralho *baralho_jogo = iniciar_baralho_jogo(); //Inicializa o baralho e embaralha
        //imprimir_baralho(baralho_jogo);
        Descritor_Jogo *marcador_jogo = alocar_descritivo();
        Mesa_Jogadores *mesa_jogo = alocar_mesa();

        void (*regra_jogo[7])(Jogador*); //Ponteiro que guarda a função de avaliar pela regra corrente
        regra_jogo[0] = avaliar_menores_quatro;
        regra_jogo[1] = avaliar_mais_cartas_sequencia;
        regra_jogo[2] = avaliar_cores_diferentes;
        regra_jogo[3] = avaliar_cartas_pares;
        regra_jogo[4] = avaliar_cartas_mesma_cor;
        regra_jogo[5] = avaliar_mais_mesmo_numero;
        regra_jogo[6] = avaliar_carta_mais_alta_paleta; // Inicia meu ponteiro com todas as regras

        qtd_jogadores = imprimir_opcao_qtd_jogadores(); //Entrar com quantos jogadores vão jogar
        regra_corrente=7; // Uso essa variável para controlar a regra, começa na regra da carta mais alta
        int verificador_jogada; //vai verificar se jogador ganhou na jogada pra passar a vez
        int tentativas; //vai controlar pro jogador não ficar fazendo várias jogadas inválidas, se fizer 3 jogadas inválidas ele perde
        int aux_regra;//Uso pra quando jogador faz troca de regra inválida

        while(marcador_jogo->qtd_jogador < qtd_jogadores){   //Inicia a mesa, dá as cartas, e encadea circular todos os jogadores
            inserir_jogador_mesa(mesa_jogo, marcador_jogo, baralho_jogo);
        }
        definir_primeiro_jogador_jogar(mesa_jogo, marcador_jogo);  //Confere quem tem a paleta com a carta mais alta
        //Vou usar pra guardar o vencedor na regra
        Jogador *vencedor = marcador_jogo->ultimo_jogar->dados_jogador; //Marca o jogador com a paleta mais alta

        while(marcador_jogo->qtd_jogador > 1){ //Aqui é o jogo com a funções de jogar
            verificador_jogada = tentativas = 0; //Cada jogada é zerado os verificadores
            do{
                system("cls"); //Limpa tela
                aux_regra = regra_corrente; //Uso pra quando jogador faz troca de regra inválida
                printf("Vez do %s jogar.\n\n", marcador_jogo->jogador_atual->dados_jogador->nome);
                printf("O baralho tem %d carta(s).\n", baralho_jogo->topo);
                explicar_jogada(&marcador_jogo->jogador_atual->dados_jogador, &vencedor); //imprimir a regra corrente
                imprimir_paletas_jogadores(marcador_jogo->jogador_atual);//imprimir a paleta de todos

                escolher_jogada(&(marcador_jogo->jogador_atual->dados_jogador));

                avaliar_todos_jogadores_regra(mesa_jogo, regra_jogo[regra_corrente-1], &vencedor);

                if(marcador_jogo->jogador_atual->dados_jogador == vencedor){    //quando ganha com a jogada
                    verificador_jogada++;
                    tirar_cartas(&marcador_jogo->jogador_atual->dados_jogador, verificador_jogada, marcador_jogo, baralho_jogo);
                }
                else{    //Quando perde com a jogada
                    tirar_cartas(&marcador_jogo->jogador_atual->dados_jogador, verificador_jogada, marcador_jogo, baralho_jogo);
                    tentativas++;
                    if(marcador_jogo->jogador_atual->dados_jogador->jogada != 0){
                        printf("Você não venceu com a jogada que fez. Abaixo suas informações.\n");
                        system("pause");
                        explicar_jogada(&marcador_jogo->jogador_atual->dados_jogador, &vencedor);//Explica porquê jogador não venceu na tentativa
                    }

                    regra_corrente = aux_regra; // Altera a regra de volta a que tava caso não tenha ganhado nela
                }
                avaliar_todos_jogadores_regra(mesa_jogo, regra_jogo[regra_corrente-1], &vencedor);  //avalia de volta antes de passar a vez, ele pode não ter vencido na regra, ou mudar a pontuação devido ao uso dos símbolos

                if(tentativas == 2 && verificador_jogada==0 && marcador_jogo->jogador_atual->dados_jogador->jogada != 0){ // Mensagem antes de perder por jogadas inválidas
                    printf("Se errar mais uma jogada você perde.\n");
                    system("pause");
                }

            }  while(verificador_jogada == 0 && tentativas < 3 && marcador_jogo->jogador_atual->dados_jogador->jogada != 0);

            if(tentativas == 3){ // Vai excluir jogador da partida
                marcador_jogo->jogador_atual->dados_jogador->jogada = 0;
            }
            if(marcador_jogo->jogador_atual->dados_jogador->jogada == 0){
                marcador_jogo->qtd_jogador--;
                printf("Jogador %s perdeu e está fora.\n", marcador_jogo->jogador_atual->dados_jogador->nome);
                system("pause");
            }

            marcador_jogo->jogador_atual = marcador_jogo->jogador_atual->proximo_jogador;
            while(marcador_jogo->jogador_atual->dados_jogador->jogada == 0)  //Passa pro próximo jogador que está no jogo ainda
                marcador_jogo->jogador_atual = marcador_jogo->jogador_atual->proximo_jogador;

        }
        printf("\n\nO vencedor é %s.\n\n", marcador_jogo->jogador_atual->dados_jogador->nome);
        system("pause");
    }

    return 0;
}

//jogada
