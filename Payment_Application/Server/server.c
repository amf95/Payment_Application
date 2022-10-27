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
    {
        .primaryAccountNumber = "1111111111111111", 
        .balance = 40000,
        .state = RUNNING
    }, // case 1
    
    {
        .primaryAccountNumber = "2222222222222222", 
        .balance = 50000,
        .state = RUNNING
    }, // case 2

    {
        .primaryAccountNumber = "3333333333333333", 
        .balance = 3000,
        .state = RUNNING
    },  // case 3  

    {
        .primaryAccountNumber = "4444444444444444", 
        .balance = 1000,
        .state = RUNNING
    },   // case 4

    /*
    {
        .primaryAccountNumber = "555555555555555555", 
        .balance = 1000,
        .state = BLOCKED
    },   // case 5
    */
    
    {
        .primaryAccountNumber = "6666666666666666", 
        .balance = 1000,
        .state = BLOCKED
    },   // case 6

    {
        .primaryAccountNumber = "7777777777777777777", 
        .balance = 1000,
        .state = RUNNING
    },   // case 7

    {
        .primaryAccountNumber = "8888888888888888", 
        .balance = 1000,
        .state = RUNNING
    },   // case 8

    {
        .primaryAccountNumber = "9999999999999999999", 
        .balance = 1000,
        .state = RUNNING
    },   // case 9

    {
        .primaryAccountNumber = "1212121212121212", 
        .balance = 1000,
        .state = RUNNING
    }   // case 10
}; 

ST_transaction_t transactionsDB[TRANSACTIONS_DB_SIZE + 1] = {0};

EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    ST_accountsDB_t accountRefrence;

    if(!(isValidAccount(&transData->cardHolderData, &accountRefrence) == SERVER_OK))
        transData->transState = FRAUD_CARD;
    else{    
        if(!(isBlockedAccount(&accountRefrence) == SERVER_OK))
            transData->transState = DECLINED_STOLEN_CARD;
        else{
            if(!(isAmountAvailable(&transData->terminalData, &accountRefrence) == SERVER_OK))
                transData->transState = DECLINED_INSUFFECIENT_FUND;
            else{
                transData->transState = APPROVED;
                accountsDB[accountsDBIndex].balance -= transData->terminalData.transAmount;
            }
        }
    }
    // save transaction anyways.
    if(saveTransaction(transData) == SERVER_OK){
        return transData->transState;
    }
    return INTERNAL_SERVER_ERROR;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, 
ST_accountsDB_t *accountRefrence){ //accountreference to the whole accountsDB.
    for(int i=0; i<= ACCOUNTS_DB_SIZE; i++){
        if(strcmp(cardData->primaryAccountNumber, 
        accountsDB[i].primaryAccountNumber) == 0){
            *accountRefrence = accountsDB[i];
            accountsDBIndex = i;
            return SERVER_OK;
        }
    }
    accountRefrence = NULL;
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
    if(accountRefrence->state == RUNNING) return SERVER_OK;
    return BLOCKED_ACCOUNT;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, 
ST_accountsDB_t *accountRefrence){
    if(termData->transAmount <= accountRefrence->balance) return SERVER_OK;
    return LOW_BALANCE;  
}

EN_serverError_t saveTransaction(ST_transaction_t *transData){
    time_t now = time(NULL);
    transData->transactionSequenceNumber = now;
    
    //save in transactionsDB(Array)
    static int sequenceIndex = 0;
    transactionsDB[sequenceIndex] = *transData;
    if(sequenceIndex < TRANSACTIONS_DB_SIZE - 1) sequenceIndex++;
//listSavedTransactions();    
//return SERVER_OK; //<<<<<<<<<<<<<<<< test
    //save data to .txt file.
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
            "%d,%s,%f,%f,%d,%.2f,%s,%s,%s\n",
            transData->transactionSequenceNumber,
            transData->terminalData.transactionDate,
            transData->terminalData.transAmount,
            accountsDB[accountsDBIndex].balance,
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
    
    return SAVING_FAILED;   
}


