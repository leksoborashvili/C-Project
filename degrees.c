#include "degrees.h"


void printDegree(degree *deg)
{
    if (deg == NULL) return;
    printf("%s\n", deg->name);
    for (int i = 0; i < deg->size; i++ )
    {
        if (deg->req[i]->size > 1) printf("OR ");
        for (int j = 0; j < deg->req[i]->size; j ++)
        {
            printf("%s ", deg->req[i]->reqCourses[j]->course);
        }
        printf("\n");
    }
    printf("\n");
    return;
}


degreeArrayList* createDegreeArrayList()
{
    degreeArrayList *degreeList = (degreeArrayList*) malloc(sizeof(degreeArrayList));
    degreeList->degrees = (degree**) malloc(sizeof(degree*) * 10);
    degreeList->curSize = 0;
    degreeList->maxSize = 10;
    return degreeList;
}

void printDegreeArrayList(degreeArrayList *degreeList)
{

    for (int i = 0; i < degreeList->curSize; i++)
    {
        if (degreeList->degrees[i] != NULL) printDegree(degreeList->degrees[i]);
    }
    return;
}

void addDegreeArrayList(degreeArrayList *degreeList, degree* deg)
{
    //size increase check here.
    if (degreeList->curSize == (degreeList->maxSize - 1) ) 
    {
        degreeList->maxSize += 10;
        degree **degreesNew = (degree**) malloc(sizeof(degree*) * degreeList->maxSize);
        for(int i = 0; i < degreeList->curSize; i++)
        {
            degreesNew[i] = degreeList->degrees[i];
        }
        free(degreeList->degrees);
        degreeList->degrees = degreesNew;
        
    }
    degreeList->degrees[degreeList->curSize] = deg;
    degreeList->curSize++;
    
}

void deleteDegree(degree *d)
{
    //frees space recursively.
    for (int i = 0; i < d->size; i ++)
    {
        for (int j = 0; j <= d->req[i]->size; j++)
        {
            free(d->req[i]->reqCourses[j]);
        }
        free(d->req[i]->reqCourses);
        free(d->req[i]);
    }
    free(d->req);
    free(d);
    return;
}

void deleteDegreeArrayList(degreeArrayList *degreeList)
{
    for(int i = 0; i < degreeList->curSize; i++)
    {
        //frees space recursively.
        deleteDegree(degreeList->degrees[i]);
    }
    free(degreeList->degrees);
    free(degreeList);
    return;
}

degree* readDegreeFile(FILE *file)
{
    char s[256];
    degree *deg  = (degree*) malloc( sizeof(degree));
    fgets(s, 256, file);
    char *t = strtok(s, "\n");
    strncpy(deg->name, t, 256);
    requirements **reqs = (requirements **) malloc( sizeof(requirements*) * 10);
    
    int sizeReqs = 0;

    while ( fgets( s, 256, file ) != NULL ) 
    { 
        reqs[sizeReqs] = (requirements *) malloc (sizeof(requirements) );
        reqs[sizeReqs]->reqCourses = (reqCourse**) malloc (10 * sizeof(reqCourse*) );
        char *token = strtok(s, " ");
        int size = 0;
        if (strcmp(token, "OR") == NULL) 
        {
            while(token!=NULL)
            {
                reqs[sizeReqs]->reqCourses[size] = (reqCourse *) malloc (sizeof (reqCourse));
                token = strtok(NULL, ", ");
                if (token == NULL) break;
                strcpy(reqs[sizeReqs]->reqCourses[size]->course, token);
                token = strtok(NULL, ", ");
                if (token == NULL) break;
                strcat(reqs[sizeReqs]->reqCourses[size]->course, " ");
                strcat(reqs[sizeReqs]->reqCourses[size]->course, token);

                //removes endline if there is one.
                if (reqs[sizeReqs]->reqCourses[size]->course[strlen(reqs[sizeReqs]->reqCourses[size]->course) - 1] == '\n')
                {
                reqs[sizeReqs]->reqCourses[size]->course[strlen(reqs[sizeReqs]->reqCourses[size]->course) - 1] = 0;
                }

                size++;
            }
            
        } else
        {
            reqs[sizeReqs]->reqCourses[size] = (reqCourse *) malloc (sizeof (reqCourse));
            strcpy(reqs[sizeReqs]->reqCourses[0], token);
            token = strtok(NULL, ", ");
            if (token == NULL) break;
            strcat(reqs[sizeReqs]->reqCourses[size]->course, " ");
            strcat(reqs[sizeReqs]->reqCourses[size]->course, token);

            //removes endline if there is one.
            if (reqs[sizeReqs]->reqCourses[size]->course[strlen(reqs[sizeReqs]->reqCourses[size]->course) - 1] == '\n')
            {
                reqs[sizeReqs]->reqCourses[size]->course[strlen(reqs[sizeReqs]->reqCourses[size]->course) - 1] = 0;
            }

            size++;
        }
        reqs[sizeReqs]->size = size;
        sizeReqs ++;
    }
    deg->size = sizeReqs;
    deg->req = reqs;
    return deg;
}

degree* getDegree(degreeArrayList *dList, char *name)
{
    for (int i = 0; i < dList->curSize; i++ )
    {
        if ( strcmp(dList->degrees[i]->name, name) == 0 )  return dList->degrees[i];
    }

    return NULL;
}