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

int clientIndex = 0;

ST_accountsDB_t accountsDB[ACCOUNTS_DB_SIZE + 1] = {
    {.primaryAccountNumber = "1111111111111111", .balance = 50000},
    {.primaryAccountNumber = "2222222222222222", .balance = 50000},
    {.primaryAccountNumber = "3333333333333333", .balance = 3000},
    {.primaryAccountNumber = "4444444444444444", .balance = 1000}
    }; 

ST_transaction_t transactionsDB[TRANSACTIONS_DB_SIZE + 1] = {0};


EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    // update balance.
    accountsDB[clientIndex].balance -= clientInfo.balance;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    for(int i=0; i<= ACCOUNTS_DB_SIZE; i++){
        if(strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0){
            return OK;
        }
    }
    return DECLINED_STOLEN_CARD;
}

EN_serverError_t isAmountAvailable(ST_trminalData_t *termData){
    if(termData->transAmount <= accountsDB[clientIndex].balance){
        return OK;
    }
    else{
        return LOW_BALANCE;
    }  
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
     
    //save data to logs.txt file.
    FILE *logFile;
    logFile = fopen(LOG_FILE_PATH, "a");
    
    if(logFile != NULL){    
        // get transaction date.
        char date[50];
        time_t now = time(NULL);
        struct tm *localTime = localtime(&now);
        strftime(date, 50, "%Y-%m-%d %H:%M:%S", localTime);

        char log[LOG_SIZE];

        snprintf(log, LOG_SIZE, 
        "{ name: \"%s\", pan: \"%s\", date: \"%s\",  balance: %f, withdraw: %f }\n",
        clientInfo.holderName, clientInfo.PAN, date,
        accountsDB[clientIndex].balance, clientInfo.balance);

        fputs(log, logFile);
          
        fclose(logFile);
        return OK;       
    }
    else{
        fclose(logFile);
        return SAVING_FAILED;
    }
}


void printClientInfo(){
    printf("{ Name: \"%s\", PAN: %s, Month: %d, Year: %d, Available Balance: %f }\n\n",
    accountsDB[clientIndex].holderName, accountsDB[clientIndex].PAN,
    accountsDB[clientIndex].expiryMonth, accountsDB[clientIndex].expiryYear,
    accountsDB[clientIndex].balance);
}