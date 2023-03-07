#ifndef __CARD_FILE_H__
#define __CARD_FILE_H__
int saveCard(const Card* pcard, const char* pPath);
int readCard(Card *pCard, const char *pPath);
Card praseCard(char *pBuf);
int getCardCount(const char *pPath);
#endif