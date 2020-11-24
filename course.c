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

int findTraversal(courseBTNode *cur, char *name)
{
    if (cur == NULL) return 0;
    if ( (strstr(cur->course->name, name) != NULL) || (strstr(name, cur->course->name) != NULL)) return 1;
    int left = findTraversal(cur->left, name);
    if (left == 1) return 1;
    int right = findTraversal(cur->right, name);
    if (right == 1) return 1;
    return 0;

}

int findCourse(courseBT *cBT, char *name)
{
    return findTraversal(cBT->head, name);
}

course *getTraversal(courseBTNode *cur, char *name)
{
    if (cur == NULL) return NULL;
    if ( strstr(cur->course->name, name) != NULL) return cur->course;
    if (cur->left != NULL) 
    {
        course *course = getTraversal(cur->left, name);
        if (course != NULL) return course;
    }
    if (cur->right != NULL) 
    {
        course *course = getTraversal(cur->right, name);
        if (course != NULL) return course;
    }

}

course *getCourse(courseBT *cBT, char *name)
{
    if (cBT->head == NULL) return NULL;
    return getTraversal(cBT->head, name);
}

void insertCourseBT(courseBTNode *cur, courseBTNode *new)
{
    if (strcmp(cur->course->name, new->course->name) > 0)
    {
        if (cur->left == NULL) {cur->left = new; new->parent = cur; }
            else {insertCourseBT(cur->left, new);}
        return;
    }
    else
    {
        if (cur->right == NULL) {cur->right = new; new->parent = cur;}
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
    cBTNode->parent = NULL;
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

   
    if (cur->course != NULL) 
    { 
        if (cur->course->reqList != NULL) deleteLinkedListReq(cur->course->reqList);
        free(cur->course);
    }
    if (cur         != NULL) free(cur);
}

void deleteCourseBT(courseBT *cBT)
{
    if (cBT->head != NULL) freeBT(cBT->head);
    free(cBT);
    return;
}

void removeTraversal(courseBTNode *cur, char *name)
{
    if (cur == NULL) return;
    
    if (strcmp(cur->course->name, name) == 0)
    {
        if (cur->left == NULL && cur->right == NULL)
        {
            if (cur->parent->left == cur)
            {
                cur->parent->left = NULL;
            }
        }
    }
}
void removeCourse(courseBT *cBT, char *name)
{
    if (cBT->head != NULL) removeTraversal(cBT->head, name);
}