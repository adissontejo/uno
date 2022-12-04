#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int qtCards;
char** cards;

/*
Vanessa

Função: ler cartas iniciais do jogo

Exemplo de entrada (scanf):
HAND [ A♥ A♥ A♥ A♥ A♥ A♥ A♥ ]

Tratar colcehetes, alocar memória em cards, incrementar qtCards.
*/
void readCards() {

}

void buyCards(int qt) {
  printf("BUY %d\n", qt);

  cards = realloc(cards, sizeof(char*)*(qtCards + qt));

  for (int i = 0; i < qt; i++) {
    scanf("\n%m[^\n]", &cards[qtCards + i]);
  }

  qtCards += qt;
}

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