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
    static field_info_t emp_fields[] = {
        FIELD_INFO(emp_t,emp_name,CHAR,0);
        FIELD_INFO(emp_t, emp_id, UINT32, 0);
        FIELD_INFO(emp_t, age, UINT32, 0);
        FIELD_INFO(emp_t, mgr_name, OBJ_PTR, emp_t);
        FIELD_INFO(emp_t, salary, FLOAT, 0);
        FIELD_INFO(emp_t, p, OBJ_PTR, 0);
    }
    //3.Register the structure in structure database
    REG_STRUCT(struct_db, emp_t, emp_fields);

    static field_info_t stud_fields[] = {
        FIELD_INFO(student_t,stud_name,CHAR,0);
        FIELD_INFO(student_t, rollno, UINT32, 0);
        FIELD_INFO(student_t, age, UINT32, 0);
        FIELD_INFO(student_t, aggregate, FLOAT, 0);
        FIELD_INFO(emp_t,best_colleage, OBJ_PTR, student_t);
    }
       
    REG_STRUCT(struct_db, student_t, stud_fields);
    //4.Verify the correctness of structure database
    print_structure_db(struct_db);
    //5.Demonstrate wirking with object database

    return 0;
}


