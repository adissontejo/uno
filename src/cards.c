#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int qtCards;
char** cards;

void readCards() {
  char *temp;
  char *card;
  
  qtCards = 0;

  cards = calloc(7, sizeof(char*));

  scanf("HAND %m[^\n]\n", &temp);

  card = strtok(temp, " ");

  while(card != NULL){
    if(card[0] != '[' && card[0] != ']'){
      int tam = (int)strlen(card);

      cards[qtCards] = calloc(tam, sizeof(char));

      strcpy(cards[qtCards], card);

      qtCards++;
    }
    
    card = strtok(NULL, " ");
  }
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

/*
Rodrigo

Função: remover carta específica da lista de cartas

Exemplo de entrada (parâmetro da função):
4♥

Exemplo de saída (printf):
DISCARD 4♥\n

Mover todas as cartas à direita da descartada uma posição à esquerda
Realocar tamanho da lista de cartas
Diminuir valor de qtCards
*/

void discardCard(char* card) {

}