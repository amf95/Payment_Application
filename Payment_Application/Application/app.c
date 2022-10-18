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

#include "application.h"
#include "../modules/card.h"
#include "../modules/terminal.h"
#include "../modules/server.h"
#include "../modules/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

client_t newCard;

client_t testCards[6] = {
    {"Ahmed Fawzy", "1111111111111111", 7, 2025, 5000},  // case: 1
    {"Mohamed Ali", "2222222222222222", 8, 2026, 10000}, // case: 2
    {"Amr Zein",    "3333333333333333", 5, 2027, 5000},  // case: 3
    {"Sara Ahmed",  "4444444444444444", 6, 2021, 1000},  // case: 4
    {"Saly Mahmoud","5555555555555555", 6, 2028, 1000}  // case: 5
    };
    

void appStart(){

    setMaxAmount(8000); // max withdraw amount.

    int mode = 0;
    
    printf(
    "0-Manual Inputs.\n"
    "{\"<NAME>\", \"xxxxxxxxxxxxxxxx\", xx, xx, xxxx}\n\n"
    "1-Transaction approved user story:\n"
    "{\"Ahmed Fawzy\", \"1111111111111111\", 7, 2025, 5000}\n\n"
    "2-Exceed the maximum amount user story:\n"
    "{\"Mohamed Ali\", \"2222222222222222\", 8, 2026, 10000}\n\n"
    "3-Insufficient fund user story:\n"
    "{\"Amr Zein\",    \"3333333333333333\", 5, 2027, 5000}\n\n"
    "4-Expired card user story:\n"
    "{\"Sara Ahmed\",  \"4444444444444444\", 6, 2021, 1000}\n\n"
    "5-Invalid card user story:\n"
    "{\"Saly Mahmoud\",\"5555555555555555\", 6, 2028, 1000}\n\n"
    "Please Enter Test Case Number: ");

    scanf("%d", &mode);
    getchar(); // eat away the '\n' left in stdin

    printf("\n");

    //--------------------------- Start Card Side ---------------------------
    switch (mode)
    {
        case 0:
            printf("Please Enter Your Name: ");
            getCardHolderName(&newCard);
            printf("Please Enter Expiry Date: ");
            getCardExpiryDate(&newCard);
            printf("Please Enter Card PAN: ");
            getCardPAN(&newCard);
            break;

        case 1:
            loadTestValues(&newCard, &testCards[mode-1], "Transaction approved user story");

            break;

        case 2:
            loadTestValues(&newCard, &testCards[mode-1], "Exceed the maximum amount user story");
            break;

        case 3:
            loadTestValues(&newCard, &testCards[mode-1], "Insufficient fund user story");    
            break;

        case 4:
            loadTestValues(&newCard, &testCards[mode-1], "Expired card user story");
            break; 

        case 5:
            loadTestValues(&newCard, &testCards[mode-1], "Invalid card user story");
            break;       

        default:
            printf("Wrong Case!");
            exit(0);
            break;
    }
    //------------------------------ End Card Side ------------------------------
    
    //--------------------------- Start Terminal Side ---------------------------
    if(isCardExpried(newCard)){
        printCardInfo(newCard);
        printf("Expired Card!\n");
        exit(0);
    }
 
    if(mode == 0){
        printf("Please Enter Wanted Amount: ");
        getTransactionAmount(&newCard);
    }
    
    printf("\n");
    printCardInfo(newCard);
    printf("\n");
    
    if(isBelowMaxAmount(newCard)){
    //----------------------- End Terminal Side -------------------------
        
        //----------------------  Start Server Side -------------------------
        recieveTransactionData(newCard);

        if(isValidAccount()){
            if(isAmountAvailable()){
                printf("Account Info Before Saving:\n");
                printClientInfo();
                
                saveTransaction();

                printf("Account Info After Saving:\n");
                printClientInfo();
            }
            else{
                printf("Insuffecient Funds!\n");
                exit(0);
            }
        }
        else{
            printf("Invalid Account!\n");
            exit(0);
        }

        //--------------------------- Server Side ---------------------------
    }
    else{
        printf("Exceeded Maximum Withdraw Amount!\n");
        exit(0);
    }

}

//---------------------------------------------------------------------

void loadTestValues(client_t *taget, client_t *source, char *testCase){
    printf("Loading \"%s\".\n", testCase);
    strcpy(taget->holderName, source->holderName);
    strcpy(taget->PAN, source->PAN);
    taget->expiryMonth = source->expiryMonth;
    taget->expiryYear = source->expiryYear;
    taget->balance = source->balance;
}