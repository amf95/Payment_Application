/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

task: Implement the application.
1-Fill in application.h file with functions' prototypes.
2-Implement appStart function.

task: Testing the application
1-Transaction approved user story.
2-Exceed the maximum amount user story.
3-Insufficient fund user story.
4-Expired card user story.
5-Invalid card user story.

*/

#include "app.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_TEST_CASES 6

ST_cardData_t card;
ST_terminalData_t terminal;
ST_transaction_t transaction;

ST_transaction_t transactionTestCases[NUM_OF_TEST_CASES + 1] = {
    {.cardHolderData = 
    {.cardHolderName =  "Ahmed Mohamed Mahmoud",
    .primaryAccountNumber = "1111111111111111", 
    .cardExpirationDate = "07/25"},
    .terminalData = {.transAmount = 5000} },  // case: 1

    {.cardHolderData = 
    {.cardHolderName =  "Mohamed Samy Ibrahim",
    .primaryAccountNumber = "2222222222222222", 
    .cardExpirationDate = "08/26"},
    .terminalData = {.transAmount = 10000} }, // case: 2

    {.cardHolderData = 
    {.cardHolderName =  "Amr Zein Mohamed Ali",
    .primaryAccountNumber = "3333333333333333", 
    .cardExpirationDate = "03/27"},
    .terminalData = {.transAmount = 5000} 
    }, // case: 3

    {.cardHolderData = 
    {.cardHolderName =  "Sara Ahmed Mohamed saad",
    .primaryAccountNumber = "4444444444444444", 
    .cardExpirationDate = "04/21"},
    .terminalData = {.transAmount = 1000} 
    }, // case: 4

    {.cardHolderData = 
    {.cardHolderName =  "Saly Mahmoud Zein Sayed",
    .primaryAccountNumber = "5555555555555555", 
    .cardExpirationDate = "05/28"},
    .terminalData = {.transAmount = 1000} 
    }, // case: 5

    {.cardHolderData = 
    {.cardHolderName =  "Saeid Ahmed Saad Sayed",
    .primaryAccountNumber = "6666666666666666", 
    .cardExpirationDate = "05/28"},
    .terminalData = {.transAmount = 1000} 
    }, // case: 6
};
    
char testCases[NUM_OF_TEST_CASES + 1][50] = {
    "1-Transaction approved user story",
    "2-Exceed the maximum amount user story",
    "3-Insufficient fund user story",
    "4-Expired card user story",
    "5-Invalid card user story",
    "6-Bloced User story"
};


