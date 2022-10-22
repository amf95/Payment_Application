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

#define NUM_OF_TEST_CASES 

ST_transaction_t transactionTestCases[NUM_OF_TEST_CASES + 1] = {
    {.cardHolderData = 
    {.cardHolderName =  "Ahmed Mohamed Mahmoud",
    .primaryAccountNumber = "1111111111111111", 
    .cardExpirationDate = "07/25"},
    .terminalData = {.transAmount = 5000},
    .transState = RUNNING
    },  // case: 0, APPROVED, SERVER_OK

    {.cardHolderData = 
    {.cardHolderName =  "Mohamed Ali Samy Ibrahim",
    .primaryAccountNumber = "2222222222222222", 
    .cardExpirationDate = "08/26"},
    .terminalData = {.transAmount = 10000},
    .transState = RUNNING
    }, // case: 1,

    {.cardHolderData = 
    {.cardHolderName =  "Amr Zein Mohamed Ali",
    .primaryAccountNumber = "3333333333333333", 
    .cardExpirationDate = "03/27"},
    .terminalData = {.transAmount = 5000},
    .transState = RUNNING
    }, // case: 3, DECLINED_INSUFFECIENT_FUND, LOW_BALANCE

    {.cardHolderData = 
    {.cardHolderName =  "Sara Ahmed Mohamed saad",
    .primaryAccountNumber = "4444444444444444", 
    .cardExpirationDate = "04/25"},
    .terminalData = {.transAmount = 1000},
    .transState = RUNNING
    }, // case: 4

    {.cardHolderData = 
    {.cardHolderName =  "Saly Mahmoud Zein Sayed",
    .primaryAccountNumber = "5555555555555555", 
    .cardExpirationDate = "05/28"},
    .terminalData = {.transAmount = 1000},
    }, // case: 5, FRAUD_CARD, ACCOUNT_NOT_FOUND

    {.cardHolderData = 
    {.cardHolderName =  "John Steward Izak Sam",
    .primaryAccountNumber = "6666666666666666", 
    .cardExpirationDate = "05/29"},
    .terminalData = {.transAmount = 1000},
    .transState = BLOCKED
    }, // case: 6, DECLINED_STOLEN_CARD, BLOCKED_ACCOUNT
};
    


EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
void listSavedTransactions(void);


void recieveTransactionDataTest(void){

    char log[LOG_SIZE];
    formateTransactionInfo(&transactionTestCases[0], log);
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "recieveTransactionData()", 
        "APPROVED",
        log,
        APPROVED,
        recieveTransactionData(&transactionTestCases[0])
    );

    formateTransactionInfo(&transactionTestCases[3], log);
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "recieveTransactionData()", 
        "DECLINED_INSUFFECIENT_FUND",
        log,
        DECLINED_INSUFFECIENT_FUND,
        recieveTransactionData(&transactionTestCases[3])
    );

    formateTransactionInfo(&transactionTestCases[6], log);
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "recieveTransactionData()", 
        "DECLINED_STOLEN_CARD",
        log,
        DECLINED_STOLEN_CARD,
        recieveTransactionData(&transactionTestCases[6])
    );

    formateTransactionInfo(&transactionTestCases[5], log);
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "recieveTransactionData()", 
        "FRAUD_CARD",
        log,
        FRAUD_CARD,
        recieveTransactionData(&transactionTestCases[5])
    );

    // move accountsDB file first.
    formateTransactionInfo(&transactionTestCases[0], log);
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "recieveTransactionData()", 
        "INTERNAL_SERVER_ERROR",
        log,
        INTERNAL_SERVER_ERROR,
        recieveTransactionData(&transactionTestCases[0])
    );
}

void isValidAccountTest(void){
    char log[LOG_SIZE];
    formateTransactionInfo(&transactionTestCases[0], log);
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "isValidAccount()", 
        "SERVER_OK",
        log,
        SERVER_OK,
        recieveTransactionData(&transactionTestCases[0])
    );

    formateTransactionInfo(&transactionTestCases[5], log);
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "isValidAccount()", 
        "ACCOUNT_NOT_FOUND",
        log,
        ACCOUNT_NOT_FOUND,
        recieveTransactionData(&transactionTestCases[5])
    );
}

void isBlockedAccountTest(void){
    char log[LOG_SIZE];
    formateTransactionInfo(&transactionTestCases[0], log);
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "isBlockedAccount()", 
        "SERVER_OK",
        log,
        SERVER_OK,
        isBlockedAccount(&transactionTestCases[0])
    );

    formateTransactionInfo(&transactionTestCases[6], log);
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "isBlockedAccount()", 
        "BLOCKED_ACCOUNT",
        log,
        BLOCKED_ACCOUNT,
        isBlockedAccount(&transactionTestCases[6])
    );
BLOCKED_ACCOUNT
SERVER_OK
}

void isAmountAvailableTest(void){
LOW_BALANCE
SERVER_OK
}



void saveTransactionTest(void){
//SAVING_FAILED
}

void listSavedTransactionsTest(void){

}


// added helper functions:
void printServerTestCaseInfo(char *testerName, char *FunctionName,
                            char *testCase, char *inputData,
                            EN_serverError_t expectedResult, 
                            EN_serverError_t actualResult){

    char expectedResultStr[32], actualResultStr[32];
    serverErrorToStr(expectedResultStr, expectedResult);
    serverErrorToStr(actualResultStr, actualResult);
    printf(
        "Tester Name: \"%s\"\n"
        "Function Name: %s\n"
        "Test Case: %s\n"
        "Input Data: %s\n"
        "Expected Result: %s\n"
        "Actual Result: %s\n\n",
        testerName, 
        FunctionName,
        testCase,
        inputData,
        expectedResultStr,
        actualResultStr
        );
}
