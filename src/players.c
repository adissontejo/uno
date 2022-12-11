#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/players.h"

int qtPlayers;
char** players;

void readPlayers() {
  char* playerList;

  scanf("PLAYERS %m[^\n]\n", &playerList);

  char* player; 

  qtPlayers = 0;

  player = strtok(playerList, " ");

  while (player != NULL) {
    if (qtPlayers == 0) {
      players = malloc(sizeof(char*));
    } else {
      players = realloc(players, (qtPlayers + 1)*sizeof(char*));
    }

    players[qtPlayers] = calloc(strlen(player) + 1, sizeof(char));

    strcpy(players[qtPlayers], player);

    qtPlayers++;

    player = strtok(NULL, " ");
  }
}