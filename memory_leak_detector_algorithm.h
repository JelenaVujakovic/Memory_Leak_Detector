#ifndef MEMORY_LEAK_DETECTOR_ALGORITHM_H_INCLUDED
#define MEMORY_LEAK_DETECTOR_ALGORITHM_H_INCLUDED


/*APIs to register root objects*/
void mld_register_root_object (object_db_t *object_db,
                               void *objptr,
                               char *struct_name,
                               unsigned int units);

void set_mld_object_as_global_root(object_db_t *object_db, void *obj_ptr);


/*APIs for MLD Algorithm*/
void run_mld_algorithm(object_db_t *object_db);

void report_leaked_objects(object_db_t *object_db);

void mld_set_dynamic_object_as_root(object_db_t *object_db, void *obj_ptr);

void mld_init_primitive_data_types_support(struct_db_t *struct_db);


#endif // MEMORY_LEAK_DETECTOR_ALGORITHM_H_INCLUDED
