//Implement functions defined in memory_leak_detector.h file
#include <stdio.> 
#include <stdlib.h>
#include "memory_leak_detector.h"
#include "css.h"
#include <assert.h>
#include <memory.h>

char* DATA_TYPE = { "UINT8","UINT32","INT32","CHAR","OBJ_PTR","VOID_PTR","FLOAT","DOUBLE","OBJ_STRUCT" };

//Dumping function
void print_structure_rec(struct_db_rec_t* struct_rec) {
	if (!structure_rec) return;
	int j = 0;
	field_info_t* field = NULL;
	printf(ANSI_COLOR_CYAN "|---------------------------------------|\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW "| %-20s | size=%-8d | #flds = %-3d| \n", struct_rec->struct_name, struct_rec->ds_size, struct_rec->n_fields);
	printf(ANSI_COLOR_CYAN "|---------------------------------------|\n" ANSI_COLOR_RESET);
	for (j = 0; j < struct_rec->n_fields; j++) {
		field = &struct_rec->fields[j];
		printf(" %-20s |", "");
		printf("%-3d %-20s | dtype = %-15s | size=%-5d| offset=%-6d | nstrucname = %-20s |\n", j, field->fname, DATA_TYPE[field->dtype], field->size, field->offset, field->nested_str_name);
		printf(" %20-s | ", "");
		printf(ANSI_COLOR_CYAN "|---------------------------------------|\n" ANSI_COLOR_RESET);
	}
}
void print_structure_db(struct_db_t* struct_db) {
	if (!struct_db) return;
	printf("Printing structure database.\n");
	int i = 0;
	struct_db_rec_t* struct_rec = NULL;
	struct_rec = struct_db->head;
	printf("Number of structures registered = %d.\n", struct_db->count);
	while (struct_rec) {
		printf("Structure num : %d (%p).\n", i++, struct_rec);
		print_structure_rec(struct_rec);
		struct_rec = struct_rec->next;
	}
}
int add_structure_to_struct_db(struct_db_t* struct_db, struct_db_rec_t* struct_rec) {
	struct_db_rec_t* head = struct_db->head;

	if (!head) {
		struct_db->head = struct_rec;
		struct_rec->next = NULL;
		struct_db->count++;
		return 0;
	}

	struct_rec->next = head;
	struct_db->head = struct_reg;
	struct_db->count++;
	return 0;
}
static struct_db_rec_t* struct_db_look_up(struct_db_t* struct_db, char* struct_name) {
	struct_db_rec_t* head = struct_db->head;
	if (!head) return NULL;

	for (; head; head = head->next) {
		if (strncmp(head->struct_name, struct_name, MAX_STRUCTURE_NAME_SIZE) == 0)
			return head;
	}
	return NULL;
}

static void add_object_to_object_db(object_db_t* object_db, void* ptr, int units, struct_db_rec_t* struct_rec, mld_boolean_t is_root) {
	object_db_rec_t* obj_rec = object_db_look_up(object_db ptr);
	//Check if object is alredy added
	assert(!obj_rec);
	object_rec = calloc(1, sizeof(object_db_rec_t));

	obj_rec->next = NULL;
	obj_rec->ptr = ptr;
	obj_rec->units = units;
	object_rec->struct_rec = struct_rec;
	object_rec->is_visited = MLD_FALSE;
	object_rec->is_root = is_root;

	object_db_rec_t* head = object_db->head;

	if (!head) {
		object_db->head = obj_rec;
		obj_rec->next = NULL;
		object_db->count++;
		return;
	}

	object_rec->next = head;
	object_db->head = obj_rec;
	object_db->count++;
}
//xcalloc funtion set object by default to non-root
void xcalloc(object_db_t* object_db, char* struct_name, int units) {
	struct_db_rec_t* struct_rec = struct_db_look_up(object_db->struct_db, struct_name);
	assert(struct_rec);
	void* ptr = calloc(units, struct_record->ds_size);
	add_object_to_object_db(object_db, units, struct_rec, MLD_FALSE);
	return ptr;
}

static void delete_object_record_from_object_db(object_db_t* obj_db, object_db_rec_t* object_rec) {
	assert(object_rec);
	object_db_rec_t* head = object_db->head;
	if (head == object_rec) {
		object_db->head = object_rec->next;
		free(object_rec);
		return;
	}

	object_db_rec_t* prev = head;
	head = head->next;

	while (head) {
		if (head != object_rec) {
			prev = head;
			head = head->next;
			continue;
		}
		prev->next = head->next;
		head->next = NULL;
		free(head);
		return;
	}
}
void xfree(object_db_t* object_db, void* ptr) {
	if (!ptr) return;
	object_db_rec_t* object_rec = object_db_look_up(object_db, ptr);
	assert(object_rec);
	assert(object_rec->ptr);
	free(object_rec->ptr);
	object_rec->ptr = NULL;
	//Delete object record from object db
	delete_object_record_from_object_db(object_db, object_rec);
}
//Dumping functions for Object database
void print_obj_rec(object_db_rec_t* obj_rec, int i) {
	if (!obj_rec) return;
	printf(ANSI_COLOR_CYAN "----------------------------------------|\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELOW "%-3d ptr = %-10p | next= %-10p | units=%-4d | struct_name = %-10s | is_root = %s | \n" ANSI_COLOR_RESET, i, obj_rec->next, obj_rec->units, obj_rec->struct_rec->struct_name, obj_rec->is_root ? "TRUE" : "FALSE");
	printf(ANSI_COLOR_CYAN "----------------------------------------|\n", ANSI_COLOR_RESET);
}
void print_object_db(object_db_t* object_db) {
	object_db_rec_t* head = object_db->head;
	unsigned int i = 0;
	printf(ANSI_COLOR_CYAN "Printing object database.\n");
	for (; head; head = head->next) {
		print_object_rec(head,i++)
	}
}
//The global object of the app which is not created by xcalloc should be registered with MLD using below API
void mld_register_global_object_as_root(object_db_t* object_db, void* objptr, char* struct_name, unsigned int units) {
	struct_db_rec_t* struct_rec = struct_db_look_up(object_db->struct_db, struct_name);
	assert(struct_rec);
	//Create new object record and add to object database
	add_object_to_object_db(object_db, objptr, units, struct_rec, MLD_TRUE);
}
//App might create and object using xcalloc,but at the same time object can be root object.Use this API to override the object flags for the object present in object db
void mld_set_dynamic_object_as_root(object_db_t* object_db, void* obj_ptr) {
	object_db_rec_t obj_rec = object_db_look_up(object_db, obj_ptr);
	assert(obj_rec);
	obj_rec->is_root = MLD_TRUE;
}
static object_db_rec_t* get_next_root_object(object_db_t* object_db, object_db_rec_t* starting_from_here) {
	object_db_rec_t* first = starting_from_here ? starting_from_here->next : obj_db->head;
	while (first) {
		if (first->is_root)
			return first;
		first = first->next;
	}
	return NULL;
}
static void init_mld_algorithm(object_db_t* object_db) {
	object_db_rec_t* obj_rec = object_db->head;
	while (obj_rec) {
		obj_rec->is_visited = MLD_FALSE;
		obj_rec = obj_rec->next;
	}
}




