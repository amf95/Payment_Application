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

void recieveTransactionDataTest(void){

}

void isValidAccountTest(void){

}

void isAmountAvailableTest(void){

}

void saveTransactionTest(void){

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
