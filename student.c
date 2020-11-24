#include "student.h"




studentBT* createStudentBT()
{
    studentBT *sBT = (studentBT*) malloc( sizeof ( studentBT) );

    sBT->head = NULL;

    return sBT;
}

student *readStudentFile(FILE *file)
{
    char s[256];
    
    student *st = (student*) malloc ( sizeof( student));
    fgets(s, 256, file);
    char *token = strtok(s, "\n");
    strcpy(st->name, token);
    fgets(s, 256, file);
    token = strtok(s, "\n");
    strcpy(st->degree, token);
    courseBT *cBT = createCourseBT();
    while(fgets(s, 256, file) != NULL)
    {
        token = strtok(s, "\n");
        course *c = (course*) malloc ( sizeof (course));
        strcpy(c->name, token);
        addElementCourseBT(cBT, c);
    }
    st->courses = cBT;

    return st;
}

student *getStudent(studentBT *sBT, char *name)
{
    studentBTNode *cur = sBT->head;

    while(cur != NULL)
    {
        if (strcmp(cur->st->name, name) == 0)
        {
            return cur->st;
        }

        if (strcmp(cur->st->name, name) > 0)
        {
            cur = cur->left;
        } else
        {
            cur = cur->right;
        }
        
    }
    return NULL;
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