#ifndef COMMANDS_HH
#define COMMANDS_HH

#include <stdlib.h>
#include "degrees.h"
#include "department.h"
#include "requirements.h"
#include "course.h"
#include "student.h"
//Every Command in this one file.
void commandC(struct departmentList *, char *);
void commandD(struct degreeArrayList *, char *);
void commandS(struct departmentList *, struct degreeArrayList *, char *);
void commandPcourse(struct departmentList *, struct degreeArrayList *, char *);
void commandPdegree(struct degreeArrayList *, char *);
void commandPdepartment(struct departmentList *, char *);

void commandM(struct studentBT *, struct degreeArrayList *, char *);
void commandN(struct studentBT *, struct degreeArrayList *, struct departmentList *, char *);
void commandR(struct degreeArrayList *, struct departmentList *, char *);
#endif