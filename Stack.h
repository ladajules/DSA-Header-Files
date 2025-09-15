#ifndef STACK_H
#define STACK_H
#include "Studtype.h"

#define STACKMAX 10

typedef struct {
    Studtype stud[STACKMAX];
    int top;
} arrSTACK;

typedef struct stackNode {
    Studtype data;
    struct stackNode *next;
} llSTACK;

typedef struct {
    arrSTACK arr;
    llSTACK *top;
} STACK;

void initStack(STACK *S);
void popUnique(STACK *S, Studtype data);
void pushUnique(STACK *S, Studtype data);
void displayStack(STACK S);
bool stackIsEmpty(STACK S);
bool stackIsFull(STACK S);
Studtype stackPeekArray(STACK S);
Studtype stackPeekList(STACK S);
bool stackIsUnique(STACK S, Studtype data);
bool cmp(Studtype a, Studtype b);
void pushArr(STACK *S, Studtype data);
void pushLL(STACK *S, Studtype data);
void popArr(STACK *S);
void popLL(STACK *S);

#endif
