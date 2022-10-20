/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

task: Implement the application.
1-Fill in application.h file with functions' prototypes.
2-Implement appStart function.

*/

#ifndef APP_H
#define APP_H

#include "../Card/card.h"
#include "../Server/server.h"

void appStart();

//Added Helper Functions.
void loadTestValues(ST_cardData_t *cardData, ST_terminalData_t *termData, 
ST_transaction_t source,char *testCase);
void printTestCases(ST_transaction_t transactionCase, char *testCase);

#endif
