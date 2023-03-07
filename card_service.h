#ifndef __CARD_FILE_H__
#define __CARD_FILE_H__
int initCardList();
int addCard(Card card);
Card *queryCard(const char *pName);
void releaseCardList();
Card *queryCards(const char *pName, int *pIndex);
int getCard();
#endif