#include"app.h"

int main(){
    appInit();

    while (1)
    {
        appStart();
        if(currentState() == END) break;
    }
    return 0;

 //  listSavedTransactionsTest(); 
}