#ifndef MEMORY_LEAK_DETECTOR_OBJECTS_H_INCLUDED
#define MEMORY_LEAK_DETECTOR_OBJECTS_H_INCLUDED


/*Object Database structure definitions Starts here*/

typedef struct _object_db_rec_ object_db_rec_t;

struct _object_db_rec_{
    object_db_rec_t *next;
    void *ptr;
    unsigned int units;
    struct_db_rec_t *struct_rec;
    mld_boolean_t is_visited; /*Used for Graph traversal*/
    mld_boolean_t is_root;    /*Is this object is Root object*/
};

typedef struct _object_db_{
    struct_db_t *struct_db;
    object_db_rec_t *head;
    unsigned int count;
} object_db_t;


/*Dumping functions*/
void
print_object_rec(object_db_rec_t *obj_rec, int i);

void
print_object_db(object_db_t *object_db);

/*API to malloc the object*/
void *xcalloc(object_db_t *object_db, char *struct_name, int units);


#endif // MEMORY_LEAK_DETECTOR_OBJECTS_H_INCLUDED
