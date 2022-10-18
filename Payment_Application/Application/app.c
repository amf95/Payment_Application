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

ST_cardData_t card;
ST_terminalData_t terminal;
ST_transaction_t transaction;

ST_transaction_t transactionTestCases[6] = {
    {.cardHolderData = 
    {.cardHolderName =  "Ahmed Mohamed Mahmoud",
    .primaryAccountNumber = "1111111111111111", 
    .cardExpirationDate = "07/25"},
    .terminalData = {.transAmount = 5000} },  // case: 1

    {.cardHolderData = 
    {.cardHolderName =  "Mohamed Ali Samy Ibrahim",
    .primaryAccountNumber = "2222222222222222", 
    .cardExpirationDate = "08/26"},
    .terminalData = {.transAmount = 10000} }, // case: 2

    {.cardHolderData = 
    {.cardHolderName =  "Amr Zein Mohamed Ali",
    .primaryAccountNumber = "3333333333333333", 
    .cardExpirationDate = "03/27"},
    .terminalData = {.transAmount = 10000} 
    }, // case: 3

    {.cardHolderData = 
    {.cardHolderName =  "Sara Ahmed Mohamed Samir",
    .primaryAccountNumber = "4444444444444444", 
    .cardExpirationDate = "04/21"},
    .terminalData = {.transAmount = 5000} 
    }, // case: 4

    {.cardHolderData = 
    {.cardHolderName =  "Saly Mahmoud Zein Sayed",
    .primaryAccountNumber = "5555555555555555", 
    .cardExpirationDate = "05/28"},
    .terminalData = {.transAmount = 1000} 
    }, // case: 3
    };
    
void loadTestValues(ST_cardData_t *cardData, ST_terminalData_t *termData, 
ST_transaction_t source,char *testCase);

void appStart(){

    terminal.maxTransAmount = 8000;
    setMaxAmount(&terminal); // max withdraw amount.

    int mode = 0;
    
    printf(
    "0-Manual Inputs.\n"
    "[\"<NAME:[20-24]>\", \"<PAN:[16-19]>\", <DATE:MM/YY>, <MAX_AMOUNT:8000>]\n\n"
    "1-Transaction approved user story:\n"
    "[\"Ahmed Mohamed Mahmoud\", \"1111111111111111\", 07/25, 5000]\n\n"
    "2-Exceed the maximum amount user story:\n"
    "[\"Mohamed Ali Samy Ibrahim\", \"2222222222222222\", 08/26, 10000]\n\n"
    "3-Insufficient fund user story:\n"
    "[\"Amr Zein Mohamed Ali\", \"3333333333333333\", 03/27, 5000]\n\n"
    "4-Expired card user story:\n"
    "[\"Sara Ahmed Mohamed Samir\",  \"4444444444444444\", 04/21, 1000]\n\n"
    "5-Invalid card user story:\n"
    "[\"Saly Mahmoud\",\"5555555555555555\", 05/28, 1000]\n\n"
    "Please Enter Test Case Number: ");

    scanf("%d", &mode);
    getchar(); // eat away the '\n' left in stdin

    printf("\n");

    //--------------------------- Start Card Side ---------------------------
    switch (mode)
    {
        case 0:
            printf("Please Enter Your Name: ");
            if(getCardHolderName(&card) == WRONG_NAME){
                printf("WRONG_NAME!\n");
                exit(0);
            }
            printf("Please Enter Expiry Date: ");
            if(getCardExpiryDate(&card) == WRONG_EXP_DATE){
                printf("WRONG_EXP_DATE!\n");
                exit(0);
            }
            printf("Please Enter Card PAN: ");
            if(getCardPAN(&card) == WRONG_PAN){
                printf("WRONG_PAN!\n");
                exit(0);
            }
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

        default:
            printf("Wrong Case!");
            exit(0);
            break;
    }
    //------------------------------ End Card Side ------------------------------
    
    //--------------------------- Start Terminal Side ---------------------------
    if(isCardExpried(&card, &terminal) == EXPIRED_CARD){
        //printCardInfo(newCard);
        printf("EXPIRED_CARD!\n");
        exit(0);
    }
 
    if(mode == 0){
        printf("Please Enter Wanted Amount: ");
        if(getTransactionAmount(&terminal) == INVALID_AMOUNT){
            printf("INVALID_AMOUNT\n");
            exit(0); 
        }
    }
    
    //printf("\n");
    //printCardInfo(newCard);
    //printf("\n");
    
    if(!(isBelowMaxAmount(&terminal) == OK)){
        printf("EXCEED_MAX_AMOUNT!\n");
        exit(0);
    }
    //----------------------- End Terminal Side -------------------------
        
    //----------------------  Start Server Side -------------------------
    transaction.cardHolderData = card;
    transaction.terminalData = terminal;
    int transactionState = recieveTransactionData(&transaction);

    switch (transactionState)
    {
    case APPROVED:
        printf("Transaction State: APPROVED!.\n");
        break;
    
    case DECLINED_INSUFFECIENT_FUND:
        printf("Transaction State: DECLINED_INSUFFECIENT_FUND!.\n");
        break;

    case DECLINED_STOLEN_CARD:
        printf("Transaction State: DECLINED_STOLEN_CARD!\n");
        break;

    case INTERNAL_SERVER_ERROR:
        printf("Transaction State: INTERNAL_SERVER_ERROR!\n");
        break;

    default:
        break;
    }
    //--------------------------- Server Side ---------------------------
    
   

}


//------------------------------ Helper Functions ----------------------------------

void loadTestValues(ST_cardData_t *cardData, ST_terminalData_t *termData, 
ST_transaction_t source,char *testCase){
    printf("Loading \"%s\".\n", testCase);
    *cardData = source.cardHolderData;
    *termData = source.terminalData;
}
