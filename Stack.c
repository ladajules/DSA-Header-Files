#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

void initStack (STACK *S) {
    S->arr.top = -1;
    S->top = NULL;
}

Studtype stackPeekArray(arrSTACK S) {
    return S.stud[S.top];
    // printf("%-15s%-15s%-5c%-10d%-10s\n", 
    //     S.arr.stud[S.arr.top].name.LName, 
    //     S.arr.stud[S.arr.top].name.FName,
    //     S.arr.stud[S.arr.top].name.Mi,
    //     S.arr.stud[S.arr.top].YrLvl,
    //     S.arr.stud[S.arr.top].Course);
}

Studtype stackPeekList(llSTACK *S) {
    return S->data;
    // printf("%-15s%-15s%-5c%-10d%-10s\n", 
    //     S.top->data.name.LName, 
    //     S.top->data.name.FName,
    //     S.top->data.name.Mi,
    //     S.top->data.YrLvl,
    //     S.top->data.Course);
}

bool cmp(Studtype a, Studtype b) {
    return strcmp(a.name.LName, b.name.LName) == 0 &&
        strcmp(a.name.FName, b.name.FName) == 0 &&
        a.name.Mi == b.name.Mi;
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

bool stackIsUnique(STACK S, Studtype data) {
    STACK tempStack;
    initStack(&tempStack);
    bool isUnique = true;
    Studtype tempData;
    
    // array
    while (S.arr.top != -1 && isUnique) {
        tempData = stackPeekArray(S.arr);
        if (cmp(tempData, data)) {
            isUnique = false;
        }
        pushArr(&tempStack, tempData);
        popArr(&S);
    }
    
    while (tempStack.arr.top != -1) {
        Studtype giveDataBak = stackPeekArray(tempStack.arr);
        pushArr(&S, giveDataBak);
        popArr(&tempStack);
    }
    
    // linked list
    llSTACK *tempHead = NULL;
    while (S.top != NULL && isUnique) {
        tempData = stackPeekList(S.top);
        if (cmp(tempData, data)) {
            isUnique = false;
        }
        llSTACK *newNode = malloc(sizeof(llSTACK));
        newNode->data = tempData;
        newNode->next = tempHead;
        tempHead = newNode;
        popLL(&S);
    }
    
    while (tempHead != NULL) {
        pushLL(&S, tempHead->data);
        llSTACK *del = tempHead;
        tempHead = tempHead->next;
        free(del);
    }

    return isUnique;
}

void popUnique(STACK *S, Studtype data) {
    if (S->arr.top == -1 && S->top == NULL) {
        printf("Stack is empty.\n");
    } else {
        // array
        STACK tempStack;
        initStack(&tempStack);
        bool flag = false;
        
        while (S->arr.top != -1 && !flag) {
            Studtype tempData =  stackPeekArray(S->arr); // top of stack 
            
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
            Studtype giveBak = stackPeekArray(tempStack.arr);
            pushArr(S, giveBak);
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
        printf("Popped.\n");
    }
}

void pushUnique(STACK *S, Studtype data) {
    if (S->arr.top == STACKMAX - 1) {
        printf("Stack is full.\n");
    } else {
        STACK temp = *S;
        if (stackIsUnique(temp, data)) {
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

            printf("Pushed.\n");
        } else {
            printf("Data is already in the stack.\n");
        }
    }
}

void displayStack(STACK S) {
    if (S.arr.top == -1 && S.top == NULL) {
        printf("Stack is empty.\n");
    } else {
        printf("\n=== Array Stack ===\n");
        printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
        STACK tempStack;
        initStack(&tempStack);
        Studtype data;
        
        while (S.arr.top != -1) {
            data = stackPeekArray(S.arr);
            printf("%-15s%-15s%-5c%-10d%-10s\n", 
                data.name.LName, 
                data.name.FName,
                data.name.Mi,
                data.YrLvl,
                data.Course);
            pushArr(&tempStack, data);
            popArr(&S); //.arr.top--; 
        }
        
        while (tempStack.arr.top != -1) {
            Studtype givData = stackPeekArray(tempStack.arr);
            pushArr(&S, givData);
            popArr(&tempStack);
        }

        printf("\n=== Linked-list Stack ===\n");
        printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
        llSTACK *tempHead = NULL;
        
        while (S.top != NULL) {
            data = stackPeekList(S.top);
            printf("%-15s%-15s%-5c%-10d%-10s\n", 
                data.name.LName, 
                data.name.FName,
                data.name.Mi,
                data.YrLvl,
                data.Course);
            llSTACK *newNode = malloc(sizeof(llSTACK));
            newNode->data = data;
            newNode->next = tempHead;
            tempHead = newNode; 
            popLL(&S); // popLL(&t2); // t2.top = t2.top->next; 
        }
        
        while (tempHead != NULL) {
            pushLL(&S, tempHead->data);
            llSTACK *del = tempHead;
            tempHead = tempHead->next;
            free(del);
        }
    }
    printf("\n");
}
