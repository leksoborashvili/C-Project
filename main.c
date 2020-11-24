#include <string.h>

#include    "requirements.h"
#include    "degrees.h"
#include    "course.h"
#include    "department.h"
#include    "commands.h"
#include    "student.h"
int main(int argc, char *argv[])
{


    char s[256];
    
    studentBT *sBT = createStudentBT();
    departmentList *departmentList  = createDepartmentList();
    degreeArrayList *degreeList  = createDegreeArrayList();

    ///READING ENGINE
    
    for(int i = 1; i < argc; i ++)
    {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {printf("INVALID FILE NAME\n"); return 0;}

        fgets(s, 256, file);

        //STUDENT\n
        if ( strcmp(s, "STUDENT\n") == 0 )
        {
            student *st = readStudentFile(file);
            addStudentToBT(sBT, st);
            fclose(file);
            continue;
        }

        //DEPARTMENT\n
        if ( strcmp(s, "DEPARTMENT\n") == 0 )
        {
            department *dep = readDepartmentFile(file);
            addToDepartmentList(departmentList, dep);
            fclose(file);
            continue;
        }

        //DEGREE\n
        if ( strcmp(s, "DEGREE\n") == 0) 
        {
            degree *deg = readDegreeFile(file);
            addDegreeArrayList(degreeList, deg);
            fclose(file);
            continue;
        }
    }
    printDegreeArrayList(degreeList);
    printDepartmentList(departmentList);
    printStudentBT(sBT);
    //main engine running the whole programn
    
    while(1)
    {
        char c[256];
        char c2[256];
        char c3[256];
        fgets(s, 256, stdin);
        // printf("c: %s\n", c);
        char *token = strtok(s, " ");
        //printf("%s\n", token);
        strcpy(c, token);
        //x
        if (c[strlen(c)-1] == '\n') c[strlen(c)-1] = 0;
        if ( strcmp("x", c) == 0) { printf("Quiting\n"); break;}
        //c
        if ( strcmp("c", c) == 0) 
        {  
            token = strtok(NULL, " ");
            if (token == NULL) {continue;}
            strcpy(c2, token);
            strcat(c2, " ");
            token = strtok(NULL, " ");
            if (token == NULL) {continue;}
            strcat(c2, token);
            if (token == NULL) continue;
            if (c2[strlen(c2)-1] == '\n') c2[strlen(c2)-1] = 0;
            
            commandC(departmentList, c2); 
            continue;
        }
        //d
        if ( strcmp("d", c) == 0) 
        { 
            token = strtok(NULL, " ");
            if (token == NULL) {continue;}
            strcpy(c2, token);
            while(token != NULL)
            {
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcat(c2, " ");
                strcat(c2, token);
            }
            if (c2[strlen(c2) - 1] == '\n') c2[strlen(c2) - 1] = 0;

            commandD(degreeList, c2); 
            continue; 
        }
        //s
        if ( strcmp("s", c) == 0) 
        { 
            token = strtok(NULL, " ");
            if (token == NULL) {continue;}
            strcpy(c2, token);
            while(token != NULL)
            {
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcat(c2, " ");
                strcat(c2, token);
            }
            if (c2[strlen(c2) - 1] == '\n') c2[strlen(c2) - 1] = 0;

            commandS(departmentList, degreeList, c2); 
            continue; 
        }
        
        //p
        if ( strcmp("p", c) == 0) 
        {
            token = strtok(NULL, " ");
            if (token == NULL) continue;
            strcpy(c3, token);
            if (c3[strlen(c3)-1] == '\n') c3[strlen(c3)-1] = 0;
            //course
            if ( strcmp("c", c3) == 0) 
            { 
                token = strtok(NULL, " ");
                if (token == NULL) {continue;}
                strcpy(c2, token);
                while(token != NULL)
                {
                    token = strtok(NULL, " ");
                    if (token == NULL) break;
                    strcat(c2, " ");
                    strcat(c2, token);
                }
                if (c2[strlen(c2) - 1] == '\n') c2[strlen(c2) - 1] = 0;

                commandPcourse(departmentList, degreeList, c2); 
                continue;
            }
            //department
            if ( strcmp("d", c3) == 0) 
            { 
                token = strtok(NULL, " ");
                if (token == NULL) {continue;}
                strcpy(c2, token);
                while(token != NULL)
                {
                    token = strtok(NULL, " ");
                    if (token == NULL) break;
                    strcat(c2, " ");
                    strcat(c2, token);
                }
                if (c2[strlen(c2) - 1] == '\n') c2[strlen(c2) - 1] = 0;

                commandPdepartment(departmentList, c2); 
                continue;
            }
            //degree
            if ( strcmp("g", c3) == 0) 
            { 
                token = strtok(NULL, " ");
                if (token == NULL) {continue;}
                strcpy(c2, token);
                while(token != NULL)
                {
                    token = strtok(NULL, " ");
                    if (token == NULL) break;
                    strcat(c2, " ");
                    strcat(c2, token);
                }
                if (c2[strlen(c2) - 1] == '\n') c2[strlen(c2) - 1] = 0; 

                commandPdegree(degreeList, c2); 
                continue;
            }
            //student
            if (strcmp("s", c3) == 0)
            {
                token = strtok(NULL, " ");
                if (token == NULL) {continue;}
                strcpy(c2, token);
                while(token != NULL)
                {
                    token = strtok(NULL, " ");
                    if (token == NULL) break;
                    strcat(c2, " ");
                    strcat(c2, token);
                }
                if (c2[strlen(c2) - 1] == '\n') c2[strlen(c2) - 1] = 0; 

                commandPstudent(sBT, c2); 
                continue;
            }
        }

        //m
        if (strcmp("m", c) == 0)
        {
            token = strtok(NULL, " ");
            if (token == NULL) {continue;}
            strcpy(c2, token);
            while(token != NULL)
            {
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcat(c2, " ");
                strcat(c2, token);
            }
            if (c2[strlen(c2) - 1] == '\n') c2[strlen(c2) - 1] = 0;

            commandM(sBT, degreeList, c2);
            continue;
        }

        //n 
        if (strcmp("n", c) == 0)
        {
            token = strtok(NULL, " ");
            if (token == NULL) {continue;}
            strcpy(c2, token);
            while(token != NULL)
            {
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcat(c2, " ");
                strcat(c2, token);
            }
            if (c2[strlen(c2) - 1] == '\n') c2[strlen(c2) - 1] = 0;
            commandN(sBT, degreeList, departmentList, c2);
            continue;
        }

        //r
        if (strcmp("r", c) == 0)
        {
            char dName[256], cName[256];
            token = strtok(NULL, " ");
            if (token == NULL) continue;
            strcpy(dName, token);


            while(token != NULL)
            {
                if (dName[strlen(dName)-1] == ',')
                {
                    dName[strlen(dName)-1] = 0;
                    break;
                }
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcat(dName, " ");
                strcat(dName, token);
                

            }
            token = strtok(NULL, " ");
            if (token == NULL) continue;
            strcpy(cName, token);
            while(token != NULL)
            {
                if (cName[strlen(cName)-1] == '\n')
                {
                    cName[strlen(cName)-1] = 0;
                    break;
                }
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcat(cName, " ");
                strcat(cName, token);
                

            }

            commandR(degreeList, departmentList, dName, cName);
            continue;
        }

        //q
        if (strcmp("q", c) == 0)
        {
            char dName[256], cName[256];
            token = strtok(NULL, " ");
            if (token == NULL) continue;
            strcpy(dName, token);

            while(token != NULL)
            {
                if (dName[strlen(dName)-1] == ',')
                {
                    dName[strlen(dName)-1] = 0;
                    break;
                }
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcat(dName, " ");
                strcat(dName, token);
                

            }

            token = strtok(NULL, " ");
            if (token == NULL) continue;
            strcpy(cName, token);
            while(token != NULL)
            {
                if (cName[strlen(cName)-1] == '\n')
                {
                    cName[strlen(cName)-1] = 0;
                    break;
                }
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcat(cName, " ");
                strcat(cName, token);
                

            }
            
            commandQ(degreeList, dName, cName); 
            continue;
        }
        //a
        if (strcmp("a", c) == 0)
        {
            course *c           = (course*) malloc( sizeof( course));
            linkedListReq *reqs = createLinkedListReq();

            char dName[256], cName[256], cTitle[256];
            //parse through department name
            token = strtok(NULL, " ");
            if (token == NULL) continue;
            strcpy(dName, token);

            while(token != NULL)
            {
                if (dName[strlen(dName)-1] == ',')
                {
                    dName[strlen(dName)-1] = 0;
                    break;
                }
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcat(dName, " ");
                strcat(dName, token);
                

            }

            //parse through course name
            token = strtok(NULL, " ");
            if (token == NULL) continue;
            strcpy(cName, token);
            while(token != NULL)
            {
                if (cName[strlen(cName)-1] == ',')
                {
                    cName[strlen(cName)-1] = 0;
                    break;
                }
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcat(cName, " ");
                strcat(cName, token);
                

            }
            
            //parse through course Title
            token = strtok(NULL, " ");
            if (token == NULL) continue;
            strcpy(cTitle, token);
            while(token != NULL)
            {
                if (cTitle[strlen(cTitle)-1] == ',')
                {
                    cTitle[strlen(cTitle)-1] = 0;
                    break;
                }
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcat(cTitle, " ");
                strcat(cTitle, token);
                

            }

            strcpy(c->name, cName);
            strcpy(c->title, cTitle);
            //loop to parse requirements.
            
            while(token != NULL)
            {
                char c4[256];
                token = strtok(NULL, " ");
                if (token == NULL) break;
                strcpy(c4, token);
                while(token != NULL)
                {
                    token = strtok(NULL, " ");
                    if (token == NULL) continue;
                    strcat(c4, " ");
                    strcat(c4, token);
                    if (c4[strlen(c4)-1] == ',' || c4[strlen(c4)-1] == '\n') 
                    {
                        c4[strlen(c4)-1] = 0;
                        addLastNodeReq(reqs, c4);
                        break;
                    }
                }
            }
            c->reqList = reqs;
            commandA(departmentList, dName, c);
            continue;
        }
        printf("iInvalid Input\n");
    }
    
    //free all the pointers
    deleteDegreeArrayList(degreeList);
    deleteDepartmentList(departmentList);
    deleteStudentBT(sBT);
}