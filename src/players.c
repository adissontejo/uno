#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/players.h"

//Variáveis globais

//Quantidade de jogadores na partida
int qtPlayers;
//Lista de strings dos ids dos bots
char** players;

/* Função que realiza a leitura dos ids dos bots que estão jogando
   Input: void
   Output: void
*/
void readPlayers() {
  // Recebe a lista com os ids dos bots
  char* playerList;

  // Leitura dos ids dos bots
  scanf("PLAYERS %m[^\n]\n", &playerList);

  char* player; 

  qtPlayers = 0;

  // Quebra a string playerList em pedaços, separados por espaço
  player = strtok(playerList, " ");

  // Executa enquanto o pedaço da string player for diferente de null
  while (player != NULL) {

    if (qtPlayers == 0) {
      // Aloca o array de players na memória
      players = malloc(sizeof(char*));
    } else {
      // Realoca o array de players de acordo com a quantidade de jogadores
      players = realloc(players, (qtPlayers + 1)*sizeof(char*));
    }

    // Aloca último player de acordo com o tamanho de player
    players[qtPlayers] = calloc(strlen(player) + 1, sizeof(char));

    // Preenche o array de players realizando a cópia da String player para players[qtdPlayers]
    strcpy(players[qtPlayers], player);

    qtPlayers++;

    // Continua quebrando a string playerList passada na primeira chamada da função strtok
    player = strtok(NULL, " ");
  }
}