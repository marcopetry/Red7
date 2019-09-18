void inserir_jogador_mesa(Mesa_Jogadores *pont_mesa, Descritor_Jogo *pont_descritor, Baralho *pont_baralho);

void definir_primeiro_jogador_jogar(Mesa_Jogadores *pont_mesa, Descritor_Jogo *pont_descritor);

Jogador* criar_jogador(Baralho* pont_baralho);

Jogador* retornar_jogador_escolhido(Mesa_Jogadores *pont_mesa, int numero_jogador);
