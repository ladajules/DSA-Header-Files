#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Queue.h"

void initQueue(Queue *Q) {
    Q->arr.front = Q->arr.rear = -1;
    Q->front = Q->rear = NULL;
}

bool queueIsEmpty(Queue Q) {
    return (Q.arr.front == -1 && Q.arr.rear == -1) && (Q.front == NULL);
}

bool queueIsFull(Queue Q) {
    return ((Q.arr.rear + 2) % QUEUEMAX == Q.arr.front);
}


void queueFrontArray(Queue Q) { 
    if (Q.arr.front == -1) {
        printf("Queue is empty.\n");
    } else {
        printf("%-15s%-15s%-5c%-10d%-10s\n",
            Q.arr.data[Q.arr.front].name.LName,
            Q.arr.data[Q.arr.front].name.FName,
            Q.arr.data[Q.arr.front].name.Mi,
            Q.arr.data[Q.arr.front].YrLvl,
            Q.arr.data[Q.arr.front].Course
        );
    }
}

void queueFrontList(Queue Q) {
    if (Q.front == NULL) {
        printf("Queue is empty.\n");
    } else {
        printf("%-15s%-15s%-5c%-10d%-10s\n",
            Q.front->data.name.LName,
            Q.front->data.name.FName,
            Q.front->data.name.Mi,
            Q.front->data.YrLvl,
            Q.front->data.Course
        );
    }
}

bool queueIsUnique(Queue Q, Studtype data) {
    bool flag = true;
    
    Queue t = Q;
    while (t.arr.front != -1 && flag) {
        if (cmp(t.arr.data[t.arr.front], data)) {
            flag = false;
        } else {
            dequeueArr(&t);
            // if (t.arr.front == t.arr.rear) {
            //     t.arr.front = t.arr.rear = -1;
            // } else {
            //     t.arr.front = (t.arr.front + 1) % QUEUEMAX;
            // }
        }
    }
    
    bool iFoundYouBroo = true;
    llQUEUE *temp = Q.front;
    while (temp != NULL && iFoundYouBroo) {
        if (cmp(temp->data, data)) {
            iFoundYouBroo = false;
        } else {
            temp = temp->next;
        }
    }

    return flag && iFoundYouBroo;
}

void enqueueArr(Queue *Q, Studtype data) {
    if (Q->arr.front == -1) {
        Q->arr.front = Q->arr.rear = 0;
    } else {
        Q->arr.rear = (Q->arr.rear + 1) % QUEUEMAX;
    } 
    Q->arr.data[Q->arr.rear] = data;
}

void enqueueLL(Queue *Q, Studtype data) {
    llQUEUE *newNode = malloc(sizeof(llQUEUE));
    newNode->data = data;
    newNode->next = NULL;

    if (Q->front == NULL) {
        Q->front = Q->rear = newNode;
    } else {
        Q->rear->next = newNode;
        Q->rear = newNode;
    }
}

void dequeueArr(Queue *Q) {
    if (Q->arr.front == Q->arr.rear) {
        Q->arr.front = Q->arr.rear = -1;
    } else {
        Q->arr.front = (Q->arr.front + 1) % QUEUEMAX;
    }
}

void dequeueLL(Queue *Q) {
    if (Q->front == Q->rear) {
        Q->front = Q->rear = NULL;
    } else {
        Q->front = Q->front->next;
    }
}


void enqueueUnique(Queue *Q, Studtype data) {
    if (queueIsFull(*Q)) {
        printf("Queue is full.\n");
    } else {
        if (queueIsUnique(*Q, data)) {
            enqueueArr(Q, data);
            enqueueLL(Q, data);
            // if (Q->arr.front == -1) {
            //     Q->arr.front = Q->arr.rear = 0;
            // } else {
            //     Q->arr.rear = (Q->arr.rear + 1) % QUEUEMAX;
            // }
            // Q->arr.data[Q->arr.rear] = data;
            
            // llQUEUE *newNode = malloc(sizeof(llQUEUE));
            // newNode->data = data;
            // newNode->next = NULL;
            
            // if (Q->front == NULL) {
            //     Q->front = Q->rear = newNode;
            // } else {
            //     Q->rear->next = newNode;
            //     Q->rear = newNode;
            // }
            
            printf("Added.\n");
        } else {
            printf("Data is already in queue.\n");
        }
    }
}

void dequeueUnique(Queue *Q, Studtype data) {
    if (queueIsEmpty(*Q)) {
        printf("Queue is empty.\n");
    } else {
        // Array
        Queue tempQueue;
        initQueue(&tempQueue);
        bool flag = false;
        
        while (Q->arr.front != -1) {
            Studtype tempData = Q->arr.data[Q->arr.front];
            
            dequeueArr(Q);
            // if (Q->arr.rear == Q->arr.front) {
            //     Q->arr.front = Q->arr.rear = -1;
            // } else {
            //     Q->arr.front = (Q->arr.front + 1) % QUEUEMAX;
            // }
            
            if (!cmp(tempData, data)) {
                enqueueArr(Q, data);
                // if (tempQueue.arr.front == -1) {
                //     tempQueue.arr.front = tempQueue.arr.rear = 0;
                // } else {
                //     tempQueue.arr.rear = (tempQueue.arr.rear + 1) % QUEUEMAX;
                // }
                // tempQueue.arr.data[tempQueue.arr.rear] = tempData;
            } 
        }
        Q->arr = tempQueue.arr;
        
        // Linked list
        llQUEUE *temp = Q->front, *prev = NULL;
        bool goodbyeMahFren = false;
        
        while (temp != NULL && !goodbyeMahFren) {
            if (cmp(temp->data, data)) {
                goodbyeMahFren = true;
                if (prev == NULL) {
                    Q->front = temp->next;
                } else {
                    prev->next = temp->next;
                    if (temp == Q->rear) {
                        Q->rear = prev;
                    }
                }
                llQUEUE *toDel = temp;
                temp = temp->next;
                free(toDel);
            } else {
                prev = temp;
                temp = temp->next;
            }
        }
        
        printf("Deleted.\n");
    }
}

void displayQueue(Queue Q) {
    if (Q.arr.front == -1 && Q.front == NULL) {
        printf("Queue is empty.\n");
    } else {
        printf("\n=== Array Queue ===\n");
        Queue t = Q;
        printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
        while (t.arr.front != -1) {
            queueFrontArray(t);
            
            dequeueArr(&t);
            // if (t.arr.front == t.arr.rear) {
            //     t.arr.front = t.arr.rear = -1;
            // } else {
            //     t.arr.front = (t.arr.front + 1) % QUEUEMAX;
            // } // dequeueUnique(&t, t.arr.data[t.arr.front]);
        }

        printf("\n=== Linked-list Queue ===\n");
        llQUEUE *temp = Q.front;
        printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
        while (temp != NULL) {
            Queue t2 = Q;
            t2.front = temp;
            queueFrontList(t2);
            temp = temp->next;
        }
    }
    printf("\n");
}