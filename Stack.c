#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

void initStack (STACK *S) {
    S->arr.top = -1;
    S->top = NULL;
}

bool stackIsEmpty(STACK S) {
    return S.arr.top == -1 || S.top == NULL;
}

bool stackIsFull(STACK S) {
    return S.arr.top == STACKMAX - 1;
}

void stackPeekArray(STACK S) {
    printf("%-15s%-15s%-5c%-10d%-10s\n", 
        S.arr.stud[S.arr.top].name.LName, 
        S.arr.stud[S.arr.top].name.FName,
        S.arr.stud[S.arr.top].name.Mi,
        S.arr.stud[S.arr.top].YrLvl,
        S.arr.stud[S.arr.top].Course);
}

void stackPeekList(STACK S) {
    printf("%-15s%-15s%-5c%-10d%-10s\n", 
        S.top->data.name.LName, 
        S.top->data.name.FName,
        S.top->data.name.Mi,
        S.top->data.YrLvl,
        S.top->data.Course);
}

bool cmp(Studtype a, Studtype b) {
    return strcmp(a.name.LName, b.name.LName) == 0 &&
        strcmp(a.name.FName, b.name.FName) == 0 &&
        a.name.Mi == b.name.Mi;
}

bool stackIsUnique(STACK S, Studtype data) {
    bool flag = true;
    STACK t = S; 
    while (!stackIsEmpty(t) && flag == true) {
        if (cmp(t.arr.stud[t.arr.top], data) && cmp(t.top->data, data)) {
            flag = false;
        }
        t.arr.top--;
        t.top = t.top->next;
    }

    return flag;
}

void pushArr(STACK *S, Studtype data) { // new
    if (S->arr.top == STACKMAX - 1) {
        printf("Stack is full.\n");
    } else {
        S->arr.top++;
        S->arr.stud[S->arr.top] = data;
    }
}

void pushLL(STACK *S, Studtype data) { // new
    llSTACK *newNode = malloc(sizeof(llSTACK));
    newNode->data = data;
    newNode->next = S->top;
    S->top = newNode;
}

void popArr(STACK *S) { // new
    if (S->arr.top == -1) {
        printf("Stack is empty.\n");
    } else {
        S->arr.top--;
    }
}

void popLL(STACK *S) { // new
    if (S->top == NULL) {
        printf("Stack is empty.\n");
    } else {
        llSTACK *temp = S->top;
        S->top = S->top->next;
        free(temp);
    }
}

void popUnique(STACK *S, Studtype data) {
    if (stackIsEmpty(*S)) {
        printf("Stack is empty.\n");
    } else {
        // array
        STACK tempStack;
        initStack(&tempStack);
        bool flag = false;
        
        while (S->arr.top != -1 && !flag) {
            Studtype tempData =  S->arr.stud[S->arr.top]; // top of stack 
            
            if (cmp(tempData, data)) {
                flag = true;
            } else {
                pushArr(&tempStack, tempData);
                // tempStack.arr.top++; 
                // tempStack.arr.stud[tempStack.arr.top] = tempData;
            }
            popArr(S); // S->arr.top--; 
        }
        
        while (tempStack.arr.top != -1) {
            pushArr(S, tempStack.arr.stud[tempStack.arr.top]);
            // S->arr.top++;
            // S->arr.stud[S->arr.top] = tempStack.arr.stud[tempStack.arr.top];
            popArr(&tempStack); // tempStack.arr.top--;
        }
        
        // linked list
        llSTACK *curr = S->top;
        llSTACK *prev = NULL;
        bool iFoundItHEHE = false;

        while (curr != NULL && !iFoundItHEHE) {
            if (cmp(curr->data, data)) {
                if (prev == NULL) {
                    S->top = curr->next;
                } else {
                    prev->next = curr->next;
                }

                llSTACK *toDel = curr;
                curr = curr->next; 
                free(toDel);
                iFoundItHEHE = true; 
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
}

void pushUnique(STACK *S, Studtype data) {
    if (stackIsFull(*S)) {
        printf("Stack is full.\n");
    } else {
        if (stackIsUnique(*S, data)) {
            //array
            pushArr(S, data);
            // S->arr.top++;
            // S->arr.stud[S->arr.top] = data;

            //linked list
            pushLL(S, data);
            // llSTACK *newNode = malloc(sizeof(llSTACK));
            // newNode->data = data;
            // newNode->next = S->top;
            // S->top = newNode;

            printf("Added.\n");
        } else {
            printf("Data is already in the stack.\n");
        }
    }
}

void displayStack(STACK S) {
    if (stackIsEmpty(S)) {
        printf("Stack is empty.\n");
    } else {
        printf("\n=== Array Stack ===\n");
        STACK t = S;
        printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
        while (!stackIsEmpty(t)) {
            stackPeekArray(t);
            popArr(&t); //.arr.top--; 
        }

        printf("\n=== Linked-list Stack ===\n");
        STACK t2 = S;
        printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
        while (!stackIsEmpty(t2)) {
            stackPeekList(t2);
            popLL(&t2); // t2.top = t2.top->next; 
        }
    }
}
