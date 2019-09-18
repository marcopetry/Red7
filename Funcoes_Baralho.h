Carta* iniciar_cartas();  /*Essa função inicia o baralho do 1 ao 7 e a cor mais fraca até a mais forte*/

Baralho* colocar_cartas_baralho(Carta* pont_carta);

void embaralhar_cartas(Baralho* pont_baralho);

Carta pegar_carta(Baralho* pont_baralho);  //Puxa carta de cima da pilha

Baralho *iniciar_baralho_jogo();  //Chama todas as funções e entrega o baralho pronto

void empilhar_carta_baralho(Baralho *pont_baralho, Carta carta_empilhar);


