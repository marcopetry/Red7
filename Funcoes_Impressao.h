void imprimir_inicio_jogo(Mesa_Jogadores *primeiro); //Imprime na tela quem começa jogando

int opcoes_jogada();

void imprimir_opcoes_cartas(Jogador **atual);

int imprimir_opcao_qtd_jogadores();

void imprimir_regra(Jogador **vencedor); //Imprimi a regra e o vencedor nela

void imprimir_paletas_jogadores(Mesa_Jogadores *pont_mesa);

void imprimir_carta(Carta dados_carta);

void imprimir_sequencia_cartas(Seq_cartas *cartas_sequencia);

void imprimir_baralho(Baralho *pont_baralho); //Usei bastante nos testes apenas

void limpa_buffer();

void explicar_jogada(Jogador **atual, Jogador **vencedor); //Explica pq jogador não venceu

int escolher_usar_simbolo(int numero_carta);

int selecionar_jogador();

