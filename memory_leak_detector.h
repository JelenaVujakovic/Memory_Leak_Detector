#ifndef __MLD__
#include <assert.h>
#include <string.h>

//Structure Data Base definition
#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

//Enumeration for data types
typedef enum {
	UINT8,
	UINT32,
	INT32,
	CHAR,
	OBJ_PTR,
	VOID_PTR,
	FLOAT,
	DOUBLE,
	OBJ_STRUCT
}data_type_t;

typedef enum {
	MLD_FALSE,
	MLD_TRUE
}mld_boolean_t;

#define OFFSETOF(struct_name,fld_name) \
	(unsigned long)&((struct_name*)0)->fld_name)
#define FIELD_SIZE(struct_name,fld_name) \
	sizeof(((struct_name*)0)->fld_name)
typedef struct _struct_db_rec_ struct_db_rec_t;

//Structure to store the information of one field of C structure
typedef struct _field_info_ {
	char fname[MAX_FIELD_NAME_SIZE];
	data_type_t dtype;
	unsigned int size;
	unsigned int offset;
	char nested_str_name[MAX_STRUCTURE_NAME_SIZE];
}field_info_t;

//Structure to store information of one C structure which could have n_fields field
struct _struct_db_rec_ {
	struct_db_rec_t* next;
	char struct_name[MAX_STRUCTURE_NAME_SIZE];//key
	unsigned int ds_size;
	unsigned int n_fields;
	field_info_t* fields;
};

//Head of the linked list representing the structure database
typedef struct _struct_db_ {
	struct_db_rec_t* head;
	unsigned int count;
}struct_db_t;

//Structure Data Base definition end
//Printing functions
void structure_rec(struct_db_rec_t* struct_rec);
void print_structure_db(struct_db_t* struct_db);

//Function to add structure recorf in a structure database
int add_structure_to_struct_db(struct_db_t* struct_db, struct_db_rec_t* struct_rec);

//Structure Registration helping APIs
#define FIELD_INFO(struct_name,fld_name,dtype,nested_struct_name)    \
	{#fld_name,dtype,FIELD_SIZE(struct_name,fld_name),				 \
	OFFSETOF(struct_name,fld_name),#nested_struct_name}

#define REG_STRUCT(struct_db,st_name,fields_arra) \
	do{	/*								  \
		struct_db_rec_t* rec = calloc(1, sizeof(struct_db_rec_t));    
		strncpy(rec->struct_name, #st_name, MAX_STRUCTURE_NAME_SIZE); \ 
		rec->ds_size = sizeof(st_name);                               \
		rec->n_fields = sizeof(fields_arr) / sizeof(field_info_t);    \
		rec->fields = fields_arr;                                     \
		if (add_structure_to_struct_db(struct_db, rec)) {             \
			assert(0);                                                \
		} */                                                          \
	}while(0);                                                        \
//---------------------------------------------------------------------------------------------



















#endif //__MLD__