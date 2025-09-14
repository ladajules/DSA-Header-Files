#ifndef STUDTYPE_H
#define STUDTYPE_H

typedef struct {
    char LName[15];
    char FName[15];
    char Mi;
} Name;

typedef struct {
    Name name;
    int YrLvl;
    char Course[10];
} Studtype, *StudPtr;

#endif