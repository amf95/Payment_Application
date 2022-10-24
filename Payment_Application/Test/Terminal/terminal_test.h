/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

*/

#ifndef TERMINAL_TEST_H
#define TERMINAL_TEST_H

#include "../../Card/card.h"
//#include "../../Terminal/terminal.h"

void getTransactionDateTest(void);
void isCardExpiredTest(void);
void isValidCardPANTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);

// added helper functions:
void printTermTestCaseInfo( char *testerName, char *FunctionName,
                        char *testCase, char *inputData,
                        EN_cardError_t expectedResult, 
                        EN_cardError_t actualResult);
#endif
