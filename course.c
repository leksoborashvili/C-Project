#include "course.h"


void printCourse(course* c)
{
    if (c == NULL) return;
    printf("%s\n", c->name);
    printf("%s\n", c->title);
    if (c->reqList != NULL) printListReq(c->reqList);
    printf("\n");
}

courseBT* createCourseBT()
{
    courseBT* cBT = (courseBT*) malloc(sizeof(courseBT));
    cBT->head = NULL;
    return cBT;
}


void insertCourseBT(courseBTNode *cur, courseBTNode *new)
{
    if (strcmp(cur->course->name, new->course->name) > 0)
    {
        if (cur->left == NULL) {cur->left = new; }
            else {insertCourseBT(cur->left, new);}
        return;
    }
    else
    {
        if (cur->right == NULL) {cur->right = new;}
            else {insertCourseBT(cur->right, new);}
        return;
    }
    
}
void addElementCourseBT(courseBT *cBT, course *c)
{
    courseBTNode* cBTNode = (courseBTNode*) malloc(sizeof(courseBTNode));
    cBTNode->course = c;
    cBTNode->left   = NULL;
    cBTNode->right  = NULL;
    if (cBT-> head == NULL)
    {
        cBT ->head = cBTNode;
        return;
    }
    insertCourseBT(cBT->head, cBTNode);
}



void PreOrder(courseBTNode *cur)
{
    if (cur == NULL) return;
    printCourse(cur->course);

    if (cur->left  != NULL) PreOrder(cur->left);
    if (cur->right != NULL) PreOrder(cur->right);
}
void printCourseBT(courseBT *cBT)
{
    if (cBT->head == NULL) return;

    PreOrder(cBT->head);
    
}

void freeBT(courseBTNode *cur)
{

    if (cur == NULL) return;

    if (cur ->left  != NULL) freeBT(cur->left);
    if (cur ->right != NULL) freeBT(cur->right);

    deleteLinkedListReq(cur->course->reqList);
    if (cur->course != NULL) free(cur->course);
    if (cur         != NULL) free(cur);
}

void deleteCourseBT(courseBT *cBT)
{
    if (cBT->head != NULL) freeBT(cBT->head);
    free(cBT);
    return;
}

