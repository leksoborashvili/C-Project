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



void PrintTraversal(courseBTNode *cur)
{
    if (cur == NULL) return;
    printCourse(cur->course);
    if (cur->left  != NULL) PrintTraversal(cur->left);
    if (cur->right != NULL) PrintTraversal(cur->right);
}
void printCourseBT(courseBT *cBT)
{
    if (cBT->head == NULL) return;

    PrintTraversal(cBT->head);
    
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

void removeTraversal(courseBT *cBT, char *name)
{
    courseBTNode *cur = cBT->head;
    while (cur != NULL)
    {
    
        if (strcmp(cur->course->name, name) == 0)
        {
            courseBTNode *parent = cur->parent;
            //both children NULL
            if (cur->left == NULL && cur->right == NULL)
            {
                if (parent == NULL) 
                {
                    cBT->head = NULL;
                    return;
                }
                if (parent->left == cur)
                {
                    free(cur);
                    parent->left = NULL;
                } else
                {
                    free(cur);
                    parent->right = NULL;
                }
                return;
            }
            //case where left is not NULL and right is.
            if (cur->left != NULL && cur->right == NULL)
            {
                if (parent == NULL)
                {
                    cBT->head = cur->left;
                    cur->left->parent = NULL;
                    free(cur);
                    return;
                }
                if (parent->left == cur)
                {
                    parent->left = cur->left;
                    parent->left->parent = parent;
                    free(cur);
                    
                } else
                {
                    parent->right = cur->left;
                    parent->right->parent = parent;
                    free(cur);
                }
                return;
            }
            //case where Right is NULL left is not.
            if (cur->left == NULL && cur->right != NULL)
            {
                if (parent == NULL)
                {
                    cBT->head = cur->right;
                    cur->right->parent = NULL;
                    free(cur);
                    return;
                }
                if (parent->left == cur)
                {
                    parent->left = cur->right;
                    parent->left->parent = parent;
                    free(cur);
                    
                } else
                {
                    parent->right = cur->right;
                    parent->right->parent = parent;
                    free(cur);
                }
                return;
            }
            //case where both children are not NULL
            if (cur->right != NULL && cur->left != NULL)
            {
                courseBTNode *suc = cur->right;
                
                while(suc->left != NULL)
                {
                    suc = suc->left;
                }
                //remove successor from the bottom.
                //successor has right child has to be set 
                if (suc->right != NULL)
                {
                    if (suc->parent->left == suc)
                    {
                        suc->parent->left = suc->right;
                        suc->right->parent = suc->parent;
                    } else
                    {
                        suc->parent->right = suc->right;
                        suc->right->parent = suc->parent;
                    }
                } else //successor does not have right child.
                {
                    if (suc->parent->left == suc)
                    {
                        suc->parent->left = NULL;
                    } else
                    {
                        suc->parent->right = NULL;
                    }
                }

                if (parent == NULL)
                {
                    cBT->head = suc;
                    suc->right  = cur->right;
                    suc->left   = cur->left;
                    if (suc->right != NULL) suc->right->parent = suc;
                    if (suc->left  != NULL)  suc->left->parent = suc;
                    suc->parent = cur->parent;
                    free(cur);
                    return;
                }
                //replace cur node with successor.
                if (parent->left == cur)
                {
                    suc->right  = cur->right;
                    suc->left   = cur->left;
                    if (suc->right != NULL) suc->right->parent = suc;
                    if (suc->left  != NULL)  suc->left->parent = suc;
                    suc->parent = cur->parent;
                    cur->parent->left = suc;
                    free(cur);
                } else
                {
                    suc->right  = cur->right;
                    suc->left   = cur->left;
                    if (suc->right != NULL) suc->right->parent = suc;
                    if (suc->left  != NULL)  suc->left->parent = suc;
                    suc->parent = cur->parent;
                    cur->parent->right = suc;
                    free(cur);
                }
            }
        return;
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

void removeCourse(courseBT *cBT, char *name)
{

        if (cBT->head != NULL) removeTraversal(cBT, name);

}


void removeCourseReqTraversal(courseBTNode *cur, char *name)
{
    if (cur == NULL) return;
    if (cur-> left  != NULL) removeCourseReqTraversal(cur->left, name);
    if (cur-> right != NULL) removeCourseReqTraversal(cur->right, name);

    if (cur->course->reqList == NULL) return;

    for (nodeReq *node = cur->course->reqList->head; node != NULL; node = node->next )
    {   
        if (node == NULL) break;
        if (node->data == NULL) continue;

        if ( strcmp(node->data, name) == 0)
        {
            if (node->prev == NULL)
            {
                cur->course->reqList->head = node->next;
                break;
            }
            node->prev->next = node->next;
            if (node -> next != NULL) node->next->prev = node->prev;
            free(node);
            break;
        }
    }

}

void removeCourseFromReq(courseBT *cBT, char *name)
{
    if (cBT->head != NULL)  removeCourseReqTraversal(cBT->head, name);
}