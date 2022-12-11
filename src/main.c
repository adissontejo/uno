#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/players.h"
#include "../include/cards.h"
#include "../include/game.h"

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

int main() {
  char temp[MAX_LINE];
  char my_id[MAX_ID_SIZE];

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  readPlayers();

  scanf("YOU %s\n", my_id);

  readCards();

  scanf("TABLE %s\n", temp);

  tableCard = calloc(strlen(temp) + 1, sizeof(char));
  tableSymbol = getCardSymbol(temp);
  strcpy(tableCard, temp);

  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];

  int qtBuy = 0;

  while(1) {
    while (1) {
      scanf("%s %[^\n]", action, complement);

      if (strcmp(action, "TURN") == 0 && strcmp(complement, my_id) == 0) {
        break;
      }

      qtBuy = 0;

      if (strcmp(action, "DISCARD") == 0) {
        if (complement[0] == 'V') {
          qtBuy = 2;
        } else if (complement[0] == 'C') {
          qtBuy = 4;
        }

        if (complement[0] == 'A' || complement[0] == 'C') {
          char* split = strtok(complement, " ");

          tableCard = calloc(strlen(split) + 1, sizeof(char));

          strcpy(tableCard, split);

          split = strtok(NULL, " ");

          tableSymbol = calloc(strlen(split) + 1, sizeof(char));

          strcpy(tableSymbol, split);
        } else {
          tableCard = calloc(strlen(complement) + 1, sizeof(char));

          strcpy(tableCard, complement);

          tableSymbol = getCardSymbol(tableCard);
        }
      }
    }
    
    if (qtBuy != 0) {
      buyCards(qtBuy);

      continue;
    }

    playTurn();
  }

  return 0;
}