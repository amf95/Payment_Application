/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

*/

#include "terminal_test.h"
#include "../../Card/card.h"
#include "../../Terminal/terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define TERM_CASES 5

ST_cardData_t cardTestData[TERM_CASES] ={
    {.cardExpirationDate = "02/25"}, // 0, valide card date
    {.cardExpirationDate = "12/21"}, // 1, expired card year
    {.cardExpirationDate = "02/22"}  // 2, expired card month
};

ST_terminalData_t termTestCases[TERM_CASES] ={
    {.transactionDate = "23/10/2022"}, // 0
    {.maxTransAmount = 5000, .transAmount = 1000}, // 1, belw max amount
    {.maxTransAmount = 5000, .transAmount = 10000} // 2, above max amount 
};

int main(){
    //getTransactionDateTest();
    //isCardExpiredTest();
    //getTransactionAmountTest();
    //isBelowMaxAmountTest();
    setMaxAmountTest();
    return 0;
}

void getTransactionDateTest(void){

    char log[TERM_LOG_SIZE];
    ST_terminalData_t termData;
    EN_terminalError_t result = getTransactionDate(&termData);
    formateTermInfo(termData, log);
    printTermTestCaseInfo( 
        "Ahmed Mahmoud Fawzy",
        "getTransactionDate()",
        "TERM_OK",
        log,
        TERM_OK,
        result
    );
}

void isCardExpiredTest(void){

    char log[TERM_LOG_SIZE];
    char termData[TERM_LOG_SIZE/2];
    char cardData[TERM_LOG_SIZE/2];

    formateTermInfo(termTestCases[0], termData);
    formateCardInfo(cardTestData[0], cardData);

    snprintf(log, TERM_LOG_SIZE, "%s\n%s", cardData, termData);

    EN_terminalError_t result = isCardExpired(cardTestData[0], termTestCases[0]);

    printTermTestCaseInfo( 
        "Ahmed Mahmoud Fawzy",
        "isCardExpiredTest()",
        "TERM_OK",
        log,
        TERM_OK,
        result
    );


    formateCardInfo(cardTestData[1], cardData);

    snprintf(log, TERM_LOG_SIZE, "%s\n%s", cardData, termData);

    result = isCardExpired(cardTestData[1], termTestCases[0]);

    printTermTestCaseInfo( 
        "Ahmed Mahmoud Fawzy",
        "isCardExpiredTest()",
        "EXPIRED_CARD_YEAR",
        log,
        EXPIRED_CARD,
        result
    );


    formateCardInfo(cardTestData[2], cardData);

    snprintf(log, TERM_LOG_SIZE, "%s\n%s", cardData, termData);

    result = isCardExpired(cardTestData[2], termTestCases[0]);

    printTermTestCaseInfo( 
        "Ahmed Mahmoud Fawzy",
        "isCardExpiredTest()",
        "EXPIRED_CARD_MONTH",
        log,
        EXPIRED_CARD,
        result
    );
}


void getTransactionAmountTest(void){

    char log[TERM_LOG_SIZE];
    
    ST_terminalData_t termData;

    printf("Please enter value > 0.0:\n");
    EN_terminalError_t result = getTransactionAmount(&termData);
    formateTermInfo(termData, log);
    printTermTestCaseInfo( 
        "Ahmed Mahmoud Fawzy",
        "getTransactionAmountTest()",
        "TERM_OK",
        log,
        TERM_OK,
        result
    );
    termData.transAmount = 0;

    printf("Please enter value <= 0.0:\n");
    result = getTransactionAmount(&termData);
    formateTermInfo(termData, log);
    printTermTestCaseInfo( 
        "Ahmed Mahmoud Fawzy",
        "getTransactionAmountTest()",
        "INVALID_AMOUNT",
        log,
        INVALID_AMOUNT,
        result
    );
}

void isBelowMaxAmountTest(void){
    char log[TERM_LOG_SIZE];

    EN_terminalError_t result = isBelowMaxAmount(&termTestCases[1]);
    formateTermInfo(termTestCases[1], log);
    printTermTestCaseInfo( 
        "Ahmed Mahmoud Fawzy",
        "isBelowMaxAmountTest()",
        "TERM_OK",
        log,
        TERM_OK,
        result
    );

    result = isBelowMaxAmount(&termTestCases[2]);
    formateTermInfo(termTestCases[2], log);
    printTermTestCaseInfo( 
        "Ahmed Mahmoud Fawzy",
        "isBelowMaxAmountTest()",
        "EXCEED_MAX_AMOUNT",
        log,
        EXCEED_MAX_AMOUNT,
        result
    );
}

void setMaxAmountTest(void){
    char log[TERM_LOG_SIZE];
    
    ST_terminalData_t termData;

    printf("Please enter value > 0.0:\n");
    EN_terminalError_t result = setMaxAmount(&termData);
    formateTermInfo(termData, log);
    printTermTestCaseInfo( 
        "Ahmed Mahmoud Fawzy",
        "setMaxAmountTest()",
        "TERM_OK",
        log,
        TERM_OK,
        result
    );
    termData.maxTransAmount = 0;

    printf("Please enter value <= 0.0:\n");
    result = setMaxAmount(&termData);
    formateTermInfo(termData, log);
    printTermTestCaseInfo( 
        "Ahmed Mahmoud Fawzy",
        "setMaxAmountTest()",
        "INVALID_MAX_AMOUNT",
        log,
        INVALID_MAX_AMOUNT,
        result
    );
}

// added helper functions:


void printTermTestCaseInfo( char *testerName, char *FunctionName,
                        char *testCase, char *inputData,
                        EN_cardError_t expectedResult, 
                        EN_cardError_t actualResult){
                            
    printf(
        "-----------------------------------\n"
        "Tester Name: \"%s\"\n"
        "Function Name: %s\n"
        "Test Case: %s\n"
        "Input Data: %s\n"
        "Expected Result: %d\n"
        "Actual Result: %d\n"
        "-----------------------------------\n",
        testerName, 
        FunctionName,
        testCase,
        inputData,
        expectedResult,
        actualResult
        );
}