Carta* iniciar_cartas();  /*Essa fun��o inicia o baralho do 1 ao 7 e a cor mais fraca at� a mais forte*/

Baralho* colocar_cartas_baralho(Carta* pont_carta);

void embaralhar_cartas(Baralho* pont_baralho);

Carta pegar_carta(Baralho* pont_baralho);  //Puxa carta de cima da pilha

Baralho *iniciar_baralho_jogo();  //Chama todas as fun��es e entrega o baralho pronto

void empilhar_carta_baralho(Baralho *pont_baralho, Carta carta_empilhar);


