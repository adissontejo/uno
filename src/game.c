#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cards.h"
extern char* getCardSymbol();

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
    char* card;
    char* cardSymbol;
    int qtdSimbols[4];
    int max = 0;

    card = strtok(cards, " ");

    for(int i = 0; i < qtCards; i++){
        int tam = (int)strlen(card);

        cardSymbol = calloc(tam, sizeof(char*));

        cardSymbol = getCardSymbol(card);

        for(int j = 0; j < tam; j++){
            if(card[0] != 'C' && card[0] != 'A'){
                
                if(strcmp(cardSymbol, tableSymbol[0]) == 0){
                    qtdSimbols[0]++;
                } else if(strcmp(cardSymbol, tableSymbol[1]) == 0){
                    qtdSimbols[1]++;
                } else if(strcmp(cardSymbol, tableSymbol[2]) == 0){
                    qtdSimbols[2]++;
                } else if(strcmp(cardSymbol, tableSymbol[3]) == 0){
                    qtdSimbols[3]++;
                }
            }
        }
        card = strtok(NULL, " ");
    }

    for(int j = 0; j < 4; j++){
        if(qtdSymbols[j] >= max){
            max = qtdSymbols[j];

            char* symbol;   
            int t = (int)strlen(tableSymbol[j]);
            symbol = calloc(t, sizeof(char*));
            symbol = tableSymbol[j];
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

}
