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

