
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
    printf("\nPlease Enter Card PAN:");
   // fgets(cardData.primaryAccountNumber,20*sizeof(uint8_t),stdin);
    gets(cardData.primaryAccountNumber); 
    printf("Please Enter card name:");
   // fgets(cardData.cardHolderName,25*sizeof(uint8_t),stdin);
    gets(cardData.cardHolderName); 
    printf("Please Enter Expiration date:");
   // fgets(cardData.cardExpirationDate,6*sizeof(uint8_t),stdin);
    gets(cardData.cardExpirationDate); 
    if(getCardHolderName(&cardData) == WRONG_NAME){
        printf("Wrong name \n");
        nextState = END;
      
    }
    else if( (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)){
        printf("Wrong expiration date \n");
        nextState = END;
         
    }
   else if(  getCardPAN(&cardData) ==WRONG_PAN ){
        printf("Wrong PAN number\n");
        nextState = END;  
    }
  else{
    printf("CARD is OK\n");
    nextState = TERMINAL;
  }
     

    break;
case TERMINAL:

    printf("please entre transaction date:");
    //fgets(termData.transactionDate,11*sizeof(uint8_t),stdin);   
    gets(termData.transactionDate);
    printf("please entre transfer amount:");
    scanf("%f",&termData.transAmount);
    if(getTransactionDate(&termData) == WRONG_DATE){
        printf("Wrong Date\n");
        nextState = END;
    }
    else if(isCardExpired(&cardData,&termData)==EXPIRED_CARD){
        printf("Card is expired\n");
        nextState = END;
    }
    else if(getTransactionAmount(&termData) == INVALID_AMOUNT){
        printf("Invaild account\n");
        nextState == END;
    }
    else if(setMaxAmount(&termData,4000) == INVALID_MAX_AMOUNT){
        printf("Invaild max amount\n");
        nextState == END;
    }
    else if(isBelowMaxAmount(&termData) == EXCEED_MAX_AMOUNT){
        printf("Exceed max amount\n");
        printf("%d \n",state);
        nextState == END;
    }
    else{
        nextState = SERVER;
    }
    break;
case SERVER:
    transData.terminalData = termData;
    transData.cardHolderData = cardData;
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