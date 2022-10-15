#ifndef CARD_HEADER
#define CARD_HEADER

#include<stdint.h>
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_NAME 24
#define MIN_NAME 20
#define DATE_LENGTH 5
#define MAX_PAN 19
#define MIN_PAN 16
typedef enum EN_cardError_t{
CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

typedef struct ST_cardData_t{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;


EN_cardError_t getCardHolderName(ST_cardData_t *cardData);

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);

EN_cardError_t getCardPAN(ST_cardData_t *cardData);

static EN_cardError_t dateFormatCheck(uint8_t *cardExpiryDate);

//test functions
void getCardHolderNameTest(void);
void testFormat(ST_cardData_t *cardData,EN_cardError_t (* func)(ST_cardData_t *),void *print,uint8_t testcaseNumber);
void getCardExpiryDateTest (void);
void expirationDateFormat(ST_cardData_t *cardData,uint8_t testcaseNumber);
void getCardPANTest (void);
#endif 