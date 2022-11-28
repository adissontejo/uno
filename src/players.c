#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/players.h"

int qtPlayers;
char** players;

void addPlayers(char* playerList) {
  char* player; 

  qtPlayers = 0;

  player = strtok(playerList, " ");

  while (player != NULL) {
    if (qtPlayers == 0) {
      players = malloc(sizeof(char*));
    } else {
      players = realloc(players, (qtPlayers + 1)*sizeof(char*));
    }

    players[qtPlayers] = malloc(sizeof(char)*(strlen(player) + 1));

    strcpy(players[qtPlayers], player);

    qtPlayers++;

    player = strtok(NULL, " ");
  }
}