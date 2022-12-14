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
    (strlen(buffer) <= NAME_MAX_SIZE)){
        strcpy(cardData->cardHolderName, buffer);
        return CARD_OK;
    }
    return WRONG_NAME;
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
    return WRONG_EXP_DATE;
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
    return WRONG_PAN;
}

EN_cardError_t isValidDateFormat(char *date){
    if((date == NULL) || (strlen(date) != EXPIRATION_DATE_SIZE) 
    || (date[DATE_SEPERATOR_INDEX] != '/')) return WRONG_EXP_DATE;


    for (int i = 0; i < EXPIRATION_DATE_SIZE; i++){
        if(date[i] == '/') continue;
        if(!(isdigit(date[i]))) return WRONG_EXP_DATE;
    }
    return CARD_OK;
}

EN_cardError_t isValidPANFormat(char *PAN){
    if((PAN == NULL) || (strlen(PAN) < PAN_MIN_SIZE) 
    || (strlen(PAN) > PAN_MAX_SIZE)) return WRONG_PAN;

    for (int i = 0; i < strlen(PAN); i++){
        if(!(isdigit(PAN[i]))) return WRONG_PAN;
    }
    return CARD_OK;
}


// added helper functons:


void formateCardInfo(ST_cardData_t card, char *log){

    snprintf(log, CARD_LOG_SIZE,
    "\n##########CARD###########\n"
    "cardHolderName: %s\n"
    "PAN: %s\n"
    "Expiration Date: %s\n"
    "#########################\n",
    card.cardHolderName,
    card.primaryAccountNumber,
    card.cardExpirationDate
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
            strcpy(str, "Unkown");
            break;
    }
}