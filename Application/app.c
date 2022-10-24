
#include"app.h"

EN_PAYMENT_STATE_t state;
EN_PAYMENT_STATE_t nextState;

void appInit(){
   state = CARD; 
}
void appStart(void){
ST_terminalData_t termData;
ST_cardData_t cardData;
ST_transaction_t transData;
// get date from the user

switch (state)
{
case CARD:
    getCardHolderName(&cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    nextState = TERMINAL;
        break;
case TERMINAL:
    if(getTransactionDate(&termData) == WRONG_DATE){
        nextState = CARD;
    }
    else if(isCardExpired(&cardData,&termData)==EXPIRED_CARD){
        nextState = CARD;
    }
    else if(getTransactionAmount(&termData) == INVALID_AMOUNT){
        nextState == CARD;
    }
    else if(setMaxAmount(&termData,4000) == INVALID_MAX_AMOUNT){
        nextState == CARD;
    }
    else if(isBelowMaxAmount(&termData) == EXCEED_MAX_AMOUNT){
        nextState == CARD;
    }
    else{
        nextState = SERVER;
    }
    break;
case SERVER:
    recieveTransactionData(&transData);
    nextState = CARD;
    break;
default:
    break;
}

state  =  nextState;

}