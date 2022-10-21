#include"terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    EN_terminalError_t terminalError = TERMINAL_OK;
    size_t dateSize;
    //fgets(termData->transactionDate,11*sizeof(uint8_t),stdin);
    dateSize = strlen(termData->transactionDate);
    
    if(dateSize !=10) terminalError = WRONG_DATE;
    
    if((termData->transactionDate[5] != '/') && (termData->transactionDate[2] != '/')){
    terminalError = WRONG_DATE;
    }
        
    for(int i=0;i<dateSize;i++){
        if((i == 2) ||( i==5))continue;

        if(isalpha(termData->transactionDate[i])){
           terminalError = WRONG_DATE;
           break;
        }

    }

    return terminalError;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){

    uint8_t transactionYear = atoi((char *)(termData->transactionDate + 8));
    uint8_t transactionMonth = atoi((char *)(termData->transactionDate + 3));
    uint8_t expiredYear = atoi((char *)(cardData->cardExpirationDate + 3));
    uint8_t expiredMonth = atoi((char *)(cardData->cardExpirationDate));

    if(transactionYear>expiredYear) return EXPIRED_CARD;

    if((transactionYear == expiredYear)&& (transactionMonth > expiredMonth)) return EXPIRED_CARD;

    return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    
   // scanf("please entre transaction amount:%f",&termData->transAmount);
    if(termData->transAmount  <= 0) return INVALID_AMOUNT;
    return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if(termData->transAmount > termData->maxTransAmount) return EXCEED_MAX_AMOUNT;
    return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount){

    if(maxAmount <= 0) return INVALID_MAX_AMOUNT;
    termData->maxTransAmount = maxAmount;
    return TERMINAL_OK;
}


void testFormatTerminal(ST_terminalData_t *termData,EN_terminalError_t (* func)(ST_terminalData_t *),void *print,uint8_t testcaseNumber){
    printf("Test Case %d:\n",testcaseNumber);
    printf("Input Data:");
    puts(print);
    if((*func)(termData) == TERMINAL_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }


}
 
void getTransactionDateTest(void){

    ST_terminalData_t *termdata = calloc(1,sizeof(ST_terminalData_t));
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: getTransactionDate\n");

    strcpy(termdata->transactionDate,"10/09/2022");
    testFormatTerminal(termdata,getTransactionDate,termdata->transactionDate,1);
    
    strcpy(termdata->transactionDate,"1/09/2022");
    testFormatTerminal(termdata,getTransactionDate,termdata->transactionDate,2);


    strcpy(termdata->transactionDate,"1\09/2022");
    testFormatTerminal(termdata,getTransactionDate,termdata->transactionDate,3);

    strcpy(termdata->transactionDate,"30/12/2030");
    testFormatTerminal(termdata,getTransactionDate,termdata->transactionDate,4);

    free(termdata);

}

void isCardExpriedTest(void){
    ST_terminalData_t *termdata = calloc(1,sizeof(ST_terminalData_t));
    ST_cardData_t *cardData = calloc(1,sizeof(ST_cardData_t));
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: isCardExpried\n");

    printf("Test Case %d:\n",1);
    strcpy(termdata->transactionDate,"20/10/2021"); 
    strcpy(cardData->cardExpirationDate,"05/23");
    printf("Input Data:\n");
    puts(termdata->transactionDate);
    printf("Input Data:\n");
    puts(cardData->cardExpirationDate);
    if(isCardExpired(cardData,termdata)== TERMINAL_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }



    printf("Test Case %d:\n",2);
    strcpy(termdata->transactionDate,"20/10/2021"); 
    strcpy(cardData->cardExpirationDate,"05/20");
    printf("Input Data:\n");
    puts(termdata->transactionDate);
    printf("Input Data:\n");
    puts(cardData->cardExpirationDate);
    if(isCardExpired(cardData,termdata)== TERMINAL_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }
    
       printf("Test Case %d:\n",3);
    strcpy(termdata->transactionDate,"20/10/2021"); 
    strcpy(cardData->cardExpirationDate,"12/21");
    printf("Input Data:\n");
    puts(termdata->transactionDate);
    printf("Input Data:\n");
    puts(cardData->cardExpirationDate);
    if(isCardExpired(cardData,termdata)== TERMINAL_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }
    
       printf("Test Case %d:\n",3);
    strcpy(termdata->transactionDate,"20/10/2021"); 
    strcpy(cardData->cardExpirationDate,"9/21");
    printf("Input Data:\n");
    puts(termdata->transactionDate);
    printf("Input Data:\n");
    puts(cardData->cardExpirationDate);
    if(isCardExpired(cardData,termdata)== TERMINAL_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }
    
    free(cardData);
    free(termdata);
}
void getTransactionAmountTest(void){
    ST_terminalData_t *termdata = calloc(1,sizeof(ST_terminalData_t));
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: getTransactionAmount\n");


    printf("Test Case %d:\n",1);
    termdata->transAmount = 0;
    printf("Input Data:%f\n",termdata->transAmount );
    if(getTransactionAmount(termdata)== TERMINAL_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }

    printf("Test Case %d:\n",2);
    termdata->transAmount = -1;
    printf("Input Data:%f\n",termdata->transAmount );
    if(getTransactionAmount(termdata)== TERMINAL_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }

        printf("Test Case %d:\n",2);
    termdata->transAmount = 1000;
    printf("Input Data:%f\n",termdata->transAmount );
    if(getTransactionAmount(termdata)== TERMINAL_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }

    free(termdata);
    

}
void setMaxAmountTest(void){
        ST_terminalData_t *termdata = calloc(1,sizeof(ST_terminalData_t));
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: setMaxAmount\n");


    printf("Test Case %d:\n",1);
    termdata->transAmount = 0;
    printf("Input Data:0\n" );
    if(setMaxAmount(termdata,0)== TERMINAL_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }

    printf("Test Case %d:\n",2);
    printf("Input Data:-1\n");
    if(setMaxAmount(termdata,-1)== TERMINAL_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }

        printf("Test Case %d:\n",2);

    printf("Input Data:1000\n");
    if(setMaxAmount(termdata,1000)== TERMINAL_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }

    free(termdata);
    

}
void isBelowMaxAmountTest(void){
    ST_terminalData_t *termdata = calloc(1,sizeof(ST_terminalData_t));
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: isBelowMaxAmount\n");
    
    termdata->maxTransAmount = 5000;
    printf("Input Data:%f\n",termdata->maxTransAmount );
    termdata->transAmount = 200;
    printf("Input Data:%f\n",termdata->transAmount );
    testFormatTerminal(termdata,isBelowMaxAmount,termdata,1);

    termdata->maxTransAmount = 50;
    printf("Input Data:%f\n",termdata->maxTransAmount );
    termdata->transAmount = 200;
    printf("Input Data:%f\n",termdata->transAmount );
    testFormatTerminal(termdata,isBelowMaxAmount,termdata,2);

    termdata->maxTransAmount = 200;
    printf("Input Data:%f\n",termdata->maxTransAmount );
    termdata->transAmount = 200;
    printf("Input Data:%f\n",termdata->transAmount );
    testFormatTerminal(termdata,isBelowMaxAmount,termdata,3);
}
int main(){
   // isCardExpriedTest();
isBelowMaxAmountTest();
}