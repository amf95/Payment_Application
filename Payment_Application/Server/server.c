/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

task: Implement the server module.
1-Fill in server.h file with functions' prototypes and typedefs.
2-Implement server-side accounts' database.
3-Implement server-side transactions' database.
4-Implement recieveTransactionData function.
5-Implement isValidAccount function.
6-Implement isAmountAvailable function.
7-Implement saveTransaction function.

*/

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int accountsDBIndex = 0;

ST_accountsDB_t accountsDB[ACCOUNTS_DB_SIZE + 1] = {
    {.primaryAccountNumber = "1111111111111111", .balance = 50000}, // case 1
    {.primaryAccountNumber = "2222222222222222", .balance = 50000}, // case 2
    {.primaryAccountNumber = "3333333333333333", .balance = 3000},  // case 3   
    {.primaryAccountNumber = "4444444444444444", .balance = 1000}   // case 4
    }; 

ST_transaction_t transactionsDB[TRANSACTIONS_DB_SIZE + 1] = {0};


EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    if(isValidAccount(&transData->cardHolderData) == SERVER_OK){
        if(isAmountAvailable(&transData->terminalData) == SERVER_OK){
            transData->transState = APPROVED;
        }
        else{
            transData->transState = DECLINED_INSUFFECIENT_FUND;
        }
    }
    else{
        transData->transState = DECLINED_STOLEN_CARD;
    }

    if(saveTransaction(transData) == SERVER_OK){
        return transData->transState;
    }
    else{
        return INTERNAL_SERVER_ERROR;
    }
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    for(int i=0; i<= ACCOUNTS_DB_SIZE; i++){
        if(strcmp(cardData->primaryAccountNumber, 
        accountsDB[i].primaryAccountNumber) == 0){
            accountsDBIndex = i;
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    if(termData->transAmount <= accountsDB[accountsDBIndex].balance){
        return SERVER_OK;
    }
    else{
        return LOW_BALANCE;
    }  
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
    time_t now = time(NULL);
    transData->transactionSequenceNumber = now;
    
    //save in transactionsDB(Array)
    static int sequenceIndex = 0;
    transactionsDB[sequenceIndex] = *transData;
    if(sequenceIndex < TRANSACTIONS_DB_SIZE - 1) sequenceIndex++;
    
    //save data to logs.txt file.
    FILE *transactions_DB;
    transactions_DB = fopen(LOG_FILE_PATH, "a");
    
    if(transactions_DB != NULL){    
        // get transaction date.
        //char date[50];
        //struct tm *localTime = localtime(&now);
        //strftime(date, 50, "%Y-%m-%d %H:%M:%S", localTime);

        char log[LOG_SIZE];

        //manage data formate. 
        snprintf(log, LOG_SIZE, 
            "%d,%s,%f,%d,%.2f,%s,%s,%s\n",
            transData->transactionSequenceNumber,
            transData->terminalData.transactionDate,
            transData->terminalData.transAmount,
            transData->transState,
            transData->terminalData.maxTransAmount,
            transData->cardHolderData.cardHolderName,
            transData->cardHolderData.primaryAccountNumber,
            transData->cardHolderData.cardExpirationDate
        );

        //save in transactions_DB(File).
        fputs(log, transactions_DB);
          
        fclose(transactions_DB);

        listSavedTransactions();

        return SERVER_OK;       
    }
    else{
        return SAVING_FAILED;
    }
    
}

/*
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData){
    char buffer[LINE_MAX_SIZE + 1];
    FILE *transactions_DB;
    transactions_DB = fopen(LOG_FILE_PATH, "r");
    
    if(transactions_DB != NULL){  
        const char seperator[] = ",";  
        while (feof(transactions_DB))
        {
            fgets(buffer, LINE_MAX_SIZE, transactions_DB);
            if(atoi(strtok(buffer, seperator) == transactionSequenceNumber)){
                fclose(transactions_DB);
                printf("Found: %s\n", buffer);
                return SERVER_OK;
            } 
        }      
    }
    else{
        return SAVING_FAILED;
    }
}
*/

void listSavedTransactions(void){
    for(int i = 0; i <= TRANSACTIONS_DB_SIZE; i++){
        if(transactionsDB[i].transactionSequenceNumber > 0){
            char *transState;
            if(transactionsDB[i].transState == APPROVED) 
            transState = "APPROVED";
            if(transactionsDB[i].transState == DECLINED_INSUFFECIENT_FUND) 
            transState = "DECLINED_INSUFFECIENT_FUND";
            if(transactionsDB[i].transState == DECLINED_STOLEN_CARD) 
            transState = "DECLINED_STOLEN_CARD";
            if(transactionsDB[i].transState == INTERNAL_SERVER_ERROR) 
            transState = "INTERNAL_SERVER_ERROR";

            printf(
            "\n#########################\n"
            "Transaction Sequence Number: %d\n" 
            "Transaction Date: %s\n"
            "Transaction Amount: %.2f\n"
            "Transaction State: %s\n"
            "Terminal Max Amount: %.2f\n"
            "Cardholder Name: \"%s\"\n"
            "PAN: %s\n"
            "Card Expiration Date: %s\n"
            "#########################\n\n",
            transactionsDB[i].transactionSequenceNumber,
            transactionsDB[i].terminalData.transactionDate,
            transactionsDB[i].terminalData.transAmount,
            transState,
            transactionsDB[i].terminalData.maxTransAmount,
            transactionsDB[i].cardHolderData.cardHolderName,
            transactionsDB[i].cardHolderData.primaryAccountNumber,
            transactionsDB[i].cardHolderData.cardExpirationDate
            );
        }
        
    }
    
}