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
    struct courseBTNode *parent;
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
 * returns 1 if given course is in the list
 * 0 if it is not
 */
int findCourse(courseBT *, char *);

void removeCourse(courseBT *, char *);
/**
 * returns pointer to the course with provided name
 * NULL if course does with given name does not exist
 */
course *getCourse(courseBT *, char *);
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