void appStart(){

    //terminal.maxTransAmount = 8000;
    if(setMaxAmount(&terminal) == INVALID_MAX_AMOUNT){ // max withdraw amount.
        printf("\nTERMINAL: INVALID_MAX_AMOUNT[%2f]!\n", terminal.maxTransAmount);
        exit(0);
    }

    printf("\n");

    int mode = 0;
    
    printf("0-Manual Inputs:\n"
    "[<NAME:[20-24]>, <PAN:[16-19]>, <DATE: MM/YY>, <AMOUNT: XXXX>]\n\n");

    printf("\n!!!WARNING :  \"1-5 Test Cases Will Bypass The Card Module\"   : WARNING!!!\n\n");
    for(int i = 0; i < NUM_OF_TEST_CASES; i++){
        printTestCases(transactionTestCases[i], testCases[i]);
    }
   
    printf("Please Enter Test Case Number: ");
    scanf("%d", &mode);
    getchar(); // eat away the '\n' left in stdin

    printf("\n");

    //--------------------------- Start Card Side ---------------------------
    switch (mode)
    {
        case 0:
            if(getCardHolderName(&card) == WRONG_NAME){
                printf("\nCARD: WRONG_NAME!\n");
                exit(0);
            }
            printf("CARD: NAME_OK!\n");

            if(getCardExpiryDate(&card) == WRONG_EXP_DATE){
                printf("CARD: WRONG_EXP_DATE!\n");
                exit(0);
            }
            printf("CARD: EXP_DATE_OK!\n");

            if(getCardPAN(&card) == WRONG_PAN){
                printf("\nCARD: WRONG_PAN!\n");
                exit(0);
            }
            printf("CARD: PAN_OK!\n");
            break;

        case 1:
            loadTestValues(&card, &terminal,  transactionTestCases[mode-1],
            "Transaction approved user story");
            break;

        case 2:
            loadTestValues(&card, &terminal,  transactionTestCases[mode-1],
            "Exceed the maximum amount user story");
            break;

        case 3:
            loadTestValues(&card, &terminal,  transactionTestCases[mode-1],
            "Insufficient fund user story");    
            break;

        case 4:
            loadTestValues(&card, &terminal,  transactionTestCases[mode-1],
            "Expired card user story");
            break; 

        case 5:
            loadTestValues(&card, &terminal,  transactionTestCases[mode-1],
            "Invalid card user story");
            break;       

        case 6:
            loadTestValues(&card, &terminal,  transactionTestCases[mode-1],
            "Blocked user story");
            break;
        default:
            printf("\nWrong Case!\n");
            exit(0);
            break;
    }
    //------------------------------ End Card Side ------------------------------
    
    //--------------------------- Start Terminal Side ---------------------------
    if(!(getTransactionDate(&terminal) == TERM_OK)){
        printf("\nTERMINAL: WRONG_DATE[%s]!\n", terminal.transactionDate);
        exit(0);
    }

    if(isCardExpired(card, terminal) == EXPIRED_CARD){
        //printCardInfo(newCard);
        printf("\nTERMINAL: EXPIRED_CARD[Card:%s, Now: %s]!\n", 
        card.cardExpirationDate, terminal.transactionDate);
        exit(0);
    }
    printf("TERMINAL: EXP_DATE_OK!\n");

    if(mode == 0){
        if(getTransactionAmount(&terminal) == INVALID_AMOUNT){
            printf("\nTERMINAL: INVALID_AMOUNT[%.2f]\n", terminal.transAmount);
            exit(0); 
        }
    }
    
    //printf("\n");
    //printCardInfo(newCard);
    //printf("\n");
    
    if(!(isBelowMaxAmount(&terminal) == TERM_OK)){
        printf("\nTERMINAL: EXCEED_MAX_AMOUNT[%.2f/%.2f]!\n", 
        terminal.transAmount, terminal.maxTransAmount);
        exit(0);
    }
    printf("\nTERMINAL: VALID_AMOUNT!\n");
    //----------------------- End Terminal Side -------------------------
        
    //----------------------  Start Server Side -------------------------
    transaction.cardHolderData = card;
    transaction.terminalData = terminal;

    switch (recieveTransactionData(&transaction))
    {
    case APPROVED:
        printf("\nSERVER: APPROVED!.\n");
        break;
    
    case DECLINED_INSUFFECIENT_FUND:
        printf("\nSERVER: DECLINED_INSUFFECIENT_FUND!.\n\n");
        break;

    case DECLINED_STOLEN_CARD:
        printf("\nSERVER: DECLINED_STOLEN_CARD!\n\n");
        break;

    case INTERNAL_SERVER_ERROR:
        printf("\nSERVER: INTERNAL_SERVER_ERROR!\n\n");
        break;
    case FRAUD_CARD:
        printf("\nSERVER: FRAUD_CARD!\n\n");
        break;
    default:
        break;
    }
    //--------------------------- Server Side ---------------------------
}


//------------------------------ Helper Functions ----------------------------------

void loadTestValues(ST_cardData_t *cardData, ST_terminalData_t *termData, 
ST_transaction_t source,char *testCase){
    printf("Loading \"%s\".\n\n", testCase);
    *cardData = source.cardHolderData;
    source.terminalData.maxTransAmount = termData->maxTransAmount; //load max amount enterd by user.
    *termData = source.terminalData;
}
/*
"1-Transaction approved user story:\n"
    "[\"Ahmed Mohamed Mahmoud\", \"1111111111111111\", 07/25, 5000]\n\n"

 {.cardHolderData = 
    {.cardHolderName =  "Saly Mahmoud Zein Sayed",
    .primaryAccountNumber = "5555555555555555", 
    .cardExpirationDate = "05/28"},
    .terminalData = {.transAmount = 1000} 
    }, // case: 5
*/
void printTestCases(ST_transaction_t transactionCase, char *testCase){
    printf("%s:\n", testCase);
    printf("[\"%s\", \"%s\", \"%s\", \"%.1f\"]\n\n",
    transactionCase.cardHolderData.cardHolderName, 
    transactionCase.cardHolderData.primaryAccountNumber,
    transactionCase.cardHolderData.cardExpirationDate,
    transactionCase.terminalData.transAmount);    
}