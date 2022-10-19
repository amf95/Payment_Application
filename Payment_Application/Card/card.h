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

#ifndef CARD_H
#define CARD_H

#include <stdint.h>

#define BUFFER_SIZE 32
#define NAME_MAX_SIZE 24
#define NAME_MIN_SIZE 20
#define DATE_SEPERATOR_INDEX 2
#define EXPIRATION_DATE_SIZE 5
#define PAN_MAX_SIZE 19
#define PAN_MIN_SIZE 16

typedef struct ST_cardData_t{
    uint8_t cardHolderName[NAME_MAX_SIZE + 1];
    uint8_t primaryAccountNumber[PAN_MAX_SIZE + 1];
    uint8_t cardExpirationDate[EXPIRATION_DATE_SIZE + 1];
}ST_cardData_t;

typedef enum EN_cardError_t{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
EN_cardError_t isValidDateFormat(char *date);
EN_cardError_t isValidPANFormat(char *PAN);

#endif