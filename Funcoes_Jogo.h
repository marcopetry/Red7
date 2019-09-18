Carta escolher_carta(Seq_cartas **pont_seq);

void avaliar_todos_jogadores_regra(Mesa_Jogadores *pont_mesa, regra avaliacao, Jogador **vencedor);

void definir_vencedor(Mesa_Jogadores *pont_mesa, Jogador **vencedor);

void avaliar_carta_mais_alta_paleta(Jogador *jogador_atual);   //Vai até final da paleta ordenada e atribui a carta maior

void avaliar_mais_mesmo_numero(Jogador *jogador_atual);

void avaliar_cartas_mesma_cor(Jogador *jogador_atual);

void avaliar_cartas_pares(Jogador *jogador_atual);

void avaliar_menores_quatro(Jogador *jogador_atual);

void avaliar_mais_cartas_sequencia(Jogador *jogador_atual);

void avaliar_cores_diferentes(Jogador *jogador_atual);

int desempatar(Jogador **atual, Jogador **vencedor);

void comparar_paletas_jogadores(Jogador **atual, Jogador **vencedor);

void escolher_jogada(Jogador **atual);

void tirar_cartas(Jogador **atual, int ganhou, Descritor_Jogo *pont_descritor_jogo, Baralho *pont_baralho); //Essa função vai receber como parâmetro se o jogador venceu com a jogada para desalocar a carta da mão, ou se perdeu e desalocar da paleta

void jogar_carta_paleta(Jogador **atual);

void jogar_carta_regra(Jogador **atual);

Carta zerar_carta(); //Vai colocar nulo todos os atributos da carta, para não gerar erros durante a execução
