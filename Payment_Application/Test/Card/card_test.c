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

    ST_cardData_t cardData; 
    printf("Enter: Ahmed Mohamed Mahmoud\n"); // 21 chars > 20 & < 24.
    EN_cardError_t result = getCardHolderName(&cardData);
    
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardHolderName()", 
        "valideNameCase",
        "Ahmed Mohamed Mahmoud",
        CARD_OK,
        result
    );


    printf("Enter: Ahmed Mohamed fawzy\n"); // 19 chars < 20.
    result = getCardHolderName(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardHolderName()", 
        "belowMinCharsCase",
        " Ahmed Mohamed fawzy",
        WRONG_NAME,
        result
    );


    printf("Enter: Ahmed Mohamed Mahmoud Zakey\n"); // 27 chars > 24.
    result = getCardHolderName(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardHolderName()", 
        "aboveMaxCharsCase",
        "Ahmed Mohamed Mahmoud Zakey",
        WRONG_NAME,
        result
    );

    printf("Just press ENTER:\n"); 
    result = getCardHolderName(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardHolderName()", 
        "nullCase",
        "",
        WRONG_NAME,
        result
    );
}


void getCardExpiryDateTest(void){

    ST_cardData_t cardData; 

    printf("Enter: 01/25\n"); // Valide
    EN_cardError_t result = getCardExpiryDate(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDate()", 
        "valideDateCase",
        "01/25",
        CARD_OK,
        result
    );


    printf("Enter: 7/25\n"); 
    result = getCardExpiryDate(&cardData);
    
    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDate()", 
        "belowMinCharsCase",
        "7/25",
        WRONG_EXP_DATE,
        result
    );


    printf("Enter: 07/2025\n"); 
    result = getCardExpiryDate(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDate()", 
        "aboveMaxCharsCase",
        "07/2025",
        WRONG_EXP_DATE,
        result
    );


    printf("Enter: 07-25\n"); 
    result = getCardExpiryDate(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDate()", 
        "wrongSeperatorCase",
        "07-25",
        WRONG_EXP_DATE,
        result
    );

    
    printf("Enter: o7/3o\n"); 
    result = getCardExpiryDate(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDate()", 
        "charCase",
        "o7/3o",
        WRONG_EXP_DATE,
        result
    );

    
    printf("Just press ENTER:\n"); 
    result = getCardExpiryDate(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardExpiryDate()", 
        "nullCase",
        "",
        WRONG_EXP_DATE,
        result
    );
}

void getCardPANTest(void){

    ST_cardData_t cardData; 

    printf("Enter: 1111111111111111\n"); // Valide
    EN_cardError_t result = getCardPAN(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardPAN()", 
        "valideDateCase",
        "1111111111111111",
        CARD_OK,
        result
    );


    printf("Enter: 111111111111111\n"); // 15
    result = getCardPAN(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardPAN()", 
        "belowMinCharsCase",
        "111111111111111",
        WRONG_PAN,
        result
    );


    printf("Enter: 11111111111111111111\n"); // 20
    result = getCardPAN(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardPAN()", 
        "aboveMaxCharsCase",
        "11111111111111111111",
        WRONG_PAN,
        result
    );


    printf("Enter: 1111111i11111111\n"); // i char
    result = getCardPAN(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardPAN()", 
        "charCase",
        "1111111i11111111",
        WRONG_PAN,
        result
    );


    printf("Just press ENTER:\n"); // NULL
    result = getCardPAN(&cardData);

    printCardTestCaseInfo(
        "Ahmed Mahmoud Fawzy", "getCardPAN()", 
        "nullCase",
        "",
        WRONG_PAN,
        result
    );
}

//Added Helper Functions:

void printCardTestCaseInfo( char *testerName, char *FunctionName,
                        char *testCase, char *inputData,
                        EN_cardError_t expectedResult, 
                        EN_cardError_t actualResult){
                            
    char expectedResultStr[32], actualResultStr[32];
    cardErrorToStr(expectedResultStr, expectedResult);
    cardErrorToStr(actualResultStr, actualResult);
    printf(
        "---------------------------------\n"
        "Tester Name: \"%s\"\n"
        "Function Name: %s\n"
        "Test Case: %s\n"
        "Input Data: %s\n"
        "Expected Result: %s\n"
        "Actual Result: %s\n\n"
        "---------------------------------\n",
        testerName, 
        FunctionName,
        testCase,
        inputData,
        expectedResultStr,
        actualResultStr
        );
}

