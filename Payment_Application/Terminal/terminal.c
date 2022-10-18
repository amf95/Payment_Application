/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

task: Implement the terminal module.
1-Fill in terminal.h file with functions' prototypes and typedefs.
2-Implement getTransactionDate function.
3-Implement isCardExpried function.
4-Implement gatTransactionAmount function.
5-Implement isBelowMaxAmount function.
6-Implement setMaxAmount function.

*/

#include "terminal.h"
#include "../Card/card.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);
    char buffer[BUFFER_SIZE + 1];
    strftime(buffer, BUFFER_SIZE, "%d/%m/%Y", localTime);

    if(strlen(buffer) == TRANSACTION_DATE_SIZE){
        return OK;
    }
    else{
        return WRONG_DATE;
    }
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
    const char seperator[] = "/";   
    int cardExpiryMonth = atoi(strtok(cardData.cardExpirationDate, seperator));
    // added 2000 to get proper format (23 => 2023).
    int cardExpiryYear = atoi(strtok(NULL, seperator)) + 2000;

    int termCurrentDay = atoi(strtok(termData.transactionDate, seperator));
    int termCurrentMonth = atoi(strtok(NULL, seperator));
    int termCurrentYear = atoi(strtok(NULL, seperator));

    if((cardExpiryYear > termCurrentYear)){
        return OK;
    }
    else if((cardExpiryYear == termCurrentYear) 
    && (cardExpiryMonth >= termCurrentMonth)){
        return OK;
    }
    else{
        return EXPIRED_CARD;
    }
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    float amount = 0.0;
    printf("Please Enter Desired Amount: ");
    scanf("%f", &amount);
    getchar(); // eat away the '\n' left in stdin

    if(amount > 0.0){
        termData->transAmount = amount;
        return OK;
    }
    else{
        return INVALID_AMOUNT;
    }
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if(termData->transAmount <= termData->maxTransAmount){
        return OK;
    }
    else{
        return EXCEED_MAX_AMOUNT;
    }
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    float amount = 0.0;
    printf("Please Set Transaction Mac Amount: ");
    scanf("%f", &amount);
    getchar(); // eat away the '\n' left in stdin

    if(amount > 0.0){
        termData->maxTransAmount = amount;
        return OK;
    }
    else{
        return INVALID_MAX_AMOUNT;
    }
}




