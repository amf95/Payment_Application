/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

*/

#include "server_test.h"
#include "../../Card/card.h"
#include "../../Terminal/terminal.h"
#include "../../Server/server.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CASES 5


ST_transaction_t transactionTestCases[CASES + 1] = {
    {.transState = RUNNING,
    .transactionSequenceNumber = 1651465,
    .cardHolderData ={
        .cardExpirationDate = "07/30",
        .cardHolderName =  "Ahmed Mohamed Mahmoud",
        .primaryAccountNumber = "1111111111111111"},
    .terminalData = {
        .maxTransAmount = 8000,
        .transactionDate = "01/10/2022",
        .transAmount = 5000},
    },  // case: 0, APPROVED

    {.cardHolderData = 
    {.cardHolderName =  "Mohamed Ali Samy Ibrahim",
    .primaryAccountNumber = "2222222222222222"},
    .terminalData = {.transAmount = 100000},
    }, // case: 1, DECLINED_INSUFFECIENT_FUND

    {.cardHolderData = 
    {.cardHolderName =  "Amr Zein Mohamed Ali",
    .primaryAccountNumber = "6666666666666666", 
    .cardExpirationDate = "03/27"},
    .terminalData = {.transAmount = 1000},
    }, // case: 2, DECLINED_STOLEN_CARD

    {.cardHolderData = 
    {.cardHolderName =  "Sara Ahmed Mohamed saad",
    .primaryAccountNumber = "5555555555555555"},
    .terminalData = {.transAmount = 1000},
    }, // case: 3 FRAUD_CARD

    // INTERNAL_SERVER_ERROR 
};
    
ST_accountsDB_t accountsDBTestCases[CASES + 1] = {
    {
        .balance = 50000,
        .state = RUNNING,
        .primaryAccountNumber = "1111111111111111" 
        // 0, SERVER_OK, RUNNUNG
    },
    {
        .balance = 1000,
        .state = BLOCKED,
        .primaryAccountNumber = "2222222222222222" 
        // 1, FRAUD_CARD, BLOCkED, LOW_BALANCE
    },

};

int main(){
 
 recieveTransactionDataTest();
 isValidAccountTest();
 isBlockedAccountTest();
 isAmountAvailableTest();
 saveTransactionTest();
 listSavedTransactionsTest();
    return 0;
}

void recieveTransactionDataTest(void){

    char log[LOG_SIZE];
    formateTransactionInfo(&transactionTestCases[0], log);
    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "recieveTransactionData()", 
        "APPROVED",
        log, // input values
        APPROVED,
        recieveTransactionData(&transactionTestCases[0])
    );

    formateTransactionInfo(&transactionTestCases[1], log);
    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "recieveTransactionData()", 
        "DECLINED_INSUFFECIENT_FUND",
        log,
        DECLINED_INSUFFECIENT_FUND,
        recieveTransactionData(&transactionTestCases[1])
    );

    formateTransactionInfo(&transactionTestCases[2], log);
    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "recieveTransactionData()", 
        "DECLINED_STOLEN_CARD",
        log,
        DECLINED_STOLEN_CARD,
        recieveTransactionData(&transactionTestCases[2])
    );

    formateTransactionInfo(&transactionTestCases[3], log);
    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "recieveTransactionData()", 
        "FRAUD_CARD",
        log,
        FRAUD_CARD,
        recieveTransactionData(&transactionTestCases[3])
    );

    // move accountsDB file first so that it can't save.
    formateTransactionInfo(&transactionTestCases[0], log);
    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "recieveTransactionData()", 
        "INTERNAL_SERVER_ERROR",
        log,
        INTERNAL_SERVER_ERROR,
        recieveTransactionData(&transactionTestCases[0])
    );
}

void isValidAccountTest(void){

    ST_accountsDB_t accountReference;

    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "isValidAccount()", 
        "SERVER_OK",
        transactionTestCases[0].cardHolderData.primaryAccountNumber,
        SERVER_OK,
        isValidAccount(&transactionTestCases[0].cardHolderData,
        &accountReference)
    );

    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "isValidAccount()", 
        "ACCOUNT_NOT_FOUND",
        transactionTestCases[3].cardHolderData.primaryAccountNumber,
        ACCOUNT_NOT_FOUND,
        isValidAccount(&transactionTestCases[3].cardHolderData,
        &accountReference)
    );
}

void isBlockedAccountTest(void){
    char log[LOG_SIZE];

    formateAccountInfo(accountsDBTestCases[0], log);
    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "isBlockedAccount()", 
        "SERVER_OK",
        log,
        SERVER_OK,
        isBlockedAccount(&accountsDBTestCases[0])
    );

    formateAccountInfo(accountsDBTestCases[1], log);
    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "isBlockedAccount()", 
        "BLOCKED_ACCOUNT",
        log,
        BLOCKED_ACCOUNT,
        isBlockedAccount(&accountsDBTestCases[1])
    );
}

void isAmountAvailableTest(void){

    char log[LOG_SIZE];
    char termData[LOG_SIZE];
    char accountData[LOG_SIZE];

    formateTermInfo(transactionTestCases[0].terminalData, termData);
    formateAccountInfo(accountsDBTestCases[0], accountData);
    snprintf(log, LOG_SIZE, "%s\n%s", termData, accountData);
    
    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "isAmountAvailable()", 
        "SERVER_OK",
        log,
        SERVER_OK,
        isAmountAvailable(&transactionTestCases[0].terminalData
        , &accountsDBTestCases[0])
    );

    formateTermInfo(transactionTestCases[1].terminalData, termData);
    formateAccountInfo(accountsDBTestCases[1], accountData);
    snprintf(log, LOG_SIZE, "%s\n%s", termData, accountData);
    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "isAmountAvailable()", 
        "LOW_BALANCE",
        log,
        LOW_BALANCE,
        isAmountAvailable(&transactionTestCases[1].terminalData
        , &accountsDBTestCases[1])
    );
}



void saveTransactionTest(void){
    
    char log[LOG_SIZE];
    formateTransactionInfo(&transactionTestCases[0], log);
    printServerTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "saveTransaction()", 
        "SERVER_OK",
        log,
        SERVER_OK,
        saveTransaction(&transactionTestCases[0])
    );
    
//SAVING_FAILED
}

void listSavedTransactionsTest(void){
    listSavedTransactions();
}


// added helper functions:
void printServerTestCaseInfo(char *testerName, char *FunctionName,
                            char *testCase, char *inputData,
                            EN_serverError_t expectedResult, 
                            EN_serverError_t actualResult){

    //char expectedResultStr[32], actualResultStr[32];
    //serverErrorToStr(expectedResultStr, expectedResult);
    //serverErrorToStr(actualResultStr, actualResult);
    printf(
        "----------------------------------\n"
        "Tester Name: \"%s\"\n"
        "Function Name: %s\n"
        "Test Case: %s\n"
        "Input Data: %s\n"
        "Expected Result: %d\n"
        "Actual Result: %d\n\n",
        testerName, 
        FunctionName,
        testCase,
        inputData,
        expectedResult,
        actualResult
        );
}


void formateAccountInfo(ST_accountsDB_t accont, char *log){
    char accountState[BUFFER_SIZE];
    serverTransStateToStr(accountState, accont.state);

    //char log[LOG_SIZE];

    snprintf(log, LOG_SIZE,
    "\n#########################\n"
    "PAN: %s\n"
    "State: %d\n"
    "Balance: %.2f\n"
    "#########################\n",
    accont.primaryAccountNumber,
    accont.state,
    accont.balance
    );
}



