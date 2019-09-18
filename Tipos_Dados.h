struct carta{  //Usei essa estrutura est�tica para iniciar as cartas
    int numero_carta;
    int cor_imprimir;
    int id_cor;
    char cor[15];
    char regra[50];
};

struct baralho{ //Pilha est�tica que sempre entrega carta de cima, maior indice
    struct carta pilha_cartas[49];
    int topo;
};

struct seq_cartas{  //Lista din�mica de sequ�ncia de cartas tanto para m�o quanto para paleta
    int qtd_cartas;       //To usando pra iniciar guardar a quantidade de cartas na m�o e na paleta
    struct carta dados_carta;
    struct seq_cartas *proxima;
};

struct jogador{
    char nome[20];
    struct seq_cartas *mao;
    struct seq_cartas *paleta;
    int pontuacao_na_regra;      //Quantidade de cartas que satisfazem a regra
    struct carta escolhida_paleta; //Guarda a carta que vai ser colocada na paleta,uso elas pra poder voltar ao estado anterior caso jogador fa�a jogada inv�lida
    struct carta escolhida_regra; //Guarda a carta ir� mudar a regra
    struct carta carta_mais_alta_na_regra; //Maior carta da paleta que satisfaz a regra vigente para casos de empate
    int jogada; //Vai guardar a opcao de jogada do participante e 0 se ele perdeu j�
};

struct mesa_jogadores{ //Lista circular din�mica de jogadores para montar a mesa
    struct jogador *dados_jogador;
    struct mesa_jogadores *proximo_jogador;
};

struct descritor_mesa{
    struct mesa_jogadores *primeiro_jogar; //Uso s� pra circular a lista dos meus jogadores e definir quem come�a
    struct mesa_jogadores *ultimo_jogar; //Uso s� pra circular a lista dos meus jogadores e definir quem come�a
    struct mesa_jogadores *jogador_atual; //uso esse pra marcar de quem � a vez de jogar e todo o jogo
    int qtd_jogador; //Vai definir quando o jogo termina, quantos jogadores t�m ativos e tamb�m pra alocar a quantidade de jogadores do jogo
};

//Defini��es dos tipos de dados
typedef struct carta Carta;
typedef struct baralho Baralho;
typedef struct seq_cartas Seq_cartas;
typedef struct jogador Jogador;
typedef struct mesa_jogadores Mesa_Jogadores;
typedef struct descritor_mesa Descritor_Jogo;

typedef void(*regra)(Jogador*); //Definido ponteiro de uso

int regra_corrente; //Global para controlar a regra mais f�cil
int qtd_jogadores;// Global pra validar o jogador selecionado mais f�cil

