#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/cards.h"

char* tableCard;
char* tableSymbol;

char* getBestSymbol() {
  const char symbols[4][4] = { "♥", "♦", "♣", "♠" };

  char* card;
  char* cardSymbol;
  int qtdSymbols[4];
  int max = 0;

  memset(qtdSymbols, 0, sizeof(qtdSymbols));
    
  for(int i = 0; i < qtCards; i++){
    int tam = (int)strlen(cards[i]);

    cardSymbol = getCardSymbol(cards[i]);

    if(cards[i][0] != 'C' && cards[i][0] != 'A'){            
      if(strcmp(cardSymbol, symbols[0]) == 0){
        qtdSymbols[0]++;
      } else if(strcmp(cardSymbol, symbols[1]) == 0){
        qtdSymbols[1]++;
      } else if(strcmp(cardSymbol, symbols[2]) == 0){
        qtdSymbols[2]++;
      } else if(strcmp(cardSymbol, symbols[3]) == 0){
        qtdSymbols[3]++;
      }
    }
  }

  char* symbol;

  for(int j = 0; j < 4; j++){
    if(qtdSymbols[j] >= max){
      max = qtdSymbols[j];

      int t = (int)strlen(symbols[j]);
      symbol = calloc(t + 1, sizeof(char));
      strcpy(symbol, symbols[j]);
    }
  }

  return symbol;
}

void playTurn() {
  int priority = 0, cardIndex = -1;

  for (int i = 0; i < qtCards; i++) {
    char* cardSymbol = getCardSymbol(cards[i]);

    if (cards[i][0] != 'A' && cards[i][0] != 'C') {
      if (strcmp(cardSymbol, tableSymbol) == 0 && priority <= 4) {
        if (priority != 4 || cardIndex == -1 || cards[i][0] > cards[cardIndex][0]) {
          cardIndex = i;
          priority = 4;
        }
      } else if (cards[i][0] == tableCard[0] && priority <= 3) {
        if (priority != 3 || cardIndex == -1 || cards[i][0] > cards[cardIndex][0]) {
          cardIndex = i;
          priority = 3;
        }
      }
    } else if (cards[i][0] == 'C' && priority < 2) {
      cardIndex = i;
      priority = 2;
    } else if (priority < 1) {
      cardIndex = i;
      priority = 1;
    }
  }  

  if (cardIndex == -1) {
    buyCards(1);
  } else {
    tableCard = calloc(strlen(cards[cardIndex]), sizeof(char));

    strcpy(tableCard, cards[cardIndex]);
 
    if (tableCard[0] == 'A' || tableCard[0] == 'C') {
      tableSymbol = getBestSymbol();

      discardCard(tableCard, tableSymbol);
    } else {
      tableSymbol = getCardSymbol(tableCard);

      discardCard(tableCard);
    }
  }
}
