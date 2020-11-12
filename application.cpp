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
    //1.Initialize a new structure database
    struct_db_t* struct_db = calloc(1, sizeof(struct_db_t));
    mld_init_primitive_data_support(struct_db);
    //2.Create structure record for structure emp_t
    //3.Register the structure in structure database
    //4.Verify the correctness of structure database
    //5.Demonstrate wirking with object database

    return 0;
}


