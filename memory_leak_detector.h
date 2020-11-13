#ifndef __MLD__
#include <assert.h>
#include <string.h>

//Structure Database definition
#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

//Enumeration for data types
typedef enum{
    UINT8,
    UINT32,
    INT32,
    CHAR,
    OBJ_PTR,
    VOID_PTR,//New data type to identify void * pointers
    FLOAT,
    DOUBLE,
    OBJ_STRUCT
}data_type_t;
typedef enum{
    MLD_FALSE,
    MLD_TRUE
}mld_boolean_t;
#define OFFSET(struct_name,fld_name) \
    (unsigned long)&(((struct_name*)0)->fld_name)
#define FIELD_SIZE(struct_name,fld_name) \
    sizeof(((struct_name*)0)->fld_name)

typedef struct _struct_db_rec struct_db_rec_t;

//Structure to store the information of one field of C structure
typedef struct _field_info_{
    char fname[MAX_FIELD_NAME_SIZE]; //Name of the field
    data_type_t dtype;
    unsigned int size;
    unsigned int offset;
    char nested_str_name[MAX_STRUCTURE_NAME_SIZE]; //if dt is OBJ_PTR or OBJ_STRUCT
}field_info_t;

//Structure to store the info of one C structure which could have n_fields fields
struct _struct_db_rec_{
    struct_db_rec_t *next; //Pointer to the next structure in the linked list
    char struct_name[MAX_STRUCTURE_NAME_SIZE];//key
    unsigned int ds_size; //Size of structure
    unsigned int n_fields; //num of fields in the structure
    field_info_t *fields; //pointer to the array of fields
};

//The head of the linked list representing the structure
typedef struct _struct_db_{
    struct_db_rec_t *head;
    unsigned int count;
}struct_db_t;
//Structure Data base definition ends

//Printing functions
void print_structure_record(struct_db_rec_t *struct_rec);
void print_structure_db(struct_db_t *struct_db);

//Add structure record to structure database
int add_structure_to_struct_sb(struct_db_t *struct_db,struct_db_rec_t *struct_rec);

//Structure registration API
#define FIELD_INFO(struct_name,fld_name,dtype,nested_struct_name) \
    {#fld_name,dtype,FIELD_SIZE(struct_name,fld_name), \
    OFFSETOF(struct_name,fld_name),#nested_struct_name}
#define REG_STRUCT(struct_db,st_name,field_arr) \
    do{ \
        struct_db_rec_t *rec=calloc(1,sizeof(struct_db_rec_t)); \
        strncpy(rec->struct_name,#st_name,MAX_STRUCTURE_NAME_SIZE); \
        rec->ds_size=sizeof(st_name); \
        rec->n_fields=sizeof(fields_arr)/sizeof(field_info_t); \
        rec->fields=fields_arr;
        if(add_structure_to_struct_db(struct_db,rec)){ \
            assert(0); \
        } \
    }while(0); \
//Structure database definition ends
//Object database structure definition
typedef struct _object_db_rec_ object_db_rec_t;

struct _object_db_rec_{
    object_db_rec_t *next;
    void *ptr;
    unsigned int units;
    struct_db_rec_t *struct_rec;
    mld_boolean_t is_visited; //used for graph traversal
    mld_boolean_t is_root;
};
typedef struct _object_db_{
    struct_db_t *struct_db;
    object_db_rec_t *head;
    unsigned int count;
}object_db_t;

//Dumping functions
void print_object_rec(object_db_rec_t *obj_rec,int i);
void print_object_db(object_db_t *obj_db);
//API to malloc the object
void* xcalloc(object_db_t *object_db,char *struct_name,int units);
//API to register root objects
void mld_register_root_objects(object_db_t *object_db,void *objptr,char *struct_name,unsigned int units);
void set_mld_object_as_global_root(object_db_t *object_db,void *object_ptr);
//API for MLD algorithm
void run_mld_algorithm(object_db_t *object_db);
void report_leaked_objects(object_db_t *object_db);
void mld_set_dynamic_object_as_root(object_db_t *object_db,void *obj_ptr);
void init_primitive_data_types_support(struct_db_t *struct_db);




#endif // __MLD__
