#ifndef STUDENT_HH
#define STUDENT_HH

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "course.h"

typedef struct student{
    char name[256];
    char degree[256];
    courseBT *  courses;
} student;

typedef struct studentBTNode{
    student *st;
    struct studentBTNode *left;
    struct studentBTNode *right;
}studentBTNode;

typedef struct studentBT{
    studentBTNode *head;
} studentBT;


studentBT* createStudentBT();

student* readStudentFile(FILE *);

student* getStudent(studentBT *, char *);

void addStudentToBT(studentBT *, student *);

void printStudentBT(studentBT *);

void deleteStudentBT(studentBT *);


#endif