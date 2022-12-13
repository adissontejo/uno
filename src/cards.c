#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis globais

// Quantidade de cartas na mão
int qtCards;
// Array de cartas na mão
char** cards;

// Função para ler as cartas na mão
// Input: void
// Output: void
void readCards() {
  // Inicializa as variáveis
  char *temp;
  char *card;
  
  qtCards = 0;

  // Aloca espaço para as 7 cartas a serem recebidas
  cards = calloc(7, sizeof(char*));

  // Lê as cartas que o gerenciador envia
  scanf("HAND %m[^\n]\n", &temp);

  // Separa as cartas
  card = strtok(temp, " ");

  // Percorre as cartas separadas e adiciona ao
  // array de cartas na mão ignorando os colchetes
  // e incrementando a quantidade de cartas na mão
  while(card != NULL){
    if(card[0] != '[' && card[0] != ']'){
      int tam = (int)strlen(card);

      cards[qtCards] = calloc(tam + 1, sizeof(char));

      strcpy(cards[qtCards], card);

      qtCards++;
    }
    
    card = strtok(NULL, " ");
  }
}

// Função para comprar cartas
// Input: int quantidade
// Output: void
void buyCards(int qt) {
  // Imprime o comando para comprar cartas
  printf("BUY %d\n", qt);

  // Realoca o array de cartas na mão para
  // a quantidade de cartas + a quantidade de cartas compradas
  cards = realloc(cards, sizeof(char*)*(qtCards + qt));

  // Lê as cartas compradas
  for (int i = 0; i < qt; i++) {
    scanf("\n%m[^\n]", &cards[qtCards + i]);
  }

  // Incrementa a quantidade de cartas na mão
  qtCards += qt;
}

// Função para obter o símbolo de uma carta
// Input: char* carta
// Output: char* símbolo
char* getCardSymbol(char* card) {
  // Aloca espaço para o símbolo
  char* symbol;
  int cardLength = (int)strlen(card);
  symbol = calloc(cardLength, sizeof(char));
  
  // Copia o símbolo da carta para a variável symbol
  // Ou seja, o conteúdo da carta a partir do índice 1 (que é a letra)
  for (int i = 1; i < cardLength; i++) {
    symbol[i-1] = card[i];
  }

  // Adiciona o caractere de fim de string
  symbol[cardLength - 1] = '\0';
  
  return symbol;
}

// Função para descartar uma carta,
// gerenciando o array de cartas na mão
// Input: char* carta, char* símbolo
// Output: void
void discardCard(char* card, char* symbol) {
  int discardedCardIndex;
    
  // Percorre o array de cartas na mão para
  // obter o índice da carta a ser descartada
  for (int i = 0; i < qtCards; i++) {
    if (strcmp(cards[i], card) == 0) {
      discardedCardIndex = i;
    }
  }
  
  // Percorre o array de cartas na mão
  // a partir do índice da carta a ser descartada
  // e copia o conteúdo da carta seguinte para a carta atual
  // para retirar a carta descartada do array
  for (int i = discardedCardIndex; i < qtCards-1; i++) {
    strcpy(cards[i], cards[i + 1]);
  }
  
  // Decrementa a quantidade de cartas na mão
  qtCards--;
  // Libera a memória da carta descartada
  free(cards[qtCards]);
  
  // Realoca o array de cartas na mão
  cards = realloc(cards, sizeof(char*) * qtCards);
  
  // Imprime o comando para descartar a carta
  // se a carta for um Coringa ou um Ás, imprimirá
  // o símbolo escolhido a ser mudado
  if (card[0] == 'A' || card[0] == 'C') {
    printf("DISCARD %s %s\n", card, symbol);
  } else {
    printf("DISCARD %s\n", card);
  }
}