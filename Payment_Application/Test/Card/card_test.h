/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

*/

#ifndef CARD_TEST_H
#define CARD_TEST_H

#include "../../Card/card.h"

void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

//Added Helper Functions.
void isValidDateFormatTest(void);
void isValidPANFormatTest(void);
void printCardTestCaseInfo( char *testerName, char *FunctionName,
                        char *testCase, char *inputData,
                        EN_cardError_t expectedResult, 
                        EN_cardError_t actualResult);
void cardErrorToStr(char *str, EN_cardError_t error);

#endif