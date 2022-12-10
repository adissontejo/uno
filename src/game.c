#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/cards.h"

char* tableCard;
char* tableSymbol;

/*
Vanessa

Função: retornar o símbolo mais presente no baralho do bot (cards)

Exemplo de retorno:
♥

Ignorar cartas A e C e usar função getCardSymbol para auxiliar
*/

char* getBestSymbol() {
  return "♥";
}

/*
Ádisson

Função: discartar carta ou então comprar uma carta

Implementar lógica de prioridade de cartas e comprar uma carta caso não possua nenhuma carta disponível para jogar
*/

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

    discardCard(tableCard);
 
    if (tableCard[0] == 'A' || tableCard[0] == 'C') {
      tableSymbol = getBestSymbol();
    } else {
      tableSymbol = getCardSymbol(tableCard);
    }
  }
}
