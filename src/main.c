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

  // Chamada a função que realiza a leitura dos ids dos bots que estão jogando
  readPlayers();

  // Ler o id do nosso bot
  scanf("YOU %s\n", my_id);

  // Chamada a função que realiza a leitura das cartas do nosso bot 
  readCards();

  // Realiza a leitura da carta sobre a mesa
  scanf("TABLE %s\n", temp);

  // Aloca o tamanho da carta sobre a mesa
  tableCard = calloc(strlen(temp) + 1, sizeof(char));
  // Guarda o símbolo da carta recebida
  tableSymbol = getCardSymbol(temp);
  strcpy(tableCard, temp);

  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];

  int qtBuy = 0;

  // Executa enquanto as condições de parada do jogo não for atingida
  while(1) {
    while (1) {
      // Ler a ação e complemento da vez
      scanf("%s %[^\n]", action, complement);

      if (strcmp(action, "TURN") == 0 && strcmp(complement, my_id) == 0) {
        break;
      }

      qtBuy = 0;

      // Verifica se a ação da vez é DISCARD
      if (strcmp(action, "DISCARD") == 0) {
        //  Incrementa a quantidade de cartas a ser comprada caso complement[0] for igual a V ou C
        if (complement[0] == 'V') {
          qtBuy = 2;
        } else if (complement[0] == 'C') {
          qtBuy = 4;
        }

        // Verifica se complement[0] é igual a A ou C
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
    
    // Se a quantidade de cartas compradas for diferente de zero, a função comprar cartas é chamada
    if (qtBuy != 0) {
      buyCards(qtBuy);

      continue;
    }

    playTurn();
  }

  return 0;
}