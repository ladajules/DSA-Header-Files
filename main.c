//#include <stdio.h>
#include <stdbool.h>
#include "Studtype.h"
#include "Stack.h"
#include "Queue.h"
#include "CursorBased.h"
#include "CBStack.h"
//#include "CBQueue.h"

int main() {
    Studtype data = {{"Gimenez", "Jules", 'L'}, 2, "BSIT"};
    STACK S; Queue Q; VHeap VH; CBStack CBS;

    Studtype data1 = {{"Doe", "John", 'T'}, 1, "BSCS"};
    Studtype data2 = {{"Garcia", "Geroge", 'Y'}, 3, "BSCS"};
    Studtype data3 
    = {{"Gonazles", "Tri", 'G'}, 4, "BSIS"};
    Studtype data4 = {{"Montaromas", "Yu", 'P'}, 2, "BSCS"};

    initStack(&S);
    initQueue(&Q);

    // testing purposes
    pushUnique(&S, data1);
    pushUnique(&S, data2);
    pushUnique(&S, data3);
    pushUnique(&S, data4);
    enqueueUnique(&Q, data1);
    enqueueUnique(&Q, data2);
    enqueueUnique(&Q, data3);
    enqueueUnique(&Q, data4);

    pushUnique(&S, data);
    enqueueUnique(&Q, data);

    displayStack(S);
    displayQueue(Q);

    popUnique(&S, data);
    dequeueUnique(&Q, data);

    displayStack(S);
    displayQueue(Q);
    
    // CURSOR-BASED
    initVHeap(&VH);
    CBinitStack(&CBS);
    
    CBpushUnique(&VH, &CBS, data);
    CBpushUnique(&VH, &CBS, data1);
    CBpushUnique(&VH, &CBS, data2);
    CBpushUnique(&VH, &CBS, data3);
    CBpushUnique(&VH, &CBS, data4);
    
    CBdisplayStack(&VH, &CBS);
    
    CBpopUnique(&VH, &CBS, data);
    CBdisplayStack(&VH, &CBS);

    return 0;
}