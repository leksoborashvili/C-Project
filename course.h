#ifndef COURSE_HH
#define COURSE_HH

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "requirements.h"
#include "department.h"
#include "degrees.h"

typedef struct course{
    char name[256];
    char title[256];
    linkedListReq *reqList;
} course;

typedef struct courseBTNode{
    course *course;
    struct courseBTNode *left;
    struct courseBTNode *right;
} courseBTNode;

typedef struct courseBT{
    courseBTNode *head;
} courseBT;

void printCourse(course *);

/** 
 * returns pointer to alocated course Binary Tree
 */
courseBT* createCourseBT();

/**
 * adds element to given course Binary Tree
 */
void addElementCourseBT(courseBT *, course *);

/**
 * prints out courses 
 */
void printCourseBT(courseBT *);

/**
 * deletes every pointer allocated by createCourseBT(). works recursively to free everything.
 */
void deleteCourseBT(courseBT *);


#endif