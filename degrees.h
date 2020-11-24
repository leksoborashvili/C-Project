#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "requirements.h"

#ifndef DEGREES_HH
#define DEGREES_HH

typedef struct degree{
    char name[256];
    linkedListReq* reqs;
} degree;

typedef struct degreeArrayList{
    degree** degrees;
    int curSize;
    int maxSize;
    
} degreeArrayList;

/**
 * prints out a degree
 */
void printDegree(degree *);
/**
 * alocates memory on the heap for degreeArrayList and returns pointer to it
 */
degreeArrayList* createDegreeArrayList();
/**
 * reads File for a degree and returns degree pointer containing the information in the file.
 */
degree* readDegreeFile(FILE *);
/**
 * frees up all the memory alocated by degreeArrayList recursively.
 */
void deleteDegreeArrayList(degreeArrayList *);
/**
 * prints out degreeArrayList
 */
void printDegreeArrayList(degreeArrayList *);
/**
 * adds degree to degreeArrayList
 */
void addDegreeArrayList(degreeArrayList *, degree *);
#endif