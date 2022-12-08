#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/game.h"

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

char* getDiscardComplement(char* card) {
  if (card[0] != 'C' && card[0] != 'A') {
    return "";
  }

  char* bestSymbol = getBestSymbol();
  
  int complementLength = (int)strlen(bestSymbol) + 1;
  
  char* complement;
  complement = calloc(complementLength, sizeof(char));
  
  complement[0] = ' ';
  
  for (int i = 1; i < complementLength; i++) {
      complement[i] = bestSymbol[i-1];
  }
  
  return complement;
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
    int discardedCardIndex;
    
    for (int i = 0; i < qtCards; i++) {
        if (strcmp(cards[i], card) == 0) {
            discardedCardIndex = i;
        }
    }
    
    for (int i = discardedCardIndex; i < qtCards-1; i++) {
        cards[i] = cards[i+1];
    }
    
    qtCards--;
    
    cards = realloc(cards, sizeof(char*) * qtCards);

    char* discardComplement = getDiscardComplement(card);
    
    printf("DISCARD %s%s\n", card, discardComplement);
}