#include"server.h"
static const char *transStateStringValue[] = {"APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR"};

ST_accountsDB_t accountsDB[] = {
    {2000.0, RUNNING, "8989374615436851"},
    {100000.0, BLOCKED, "5807007076043875"},
    {0.0, RUNNING, "9607007076043875"},
    {0.0, BLOCKED, "1234007076043875"},
    {100.0, RUNNING, "7894007076043875"}
};
ST_transaction_t transactions[255] = {0};

EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    EN_transState_t transState;
    ST_accountsDB_t accountRefrence;
    if(isValidAccount(&transData->cardHolderData,&accountRefrence) == ACCOUNT_NOT_FOUND){
        transState = FRAUD_CARD;
        printf("ACCOUNT_NOT_FOUND\n");
        }
    else if(isAmountAvailable(&transData->terminalData, &accountRefrence) == LOW_BALANCE){ 
        transState = DECLINED_INSUFFECIENT_FUND;
         printf("DECLINED_INSUFFECIENT_FUND\n");
        }
    else if(isBlockedAccount(&accountRefrence) == BLOCKED_ACCOUNT) {
        transState = DECLINED_STOLEN_CARD;
        printf("DECLINED_STOLEN_CARD\n");
        }
    else if(saveTransaction(transData) == SAVING_FAILED) {
        transState = INTERNAL_SERVER_ERROR;
        printf("INTERNAL_SERVER_ERROR\n");
        }
    else{
        transState = APPROVED;
        printf("APPROVED \n");
}
    if(transState == APPROVED){
        accountRefrence.balance = accountRefrence.balance - transData->terminalData.transAmount;
    } 
    return transState;
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
    size_t DB_length = sizeof(accountsDB)/sizeof(accountsDB[0]);
    EN_serverError_t serverError = ACCOUNT_NOT_FOUND;
    uint8_t index=0;
    for(int i=0;i<DB_length;i++){
    
        if(strcmp((accountsDB[i].primaryAccountNumber),cardData->primaryAccountNumber) == 0){
            serverError = SERVER_OK;   
            index = i;   
            break;
        }
     

    }
   *accountRefrence =  accountsDB[index];
    if(serverError == ACCOUNT_NOT_FOUND) accountRefrence = NULL;


    return serverError;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
if(accountRefrence->state == BLOCKED) return BLOCKED_ACCOUNT;

