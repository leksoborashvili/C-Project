#include "degrees.h"


void printDegree(degree *deg)
{
    if (deg == NULL) return;
    printf("%s\n", deg->name);
    if (deg->reqs != NULL) 
    {
        if (deg->reqs->head == NULL) return;
        nodeReq *head = deg->reqs->head;
        while(head->next != NULL)
        {
            printf("%s", head->data);
            head = head->next;
        }
        printf("%s\n", head->data);
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
    deleteLinkedListReq(d->reqs);
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
    degree        *deg  = (degree*) malloc( sizeof(degree));
    linkedListReq *reqs = createLinkedListReq();
    fgets(s, 256, file);
    char *t = strtok(s, "\n");
    strncpy(deg->name, t, 256);
    while ( fgets( s, 256, file ) != NULL ) 
    { 
        // if (s[0] == 'O' && s[1] == 'R') b= s + 3;
        addLastNodeReq(reqs, s);
    } 
    deg->reqs = reqs;
    return deg;
}