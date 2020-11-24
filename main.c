#include <string.h>

#include    "requirements.h"
#include    "degrees.h"
#include    "course.h"
#include    "department.h"
#include    "commands.h"
#include    "student.h"
int main(int argc, char *argv[])
{

    FILE *file1 = fopen("student1.txt", "r");
    FILE *file2 = fopen("student2.txt", "r");
    FILE *file3 = fopen("degree1.txt", "r");
    FILE *file4 = fopen("department1.txt", "r");
    char s[256];
    fgets(s, 256, file1);
    fgets(s, 256, file2);
    fgets(s, 256, file3);
    fgets(s, 256, file4);
    //student
    studentBT *sBT = createStudentBT();
    student *st1 = readStudentFile(file1);
    student *st2 = readStudentFile(file2);
    addStudentToBT(sBT, st1);
    addStudentToBT(sBT, st2);

    printStudentBT(sBT);
    

    //degree
    degreeArrayList *degreeList  = createDegreeArrayList();
    degree *degree1              = readDegreeFile(file3);
    addDegreeArrayList(degreeList, degree1);
    // printDegree(degree1);
    //degree *d = getDegree(degreeList, "AB Computer Science");

    commandM(sBT, degreeList, "Cesar Gonzales");

    //department
    departmentList *departmentList  = createDepartmentList();
    department *department1         = readDepartmentFile(file4);
    addToDepartmentList(departmentList, department1);
    course *course = getCourse(department1->cBT, "MATH 263");

    printf("\n\n");
    commandN(sBT, degreeList, departmentList, "Cesar Gonzales");
    deleteStudentBT(sBT);
    deleteDegreeArrayList(degreeList);
    deleteDepartmentList(departmentList);

    fclose(file1);
    fclose(file2);
    fclose(file3);
    // if (argc != 5) {printf("Please provide valid files!\n"); return 0;}
    // FILE *file1 = fopen(argv[1], "r");
    // FILE *file2 = fopen(argv[2], "r");
    // FILE *file3 = fopen(argv[3], "r");
    // FILE *file4 = fopen(argv[4], "r");
    // char s[256];
    // if (file1 == NULL || file2 == NULL)
    // {
    //     printf("Please provide valid files!\n"); return 0;
    // }
    // fgets(s, 256, file1);
    // fgets(s, 256, file2);
    // fgets(s, 256, file3);
    // fgets(s, 256, file4);
    // //reading department files.
    // departmentList *departmentList  = createDepartmentList();
    // department *department1         = readDepartmentFile(file1);
    // addToDepartmentList(departmentList, department1);
    // department *department2         = readDepartmentFile(file2);
    // addToDepartmentList(departmentList, department2);
    // //reading degree files
    // degreeArrayList *degreeList  = createDegreeArrayList();
    // degree *degree1              = readDegreeFile(file3);
    // addDegreeArrayList(degreeList, degree1);
    // degree *degree2              = readDegreeFile(file4);
    // addDegreeArrayList(degreeList, degree2);
    // //main engine running the whole programn
    // while(1)
    // {
    //     char c[256];
    //     char c2[256];
    //     char c3[256];
    //     scanf("%1s", &c);
    //     // printf("c: %s\n", c);
    //     if ( strcmp("x", c) == 0) { printf("Quiting\n"); break;}
    //     scanf(" ");
    //     if ( strcmp("c", c) == 0) 
    //     { 
    //         fgets(c3, 256, stdin); 
    //         char *token = strtok(c3, "\n");     
    //         if (token == NULL) continue;
    //         commandC(departmentList, token); 
    //         continue;
    //     }
    //     if ( strcmp("d", c) == 0) 
    //     { 
    //         fgets(c3, 256, stdin); 
    //         char *token = strtok(c3, "\n");  
    //         if (token == NULL) continue;
    //         commandD(degreeList, token); 
    //         continue; 
    //     }
    //     if ( strcmp("s", c) == 0) 
    //     { 
    //         fgets(c3, 256, stdin); 
    //         char *token = strtok(c3, "\n");  
    //         if (token == NULL) continue;
    //         commandS(departmentList, degreeList, token); 
    //         continue; 
    //     }
    //     //TODO

    //     if ( strcmp("p", c) == 0) 
    //     {
    //         scanf("%1s", c2);
            
    //         if ( strcmp("c", c2) == 0) 
    //         { 
    //             scanf(" ");
    //             fgets(c3, 256, stdin); 
    //             printf("%s\n", c3);
    //             char *token = strtok(c3, "\n");  
    //             commandPcourse(departmentList, degreeList, c3); 
    //             continue;
    //         }
    //         if ( strcmp("d", c2) == 0) 
    //         { 
    //             scanf(" ");
    //             fgets(c3, 256, stdin); 
    //             char *token = strtok(c3, "\n");  
    //             commandPdepartment(departmentList, c3); 
    //             continue;
    //         }
    //         if ( strcmp("g", c2) == 0) 
    //         { 
    //             scanf(" ");
    //             fgets(c3, 256, stdin); 
    //             char *token = strtok(c3, "\n");  
    //             commandPdegree(degreeList, c3); 
    //             continue;
    //         }
    //     }
    //     printf("iInvalid Input\n");
    // }


    // //free all the pointers
    // deleteDegreeArrayList(degreeList);
    // deleteDepartmentList(departmentList);

    // fclose(file4);
    // fclose(file3);
    // fclose(file2);
    // fclose(file1);
}