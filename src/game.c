#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/cards.h"

char* tableCard;
char* tableSymbol;
const char symbols[4][4] = { "♥", "♦", "♣", "♠" };
/*
Vanessa

Função: retornar o símbolo mais presente no baralho do bot (cards)

Exemplo de retorno:
♥

Ignorar cartas A e C e usar função getCardSymbol para auxiliar
*/

char* getBestSymbol() {
    char* card;
    char* cardSymbol;
    int qtdSymbols[4];
    int max = 0;
    
    for(int i = 0; i < qtCards; i++){
        int tam = (int)strlen(cards[i]);

        cardSymbol = calloc(tam, sizeof(char*));

        cardSymbol = getCardSymbol(cards[i]);

        for(int j = 0; j < tam; j++){
            if(cards[0][j] != 'C' && cards[0][j] != 'A'){
                
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
    }

    char* symbol; 
    for(int j = 0; j < 4; j++){
        if(qtdSymbols[j] >= max){
            max = qtdSymbols[j];
  
            int t = (int)strlen(symbols[j]);
            symbol = calloc(t, sizeof(char*));
            symbol = symbols[j];
        }
    }

    return symbol;
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