return SERVER_OK;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence){
    if(termData->transAmount <= accountRefrence->balance) return SERVER_OK;

    return LOW_BALANCE;
}
EN_serverError_t saveTransaction(ST_transaction_t *transData){
    static uint32_t sequence =0;
    sequence++;
    transData->transactionSequenceNumber = sequence;
    transactions[sequence-1] = *transData;

    listSavedTransactions();
    return SERVER_OK;
}
void listSavedTransactions(void){
   for(int i=0;i<255;i++){
    if(transactions[i].transactionSequenceNumber !=0){
        printf("Transaction Sequence Number: %d \n",(int)transactions[i].transactionSequenceNumber);
        printf("Transaction Amount: %f \n",transactions[i].terminalData.transAmount);
        printf("Transaction State:%s \n",transStateStringValue[transactions[i].transState]);
        printf("Terminal Max Amount:%f \n",transactions[i].terminalData.maxTransAmount);
        printf("Cardholder Name:");
        puts(transactions[i].cardHolderData.cardHolderName);
        printf("PAN:");
        puts(transactions[i].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date:");
        puts(transactions[i].cardHolderData.cardExpirationDate);
    }
   } 
  
}

void recieveTransactionDataTest(void){
    ST_transaction_t transData;

   
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: recieveTransactionData\n");
    
    printf("Test Case %d:\n",1);
   
    printf("Input Data:\n");
    strcpy( transData.cardHolderData.primaryAccountNumber,"8989374615436851");
    transData.terminalData.transAmount = 200;
    if(recieveTransactionData(&transData)== APPROVED){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }
}

void isValidAccountTest(void){

    ST_accountsDB_t accountRefrence;
    ST_cardData_t cardData;

    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: recieveTransactionData\n");

    printf("Test Case %d:\n",1);
    strcpy(cardData.primaryAccountNumber,"7894007076043875"); 

    printf("Input Data:");
    puts(cardData.primaryAccountNumber);
    if(isValidAccount(&cardData,&accountRefrence)== SERVER_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }

    printf("Test Case %d:\n",2);
    strcpy(cardData.primaryAccountNumber,""); 

    printf("Input Data:");
    puts(cardData.primaryAccountNumber);
    if(isValidAccount(&cardData,&accountRefrence)== SERVER_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }

    printf("Test Case %d:\n",3);
    strcpy(cardData.primaryAccountNumber,"45456456"); 

    printf("Input Data:");
    puts(cardData.primaryAccountNumber);
    if(isValidAccount(&cardData,&accountRefrence)== SERVER_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }

}
void isBlockedAccountTest(void){
    ST_accountsDB_t accountRefrence;
  
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: isBlockedAccount\n");

    printf("Test Case %d:\n",1);
    printf("Input Data: RUNNING\n");
    accountRefrence = accountsDB[0];
    if(isBlockedAccount(&accountRefrence)== SERVER_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }

     printf("Input Data: BLOCKED\n");
    accountRefrence = accountsDB[1];
    if(isBlockedAccount(&accountRefrence)== BLOCKED_ACCOUNT){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }



}
void isAmountAvailableTest(void){
        ST_accountsDB_t accountRefrence;
  ST_terminalData_t termData;
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: isAmountAvailable\n");

    printf("Test Case %d:\n",1);
    printf("Input Data: 100\n");
    accountRefrence = accountsDB[0];
    termData.transAmount = 100;
    
    if(isAmountAvailable(&termData,&accountRefrence)== SERVER_OK){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }

     printf("Input Data: 3000\n");
     termData.transAmount = 3000;
    
    if(isAmountAvailable(&termData,&accountRefrence)== LOW_BALANCE){
        printf("Expected Result: OK\n");
        printf("Actual Result: OK\n");
    }

    else{
        printf("Expected Result: NOK\n");    
        printf("Actual Result: NOK\n");
    }


}
void listSavedTransactionsTest(void){
      printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: listSavedTransactions\n");
    ST_transaction_t trans;

    strcpy( trans.cardHolderData.cardHolderName,"mohamed yasser");
    strcpy(trans.cardHolderData.primaryAccountNumber, "12132");
    strcpy(trans.cardHolderData.cardExpirationDate, "05/25");
    saveTransaction(&trans);
    strcpy( trans.cardHolderData.cardHolderName,"mohamed yasser");
    strcpy(trans.cardHolderData.primaryAccountNumber, "12132");
    strcpy(trans.cardHolderData.cardExpirationDate, "05/25");
    saveTransaction(&trans);
    listSavedTransactions();
}

void saveTransactionTest(void){
    ST_transaction_t transData;
    printf("Tester Name: Mohamed Elesaily\n");
    printf("Function Name: saveTransactionTest\n");
    ST_transaction_t trans;

    strcpy( trans.cardHolderData.cardHolderName,"mohamed yasser");
    strcpy(trans.cardHolderData.primaryAccountNumber, "12132");
    strcpy(trans.cardHolderData.cardExpirationDate, "05/25");
    saveTransaction(&transData);


    strcpy( trans.cardHolderData.cardHolderName,"mohamed");
    strcpy(trans.cardHolderData.primaryAccountNumber, "456456");
    strcpy(trans.cardHolderData.cardExpirationDate, "05/25");
    trans.terminalData.transAmount = 500;
    saveTransaction(&transData);
    trans.terminalData.transAmount = 500;
    strcpy( trans.cardHolderData.cardHolderName,"ahmed");
    strcpy(trans.cardHolderData.primaryAccountNumber, "456456");
    strcpy(trans.cardHolderData.cardExpirationDate, "05/25");
    saveTransaction(&transData);
}
