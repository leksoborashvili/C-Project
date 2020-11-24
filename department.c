#include "department.h"


departmentList* createDepartmentList()
{
    departmentList *dList = (departmentList*) malloc( sizeof( departmentList ));
    dList->departments = (department**) malloc( sizeof( department*) * 10);
    dList->curSize = 0;
    dList->maxSize = 10;
    return dList;
}

void deleteDepartmentList(departmentList *dList)
{
    for (int i = 0; i < dList->curSize; i++)
    {
        //recursively frees space
        deleteCourseBT(dList->departments[i]->cBT);
        free(dList->departments[i]);
    }
    free(dList->departments);
    free(dList);
}

void addToDepartmentList(departmentList *dList, department *d)
{
    //checks if the arraylist sie needs to be increased.
    if (dList ->curSize == (dList->maxSize - 1) )
    {
        dList->maxSize += 10;
        dList->departments = (department**) realloc( dList->departments, sizeof( department*) * dList->maxSize);
        
    }
    dList->departments[dList->curSize] = d;
    dList->curSize ++;
}

void printDepartment(department *d)
{
    printf("%s\n", d->name);
    printCourseBT(d->cBT);
}

void printDepartmentList(departmentList *dList)
{
    for (int i = 0; i < dList->curSize; i ++)
    {
        printDepartment(dList->departments[i]);
        // printf("\n");
    }
    printf("\n\n");
}

department* readDepartmentFile(FILE *file)
{
    char s[256];
    fgets(s, 256, file);
    // printf("%s\n", s);
    department *d = (department*) malloc (sizeof ( department) );
    if (s != NULL)
    {
        char *token = strtok(s, "\n");
        strcpy(d->name, token);
    }
    courseBT *courseBT = createCourseBT();
    
    while(fgets(s, 256, file) != NULL)
    {
        course *c = (course*) malloc(sizeof(course));
        linkedListReq *reqs = createLinkedListReq();
        //reading name of the course.
        char *t = strtok(s, "\n");      //removes endline
        strcpy(c->name, t);
        //reading title of the course
        fgets(s, 256, file);
        t = strtok(s, "\n");            //removes endline
        strcpy(c->title, t);
        //reading requirements.
        fgets(s, 256, file);
        char *token;
        token = strtok(s, " ");
        if (strcmp(token, "OR") == 0 ) {token = strtok(NULL, " ");}
        
        char b[16];

        if (token != NULL) {strcpy(b, token);}
        token = strtok(NULL, ", ");
        strcat(b, " ");
        if (token != NULL) strcat(b, token);
        //printf("%s\n", b);

        if (strcmp(b, "\n ") != 0) addLastNodeReq(reqs, b);
        //parsing all the requirements using strtok();
        while(token != NULL)
        {
            token = strtok(NULL, " ");
            char b[16];
            if (token == NULL ) break;
            strcpy(b, token);
            token = strtok(NULL, ", ");
            strcat(b, " ");
            if (token == NULL ) break;
            strcat(b, token);
            //printf("%s\n", b);
            addLastNodeReq(reqs, b);
        }
        c->reqList = reqs;
        addElementCourseBT(courseBT, c);
    }
    
    d->cBT = courseBT;
    return d;
}