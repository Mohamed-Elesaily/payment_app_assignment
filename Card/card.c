#include "card.h"
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    size_t card_length;
    EN_cardError_t cardError;

    card_length = strlen(cardData->cardHolderName);
    if( (card_length <= MAX_NAME) && (card_length >= MIN_NAME)){
        cardError = CARD_OK;
    }
    else{
        cardError = WRONG_NAME;
    }

    return cardError;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    EN_cardError_t cardError;

    cardError = dateFormatCheck(cardData->cardExpirationDate);
    return cardError;


}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    EN_cardError_t cardError;
    uint8_t number;
   
    size_t PAN_l = strlen(cardData->primaryAccountNumber); 
    if((PAN_l>=MIN_PAN) && (PAN_l<=MAX_PAN)) cardError = CARD_OK;
    else cardError = WRONG_PAN;
    for(int i=0;i<PAN_l;i++){
        if(isalpha(cardData->primaryAccountNumber[i])){
            cardError = WRONG_PAN;
            break;
        }
    }
    return cardError;
}

EN_cardError_t dateFormatCheck(uint8_t *cardExpiryDate){
    EN_cardError_t cardError = CARD_OK;
    size_t exp_l;    
    exp_l = strlen(cardExpiryDate);
    if(exp_l != DATE_LENGTH){
        cardError = WRONG_EXP_DATE;
    }
    for(int i=0;i< DATE_LENGTH;i++){
       
       if(i==2){
        if(cardExpiryDate[i] != '/'){
            cardError = WRONG_EXP_DATE;
            break;
        }
           
        
       }
       else if(isalpha(cardExpiryDate[i])){
          cardError = WRONG_EXP_DATE;
          break;     
       }

     
       
    }
  return cardError;
}


void getCardHolderNameTest(void){
    ST_cardData_t *cardData;
    cardData = (ST_cardData_t *) calloc(1,sizeof(ST_cardData_t));
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: getCardHolderName\n");

    strcpy(cardData->cardHolderName,"Mohamed Yasser Ahmed Hanafy");
    testFormat(cardData,getCardHolderName,cardData->cardHolderName,1);

    strcpy(cardData->cardHolderName,"");
    testFormat(cardData,getCardHolderName,cardData->cardHolderName,2);

    strcpy(cardData->cardHolderName,"M");
    testFormat(cardData,getCardHolderName,cardData->cardHolderName,3);

    strcpy(cardData->cardHolderName,"Mohamed Yasser dsafdsfff");
    testFormat(cardData,getCardHolderName,cardData->cardHolderName,4);

    strcpy(cardData->cardHolderName,"Mohamed Yasser dsaff");
    testFormat(cardData,getCardHolderName,cardData->cardHolderName,5);

    strcpy(cardData->cardHolderName,"Mohamed Yasser dsafff");
    testFormat(cardData,getCardHolderName,cardData->cardHolderName,6);

    free(cardData);
}
void getCardExpiryDateTest (void){
    ST_cardData_t *cardData;
    cardData = (ST_cardData_t *) calloc(1,sizeof(ST_cardData_t));
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: getCardExpiryDate\n");

    strcpy(cardData->cardExpirationDate,"05/25");
    testFormat(cardData,getCardExpiryDate,cardData->cardExpirationDate,1);
    
    strcpy(cardData->cardExpirationDate,"05:25");
    testFormat(cardData,getCardExpiryDate,cardData->cardExpirationDate,2);

    strcpy(cardData->cardExpirationDate,"aa/25");
    testFormat(cardData,getCardExpiryDate,cardData->cardExpirationDate,3);

    strcpy(cardData->cardExpirationDate,"/25");
    testFormat(cardData,getCardExpiryDate,cardData->cardExpirationDate,4);

    strcpy(cardData->cardExpirationDate,"05/");
    testFormat(cardData,getCardExpiryDate,cardData->cardExpirationDate,5);

    free(cardData);
}
void getCardPANTest (void){
    ST_cardData_t *cardData;
    cardData = (ST_cardData_t *) calloc(1,sizeof(ST_cardData_t));
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: getCardPAN\n");

    strcpy(cardData->primaryAccountNumber,"123456789123456789");
    testFormat(cardData,getCardPAN,cardData->primaryAccountNumber,1);

    strcpy(cardData->primaryAccountNumber,"1234567891234568");
    testFormat(cardData,getCardPAN,cardData->primaryAccountNumber,2);

    strcpy(cardData->primaryAccountNumber,"123456789dasd345");
    testFormat(cardData,getCardPAN,cardData->primaryAccountNumber,3);

    free(cardData);
}


void testFormat(ST_cardData_t *cardData,EN_cardError_t (* func)(ST_cardData_t *),void *print,uint8_t testcaseNumber){
    printf("Test Case %d:\n",testcaseNumber);
    printf("Input Data:");
    puts(print);
    if((*func)(cardData) == CARD_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }


}