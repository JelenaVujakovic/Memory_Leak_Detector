#include "memory_leak_detector.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

//Application structures
typedef struct emp_ {
    char emp_name[30];
    unsigned int emp_id;
    unsigned int age;
    struct emp* mgr;
    float salary;
    int* p;
}emp_t;

typedef struct student_ {
    char stud_name[32];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    struct student_* best_colleage;
}student_t;


int main(int argc, char **argv)
{
   

    return 0;
}


