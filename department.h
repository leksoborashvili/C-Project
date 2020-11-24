#ifndef DEPARTMENT_HH
#define DEPARTMENT_HH

#include <stdlib.h>
#include "course.h"

typedef struct department{
    char name[256];
    struct courseBT *cBT;

} department;

typedef struct departmentList{
    department **departments;
    int curSize;
    int maxSize;
} departmentList;

/**
 * prints out department
 */
void printDepartment(department *);
/**
 * allocates memory for department and returns pointer to it.
 */
departmentList* createDepartmentList();
/**
 * reads file and returns pointer to struct department containing all the information from a file.
 */
department* readDepartmentFile(FILE *);
/**
 * adds department to given list
 */
void addToDepartmentList(departmentList *, department *);
/**
 * prints department list
 */
void printDepartmentList(departmentList *);
/**
 * frees space recursively.
 */
void deleteDepartmentList(departmentList *);


#endif