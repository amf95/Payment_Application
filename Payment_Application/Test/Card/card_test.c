/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

*/


#include "card_test.h"
#include "../../Card/card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    getCardHolderNameTest();
    getCardExpiryDateTest();
    getCardPANTest();

    return 0;
}

void getCardHolderNameTest(void){
    ST_cardData_t valideNameCase = 
    {.cardHolderName = "Ahmed Mohamed Mahmoud"}; // 21 chars > 20 & < 24.
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardHolderName()", 
        "valideNameCase",
        valideNameCase.cardHolderName,
        CARD_OK,
        getCardHolderName(&valideNameCase)
    );

    ST_cardData_t belowMinCharsCase = 
    {.cardHolderName = "Ahmed Mohamed fawzy"}; // 19 chars < 20.
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardHolderName()", 
        "belowMinCharsCase",
        belowMinCharsCase.cardHolderName,
        WRONG_NAME,
        getCardHolderName(&belowMinCharsCase)
    );

    ST_cardData_t aboveMaxCharsCase = 
    {.cardHolderName = "Ahmed Mohamed Mahmoud Zakey"}; // 27 chars > 24.
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardHolderName()", 
        "aboveMaxCharsCase",
        aboveMaxCharsCase.cardHolderName,
        WRONG_NAME,
        getCardHolderName(&aboveMaxCharsCase)
    );

    ST_cardData_t nullCase = 
    {.cardHolderName = NULL}; // NULL.
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardHolderName()", 
        "nullCase",
        nullCase.cardHolderName,
        WRONG_NAME,
        getCardHolderName(&nullCase)
    );
}

void getCardExpiryDateTest(void){

    ST_cardData_t valideDateCase = 
    {.cardExpirationDate = "01/25"}; // Valide
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDateTest()", 
        "valideDateCase",
        valideDateCase.cardExpirationDate,
        CARD_OK,
        getCardExpiryDate(&valideDateCase)
    );

    ST_cardData_t expiredYearCardCase = 
    {.cardExpirationDate = "01/21"}; 
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDateTest()", 
        "expiredYearCardCase",
        expiredYearCardCase.cardExpirationDate,
        WRONG_EXP_DATE,
        getCardExpiryDate(&expiredYearCardCase)
    );

    ST_cardData_t expiredMonthCardCase = 
    {.cardExpirationDate = "05/22"}; 
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDateTest()", 
        "expiredMonthCardCase",
        expiredMonthCardCase.cardExpirationDate,
        WRONG_EXP_DATE,
        getCardExpiryDate(&expiredMonthCardCase)
    );

    ST_cardData_t belowMinCharsCase = 
    {.cardExpirationDate = "7/25"}; 
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDateTest()", 
        "belowMinCharsCase",
        belowMinCharsCase.cardExpirationDate,
        WRONG_EXP_DATE,
        getCardExpiryDate(&belowMinCharsCase)
    );

    ST_cardData_t aboveMaxCharsCase = 
    {.cardExpirationDate = "07/2025"}; 
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDateTest()", 
        "aboveMaxCharsCase",
        aboveMaxCharsCase.cardExpirationDate,
        WRONG_EXP_DATE,
        getCardExpiryDate(&aboveMaxCharsCase)
    );

    ST_cardData_t wrongSeperatorCase = 
    {.cardExpirationDate = "07-25"}; 
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDateTest()", 
        "wrongSeperatorCase",
        wrongSeperatorCase.cardExpirationDate,
        WRONG_EXP_DATE,
        getCardExpiryDate(&wrongSeperatorCase)
    );

    ST_cardData_t charCase = 
    {.cardExpirationDate = "o7/3o"}; 
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDateTest()", 
        "charCase",
        charCase.cardExpirationDate,
        WRONG_EXP_DATE,
        getCardExpiryDate(&charCase)
    );

    ST_cardData_t nullCase = 
    {.cardExpirationDate = NULL}; // NULL.
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDateTest()", 
        "nullCase",
        nullCase.cardExpirationDate,
        WRONG_EXP_DATE,
        getCardExpiryDate(&nullCase)
    );
}

void getCardPANTest(void){

    ST_cardData_t valideDateCase = 
    {.primaryAccountNumber = "1111111111111111"}; // Valide 16
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardPANTest()", 
        "valideDateCase",
        valideDateCase.primaryAccountNumber,
        CARD_OK,
        getCardPAN(&valideDateCase)
    );


    ST_cardData_t belowMinCharsCase = 
    {.primaryAccountNumber = "111111111111111"}; // 15
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardPANTest()", 
        "belowMinCharsCase",
        belowMinCharsCase.primaryAccountNumber,
        WRONG_EXP_DATE,
        getCardPAN(&belowMinCharsCase)
    );

    ST_cardData_t aboveMaxCharsCase = 
    {.primaryAccountNumber = "11111111111111111111"}; // 20
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardPANTest()", 
        "aboveMaxCharsCase",
        aboveMaxCharsCase.primaryAccountNumber,
        WRONG_EXP_DATE,
        getCardPAN(&aboveMaxCharsCase)
    );

    ST_cardData_t charCase = 
    {.primaryAccountNumber = "1111111i111111"}; 
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardPANTest()", 
        "charCase",
        charCase.primaryAccountNumber,
        WRONG_EXP_DATE,
        getCardPAN(&charCase)
    );

    ST_cardData_t nullCase = 
    {.primaryAccountNumber = NULL}; // NULL.
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardPANTest()", 
        "nullCase",
        nullCase.primaryAccountNumber,
        WRONG_EXP_DATE,
        getCardPAN(&nullCase)
    );
}

//Added Helper Functions.
void isValidDateFormatTest(void){

}

void isValidPANFormatTest(void){
    
}


void printCardTestCaseInfo( char *testerName, char *FunctionName,
                        char *testCase, char *inputData,
                        EN_cardError_t expectedResult, 
                        EN_cardError_t actualResult){
printf("\n\ndump\n\n");
    char expectedResultStr[32], actualResultStr[32];
    cardErrorToStr(expectedResultStr, expectedResult);
    cardErrorToStr(actualResultStr, actualResult);
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

void cardErrorToStr(char *str, EN_cardError_t error){
    switch (error)
    {
    case CARD_OK:
        strcpy(str, "CARD_OK");
        break;
    case WRONG_NAME:
        strcpy(str, "WRONG_NAME");
        break;
    case WRONG_EXP_DATE:
        strcpy(str, "WRONG_EXP_DATE");
        break;
    case WRONG_PAN:
        strcpy(str, "WRONG_PAN");
        break;
    default:
        break;
    }
}