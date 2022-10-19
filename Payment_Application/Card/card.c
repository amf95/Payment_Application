/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

task: Implement the card module.
1-Fill in card.h file with functions' prototypes and typedefs.
2-Implement getCardHolderName function.
3-Implement getCardExpiryDate function.
4-Implement getCardPAN function.

*/

#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    char buffer[BUFFER_SIZE + 1];
    printf("Please Enter Card Holder Name: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strlen(buffer) - 1] = '\0'; //get rid of '\n' added by fgets()

    if((buffer != NULL) && (strlen(buffer) >= NAME_MIN_SIZE) && 
    (strlen(buffer) < NAME_MAX_SIZE)){
        strcpy(cardData->cardHolderName, buffer);
        return CARD_OK;
    }
    else{
        return WRONG_NAME;
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    char buffer[BUFFER_SIZE + 1];
    printf("Please Enter Card Expiration Date: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strlen(buffer) - 1] = '\0'; //get rid of '\n' added by fgets()

    if(isValidDateFormat(buffer) == CARD_OK){
        strcpy(cardData->cardExpirationDate, buffer);
        return CARD_OK;
    }
    else{
        return WRONG_EXP_DATE;
    }

    
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    char buffer[BUFFER_SIZE +1];
    printf("Please Enter Card PAN: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strlen(buffer) - 1] = '\0'; //get rid of '\n' added by fgets()
    
    if(isValidPANFormat(buffer) == CARD_OK){
        strcpy(cardData->primaryAccountNumber, buffer);
        return CARD_OK;
    }
    else{
        return WRONG_PAN;
    }
}

EN_cardError_t isValidDateFormat(char *date){
    if((date != NULL) && (strlen(date) == EXPIRATION_DATE_SIZE) &&
    (date[DATE_SEPERATOR_INDEX] == '/')){
        
        for (int i = 0; i < EXPIRATION_DATE_SIZE; i++){
            if(date[i] == '/') continue;
            if(!(isdigit(date[i]))) {
                return WRONG_EXP_DATE;
            }
        }
        return CARD_OK;
    }
    else{
        return WRONG_EXP_DATE;
    }
}

EN_cardError_t isValidPANFormat(char *PAN){
    if((PAN != NULL) && (strlen(PAN) >= PAN_MIN_SIZE) && (strlen(PAN) <= PAN_MAX_SIZE)){

        for (int i = 0; i < strlen(PAN); i++){
            if(!(isdigit(PAN[i]))) return WRONG_PAN;
        }
        return CARD_OK;
    }
    else{
        return WRONG_PAN;
    }
}


/*
void printCardInfo(client_t newCard){
    printf(
        "\n---------------------- YOUR CARD/REQUEST INFO ----------------------\n"
        "\n{ Name: \"%s\", PAN: %s, Month: %d, Year: %d, Amount: %f }\n\n", 
        newCard.holderName, newCard.PAN, newCard.expiryMonth,
        newCard.expiryYear, newCard.balance);
}
*/