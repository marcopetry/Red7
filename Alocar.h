Jogador* aloca_jogador();

struct seq_cartas* aloca_sequencia_cartas();

void adicionar_carta_sequencia(Seq_cartas** pont_seq, Carta carta_retirada); //Vai pegar carta alocada e encadear. Tamb�m vai alocar a m�o na mem�ria

void desalocar_carta(Seq_cartas **pont_seq, Carta descartar);

Descritor_Jogo* alocar_descritivo();

Mesa_Jogadores* alocar_mesa();

