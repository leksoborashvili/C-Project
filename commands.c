#include "commands.h"





/**
 * goes through department list and looks up a course with given name
 */ 
void commandC(departmentList *dList, char *name)
{
    for (int i = 0; i < dList->curSize; i++)
    {
        courseBT *curCBT = dList->departments[i]->cBT;
        courseBTNode *cur = curCBT->head;
        while(cur !=NULL)
        {
            if (strcmp(cur->course->name, name) == 0)
            {
                printf("%s\n", cur->course->title);
                printListReq(cur->course->reqList);
                printf("\n");   
                return;
            }
            if (strcmp(cur->course->name, name) > 0 )
            {
                cur = cur->left;
            } else
            {
                cur = cur->right;
            }
        
    }
    }
    printf("NOT FOUND\n");
}

/**
 * goes through degree list and prints out the requirements
 */
void commandD(degreeArrayList *dList, char *name)
{
    for (int i = 0; i < dList->curSize; i ++)
    {
        if (strcmp(name, dList->degrees[i]->name) == 0)
        {
            printDegree(dList->degrees[i]);
            return ;
        }
    }
    printf("NOT FOUND\n");
}


/**
 * checks for which degrees is course required for.
 */
void commandSdegree(struct degreeArrayList *dList, char *name)
{
    for ( int i = 0; i < dList->curSize; i ++)
    {
        requirements **reqList = dList->degrees[i]->req;
        degree *d = dList->degrees[i];
        for(int j = 0; j < d->size; j++)
        {
            for (int k = 0; k < d->req[j]->size; k++)
            {
                if (strcmp(d->req[j]->reqCourses[k]->course, name) == 0) {printf("%s\n", dList->degrees[i]->name); break;}
            }
        }
    }
    
}



void searchReq(courseBTNode *cur, char *name)
{
    if (cur == NULL) return;
    linkedListReq *reqs = cur->course->reqList;
    for(nodeReq *node = reqs->head; node != NULL; node = node->next)
    {
        if (strstr(node->data, name) != NULL)
        {
            printf("%s ", cur->course->name);
            break;
        }
    }
    searchReq(cur->left, name);
    searchReq(cur->right, name);
}
/** 
 * checks for which classes can be taken in the department.
 */
void commandSdepartment(struct departmentList *dList, char *name)
{
    for (int i = 0; i < dList->curSize; i ++)
    {
        courseBT *cBT = dList->departments[i]->cBT;
        courseBTNode *cur = cBT->head;

        searchReq(cur, name);
    }
    printf("\n");
}

/**
 * goes through degree and department list and print all the effects
 */
void commandS(struct departmentList *departmentList, struct degreeArrayList *degreeList, char *name)
{
    commandSdepartment(departmentList, name);
    commandSdegree(degreeList, name);
    printf("\n");
}

/**
 * goes and prints the department/degree/pre-reqs for the course
 */
void commandPcourse(departmentList *departmentList, degreeArrayList *degreeList, char *name)
{


    printf("departmnet: ");
    for (int i = 0; i < departmentList->curSize; i++)
    {
        courseBT *cBT = departmentList->departments[i]->cBT;
        courseBTNode *cur = cBT -> head;

        while( cur!= NULL)
        {
            if (strcmp(cur->course->name, name) == 0)
            {
                printf(departmentList->departments[i]->name);
                printf("\npre-reqs: ");
                printListReq(cur->course->reqList);
                break;
            }

            if (strcmp(cur->course->name, name) > 0)
            {
                cur = cur->left;
            }else
            {
                cur = cur->right;
            }
        }
    }
    printf("degree: ");
    for(int i = 0; i < degreeList->curSize; i ++)
    {
        degree *d = degreeList->degrees[i];
        requirements **reqList = degreeList->degrees[i]->req;
        for(int j = 0; j < d->size; j++)
        {
            for (int k = 0; k < d->req[j]->size; k++)
            {
                if (strstr(d->req[j]->reqCourses[k]->course, name) != NULL) { printf("%s ", d->name);}
            }
        }
    }
    printf("\n\n");


}
/**
 * prints out department
 */
void commandPdepartment(departmentList *dList, char *name)
{
    for (int i = 0; i < dList->curSize; i ++)
    {
        if ( strstr(dList->departments[i]->name, name) !=NULL)
        {
            printDepartment(dList->departments[i]);
            break;
        }
    }
    printf("\n");
}  
/**
 * prints out degree
 */
void commandPdegree(degreeArrayList *dList, char *name)
{
    for(int i = 0; i < dList->curSize; i ++)
    {
        if ( strstr(dList->degrees[i]->name, name) != NULL)
        {
            printDegree(dList->degrees[i]);
            break;
        }
    }
    printf("\n");
}


void commandM(studentBT *sBT, degreeArrayList *dList, char *name)
{
    student *st = getStudent(sBT, name);
    if (st == NULL) {printf("STUDENT NOT FOUND\n"); return;}
    degree *d = getDegree(dList, st->degree);
    if (d == NULL) {printf("NO INFO ABOUT DEGREE\n"); return;}
    for (int i = 0; i < d->size; i ++)
    {
        int x = 0;
        for (int j = 0; j < d->req[i]->size; j++)
        {
            if (findCourse(st->courses, d->req[i]->reqCourses[j]->course) == 1)
            {
                x = 1;
            }
            
        }
        //if x == 1 dont have to take any of this courses.
        if ( x == 1) continue;
        if (d->req[i]->size > 1) printf("OR ");
        for (int j = 0; j < d->req[i]->size; j++)
        {
            printf("%s ", d->req[i]->reqCourses[j]->course);
            
        }
        printf("\n");
    }

}

//will not print courses that we have not data about in the departments since we don't know pre-reqs.
void commandN(studentBT *sBT, degreeArrayList *degList, departmentList *depList, char *name)
{
    student *st = getStudent(sBT, name);
    if (st == NULL) {printf("STUDENT NOT FOUND\n"); return;}
    degree *deg = getDegree(degList, st->degree);
    if (deg == NULL) {printf("NO INFO ABOUT DEGREE\n"); return;}

    for (int i = 0; i < deg->size; i ++)
    {
        int x = 0;
        for (int j = 0; j < deg->req[i]->size; j++)
        {
            if (findCourse(st->courses, deg->req[i]->reqCourses[j]->course) == 1)
            {
                x = 1;
            }
            
        }
        //if x == 1 dont have to take any of this courses.
        if ( x == 1) continue;
        //we have to look for the courses in every department.
        for (int j = 0; j < depList->curSize; j++)
        {
            department *dep = depList->departments[j];
            for (int k = 0; k < deg->req[i]->size; k++)
            {
                course* c = getCourse(dep->cBT, deg->req[i]->reqCourses[k]->course);
                if (c == NULL) break;
                int y = 0;
                for (nodeReq *node = c->reqList->head; node != NULL; node = node->next)
                {
                    y = y || findCourse(st->courses, node->data);
                }
                if (y == 1 || c->reqList->head == NULL)
                {
                    printf("%s\n", c->name);
                }
            }
            
        }
    }
    printf("\n");

}


void commandR(degreeArrayList *degList, departmentList *depList, char *name)
{
    department *dep = getDepartment(depList, name);
    if (dep == NULL) {printf("DEPARTMENT NOT FOUND\n"); return;}

    
}