void listSavedTransactions(void){
    printf("TRANSACTIONS LIST:\n");
    for(int i = 0; i <= TRANSACTIONS_DB_SIZE; i++){
        if(transactionsDB[i].transactionSequenceNumber > 0){
            char log[LOG_SIZE];
            formateTransactionInfo(&transactionsDB[i], log);
            printf("%s\n", log);
        }
    }
}


// added helper functions:

void formateTransactionInfo(ST_transaction_t *transData, char *log){
    char transState[BUFFER_SIZE];
    serverTransStateToStr(transState, transData->transState);

    float balanceAfterTransaction = 0.0;

    if(transData->transState == APPROVED){
    balanceAfterTransaction = 
    accountsDB[accountsDBIndex].balance + transData->terminalData.transAmount;
    }
    else if(transData->transState == DECLINED_INSUFFECIENT_FUND){
        balanceAfterTransaction = accountsDB[accountsDBIndex].balance;
    }
    else if(transData->transState == FRAUD_CARD 
    || transData->transState == DECLINED_STOLEN_CARD){
        balanceAfterTransaction = 0.0;
        accountsDB[accountsDBIndex].balance = 0;
    }
    //char log[LOG_SIZE];
    
    snprintf(log, LOG_SIZE,
    "\n#########SERVER##########\n"
    "Transaction Sequence Number: %d\n" 
    "Transaction Date: %s\n"
    "Balance Before Transaction: %.2f\n"
    "Transaction Amount(Withdraw): %.2f\n"
    "Balance After Transaction: %.2f\n"
    "Transaction State: %s\n"
    "Terminal Max Amount: %.2f\n"
    "Cardholder Name: \"%s\"\n"
    "PAN: %s\n"
    "Card Expiration Date: %s\n"
    "#########################\n\n",
    transData->transactionSequenceNumber,
    transData->terminalData.transactionDate,
    balanceAfterTransaction,
    transData->terminalData.transAmount,
    accountsDB[accountsDBIndex].balance,
    transState,
    transData->terminalData.maxTransAmount,
    transData->cardHolderData.cardHolderName,
    transData->cardHolderData.primaryAccountNumber,
    transData->cardHolderData.cardExpirationDate
    );
}

void serverErrorToStr(char *str, EN_serverError_t error){
    switch (error)
    {
        case SERVER_OK:
            strcpy(str, "SERVER_OK");
            break;
        case SAVING_FAILED:
            strcpy(str, "SAVING_FAILED");
            break;
        case TRANSACTION_NOT_FOUND:
            strcpy(str, "TRANSACTION_NOT_FOUND");
            break;
        case ACCOUNT_NOT_FOUND:
            strcpy(str, "ACCOUNT_NOT_FOUND");
            break;
        case BLOCKED_ACCOUNT:
            strcpy(str, "BLOCKED_ACCOUNT");
            break;
        default:
            strcpy(str, "Unkown");
            break;
    }
}

void serverTransStateToStr(char *str, EN_transState_t transState){
     switch (transState)
    {
        case APPROVED:
        strcpy(str, "APPROVED");
        break;
        case DECLINED_INSUFFECIENT_FUND:
            strcpy(str, "DECLINED_INSUFFECIENT_FUND");
            break;
        case DECLINED_STOLEN_CARD:
            strcpy(str, "DECLINED_STOLEN_CARD");
            break;
        case FRAUD_CARD:
            strcpy(str, "FRAUD_CARD");
            break;
        case INTERNAL_SERVER_ERROR:
            strcpy(str, "INTERNAL_SERVER_ERROR");
            break;
        default:
            strcpy(str, "Unkown");
            break;
    }
}

void serverAccountStateToStr(char *str, EN_accountState_t accountState){
     switch (accountState)
    {
        case RUNNING:
            strcpy(str, "RUNNING");
            break;
        case BLOCKED:
            strcpy(str, "BLOCKED");
            break;
        default:
            strcpy(str, "Unkown");
            break;
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