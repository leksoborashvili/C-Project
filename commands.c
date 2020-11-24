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
            degree *deg = dList->degrees[i];
                    if (deg->reqs->head == NULL) return;
                    nodeReq *head = deg->reqs->head;
                    while(head->next != NULL)
                    {
                        printf("%s", head->data);
                        head = head->next;
                    }
                    printf("%s\n", head->data);
            return;
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
        linkedListReq *reqList = dList->degrees[i]->reqs;
        for(nodeReq *node = reqList->head;  node != NULL; node = node->next)
        {
            if (strstr(node->data, name) != NULL) {printf("%s\n", dList->degrees[i]->name); break;}
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
        for(nodeReq *node = degreeList->degrees[i]->reqs->head; node != NULL; node = node->next)
        {
            if ( strstr(node->data, name) != NULL)
            {
                printf("%s ", degreeList->degrees[i]->name);
                break;
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