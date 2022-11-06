#ifndef APP_HEADER
#define APP_HEADER

#include<stdio.h>
#include <unistd.h>
#include"../Card/card.h"
#include"../Server/server.h"
#include"../Terminal/terminal.h"
typedef enum EN_PAYMENT_STATE_t{
    CARD,TERMINAL,SERVER,END
}EN_PAYMENT_STATE_t; 

void appInit();
void appStart(void);
EN_PAYMENT_STATE_t currentState();
#endif 