#ifndef CARDS_H

extern int qtCards;
extern char** cards;

extern void readCards();
extern void buyCards(int qt);
extern char* getCardSymbol(char* card);
extern void discardCard();

#endif