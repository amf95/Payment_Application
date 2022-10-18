/*

Auther: Ahmed Mahmoud Fawzy.
Creation Date: 15-10-2022 Sat 10:30 AM.
Last Modification Date: 17-10-2022 Mon 17:00 PM  => Ahmed Fawzy.

task: Implement the application.
1-Fill in application.h file with functions' prototypes.
2-Implement appStart function.

*/

#ifndef SERVER_H
#define SERVER_H

#include "../modules/config.h"
#include "../modules/newTypes.h"

void loadTestValues(client_t *taget, client_t *source, char *testCase);
void appStart();

#endif
