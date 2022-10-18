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

#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include "../Card/card.h"

#define BUFFER_SIZE 32
#define TRANSACTION_DATE_SIZE 10

typedef struct ST_terminalData_t
{
float transAmount;
float maxTransAmount;
uint8_t transactionDate[TRANSACTION_DATE_SIZE + 1];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

#endif