#include "student.h"




studentBT* createStudentBT()
{
    studentBT *sBT = (studentBT*) malloc( sizeof ( studentBT) );

    sBT->head = NULL;

    return sBT;
}

void insertStudent(studentBTNode *cur, studentBTNode *new)
{
    if ( strcmp(cur->st->name, new->st->name) > 0)
    {
        if (cur->left == NULL) 
            {
                cur->left = new; 
                return;
            }   else 
            {
                insertStudent(cur->left, new);
            }
    }   else
    {
        if (cur->right == NULL)
        {
            cur->right = new;
            return;
        }   else
        {
            insertStudent(cur->right, new);
        }
        
    }
    
}
void addStudentToBT(studentBT *sBT, student *st)
{
    studentBTNode *node = (studentBTNode*) malloc( sizeof ( studentBTNode) );
    node->st    = st;
    node->left  = NULL;
    node->right = NULL;
    if (sBT->head == NULL) { sBT->head = node; return;}
    insertStudent(sBT->head, node);
}


void preOrderPrint(studentBTNode *cur)
{
    if (cur == NULL) return;
    if (cur->st != NULL) 
    {
        printf("%s\n", cur->st->name);
        printf("%s\n", cur->st->degree);
        printCourseBT(cur->st->courses);
    }
    if (cur->left !=NULL) preOrderPrint(cur->left);
    if (cur->right !=NULL) preOrderPrint(cur->right);

}
void printStudentBT(studentBT *sBT)
{
    if (sBT->head != NULL) preOrderPrint(sBT->head);
}


void preOrderDelete(studentBTNode *cur)
{
    if (cur == NULL) return;
    deleteCourseBT(cur->st->courses);
    preOrderDelete(cur->left);
    preOrderDelete(cur->right);

    if (cur->st    != NULL) free(cur->st);
    if (cur->left  != NULL) free(cur->left);
    if (cur->right != NULL) free(cur->right);
}
void deleteStudentBT(studentBT *sBT)
{
    if (sBT->head != NULL) preOrderDelete(sBT->head);
    free(sBT);

}