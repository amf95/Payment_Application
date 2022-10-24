/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

*/

#ifndef SERVER_TEST_H
#define SERVER_TEST_H

#include "../../Card/card.h"
#include "../../Terminal/terminal.h"
#include "../../Server/server.h"

void recieveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);
void listSavedTransactionsTest(void);

// added helper functions:
void printServerTestCaseInfo( char *testerName, char *FunctionName,
                        char *testCase, char *inputData,
                        EN_serverError_t expectedResult, 
                        EN_serverError_t actualResult);
void formateAccountInfo(ST_accountsDB_t accont, char *log);
#endif
