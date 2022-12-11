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

      cards[qtCards] = calloc(tam + 1, sizeof(char));

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
  symbol = calloc(cardLength, sizeof(char));
  
  for (int i = 1; i < cardLength; i++) {
    symbol[i-1] = card[i];
  }

  symbol[cardLength - 1] = '\0';
  
  return symbol;
}

void discardCard(char* card, char* symbol) {
  int discardedCardIndex;
    
  for (int i = 0; i < qtCards; i++) {
    if (strcmp(cards[i], card) == 0) {
      discardedCardIndex = i;
    }
  }
    
  for (int i = discardedCardIndex; i < qtCards-1; i++) {
    strcpy(cards[i], cards[i + 1]);
  }
    
  qtCards--;

  free(cards[qtCards]);
    
  cards = realloc(cards, sizeof(char*) * qtCards);
    
  if (card[0] == 'A' || card[0] == 'C') {
    printf("DISCARD %s %s\n", card, symbol);
  } else {
    printf("DISCARD %s\n", card);
  }
}