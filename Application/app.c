
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
    if(getCardHolderName(&cardData) == WRONG_NAME){
        nextState = END;
            printf("%d h\n\n",nextState); 
    }
    if( (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)){
        nextState = END;
            printf("%d hhh\n",nextState); 
    }
    if(  getCardPAN(&cardData) ==WRONG_PAN ){
        nextState = END;
            printf("%d hhhhh\n\n",nextState); 
    }
  if(nextState != END)
     nextState = TERMINAL;


    break;
case TERMINAL:
    if(getTransactionDate(&termData) == WRONG_DATE){
        nextState = END;
    }
    if(isCardExpired(&cardData,&termData)==EXPIRED_CARD){
        nextState = END;
    }
     if(getTransactionAmount(&termData) == INVALID_AMOUNT){
        nextState == END;
    }
    if(setMaxAmount(&termData,4000) == INVALID_MAX_AMOUNT){
        nextState == END;
    }
    if(isBelowMaxAmount(&termData) == EXCEED_MAX_AMOUNT){
        nextState == END;
    }
    if(nextState != END){
        nextState = SERVER;
    }
    break;
case SERVER:
    recieveTransactionData(&transData);
    nextState = END;
    break;
default:
    break;
}

state  =  nextState;

}

EN_PAYMENT_STATE_t currentState(){
    return state;
}