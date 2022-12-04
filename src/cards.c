#include <stdio.h>

int qtCards;
char** cards;

/*
Vanessa

Função: ler cartas iniciais do jogo

Exemplo de entrada (scanf):
CARDS [ A♥ A♥ A♥ A♥ A♥ A♥ A♥ ]

Tratar colcehetes, alocar memória em cards, incrementar qtCards.
*/
void readCards() {

}

/*
Ádisson

Função: comprar cartas durante o jogo

Exemplo de comando (printf):
BUY 4

Exemplo de resposta (scanf):
A♥
A♥
A♥
A♥

Realocar cards, adicionar cartas novas na lista, incrementar qtCards
*/
void buyCards(int qt) {

}

/*
Rodrigo

Função: retornar símbolo de carta passada como parâmetro

Exemplo de entrada (parâmetro da função):
A♥

Exemplo de saída (retorno da função):
♥

Remover primeiro caractére da string (atenção para não alterar a string original)
*/
char* getCardSymbol(char* card) {
  char* symbol;
  int cardLength = (int)strlen(card);
  symbol = calloc(cardLength-1, sizeof(char));
  
  for (int i = 1; i < cardLength; i++) {
      symbol[i-1] = card[i];
  }
  
  return symbol;
}

void discardCard() {

}