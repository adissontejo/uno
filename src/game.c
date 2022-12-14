#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/cards.h"

//Variáveis globais

//Carta atual da mesa
char* tableCard;
//Naipe atual da mesa
char* tableSymbol;

/*Função para pegar o naipe da carta que mais aparece na mão de cartas
  Input: void
  Output: char* symbol
*/
char* getBestSymbol() {
  const char symbols[4][4] = { "♥", "♦", "♣", "♠" };

  char* card;
  char* cardSymbol;
  int qtdSymbols[4];
  int max = 0;

  memset(qtdSymbols, 0, sizeof(qtdSymbols));
    
  for(int i = 0; i < qtCards; i++){

    // Guarda o naipe da carta obtido com a função getCardSymbol
    cardSymbol = getCardSymbol(cards[i]);

    // Verifica se a carta na posição [i][0] é diferente de 'C' e 'A'
    if(cards[i][0] != 'C' && cards[i][0] != 'A'){      

      /* Realiza a comparação do naipe obtido da carta com os 4 naipes do barralho 
        e incrementa a quantidade quando a condição for verdadeira
      */      
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

  /* Percorre o vetor da quantidade de naipes verificando quem aparaceu mais
    e guardar o valor do naipe
  */
  for(int j = 0; j < 4; j++){
    if(qtdSymbols[j] >= max){
      max = qtdSymbols[j];

      int t = (int)strlen(symbols[j]);
      symbol = calloc(t + 1, sizeof(char));
      strcpy(symbol, symbols[j]);
    }
  }

  // Retorna o naipe que apareceu com mais frequência
  return symbol;
}

/* Função que verifica a prioridade da carta e executa ações baseadas nisso
   Input: void
   Output: void
*/
void playTurn() {
  /*
    Define a prioridade da carta escolhida com o valor inicial zero
    e a posição da carta escolhida com o valor inicial -1
  */
  int priority = 0, cardIndex = -1;

  // Percorre as cartas do baralho e analisa cada carta
  for (int i = 0; i < qtCards; i++) {
    // Pega o naipe da carta atual
    char* cardSymbol = getCardSymbol(cards[i]);

    // Caso a carta atual não seja A ou C
    if (cards[i][0] != 'A' && cards[i][0] != 'C') {
      // Caso a carta diferente de A e diferente de C tenha o mesmo naipe
      // que o naipe atual da mesa e a prioridade da carta escolhida do momento
      // não seja maior que 4
      if (strcmp(cardSymbol, tableSymbol) == 0 && priority <= 4) {
        // Caso a prioridade seja igual a 4, tem-se que o critério de desempate
        // é a posição do char da carta na tabela ascii, priorizando assim as cartas
        // de ação
        // V > R > D > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2 > 1
        if (priority != 4 || cardIndex == -1 || cards[i][0] > cards[cardIndex][0]) {
          // Substitui a carta escolhida pela carta atual e coloca 4 como valor da prioridade
          // dessa carta
          cardIndex = i;
          priority = 4;
        }
      }
      // Caso o naipe da carta seja diferente da atual da mesa porém a letra ou o número
      // seja o mesmo
      else if (cards[i][0] == tableCard[0] && priority <= 3) {
        // Caso a prioridade seja igual a 3, tem-se que o critério de desempate
        // é a posição do char da carta na tabela ascii, priorizando assim as cartas
        // de ação
        // V > R > D > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2 > 1
        if (priority != 3 || cardIndex == -1 || cards[i][0] > cards[cardIndex][0]) {
          // Substitui a carta escolhida pela carta atual e coloca 3 como valor da prioridade
          // dessa carta
          cardIndex = i;
          priority = 3;
        }
      }
    }
    // Caso a carta seja do tipo C e a prioridade da carta escolhida do momento seja menor
    // que 2
    else if (cards[i][0] == 'C' && priority < 2) {
      // Substitui a carta escolhida pela carta atual e coloca 2 como valor da prioridade
      // dessa carta
      cardIndex = i;
      priority = 2;
    } 
    // Caso a carta seja do tipo A e a prioridade da carta escolhida do momento seja menor
    // que 1
    else if (priority < 1) {
      // Substitui a carta escolhida pela carta atual e coloca 1 como valor da prioridade
      // dessa carta
      cardIndex = i;
      priority = 1;
    }
  }  

  // Se não tiver sido encontrada nenhuma carta que possa ser jogada
  if (cardIndex == -1) {
    buyCards(1); // Compra uma carta
  } else {
    // Atualiza a carta atual da mesa com o valor da carta escolhida
    tableCard = calloc(strlen(cards[cardIndex]), sizeof(char));

    strcpy(tableCard, cards[cardIndex]);
 
    // Caso a carta escolhida seja A ou C
    if (tableCard[0] == 'A' || tableCard[0] == 'C') {
      // Atualiza o naipe atual da mesa através da escolha de um naipe e descarta a carta
      // junto com o símbolo escolhido de informação
      tableSymbol = getBestSymbol();

      discardCard(tableCard, tableSymbol);
    }
    // Caso a carta escolhida não seja A nem C
    else {
      // Atualiza o naipe atual da mesa pegando o naipe da carta escolhida e descarta a carta
      tableSymbol = getCardSymbol(tableCard);

      discardCard(tableCard);
    }
  }
}
