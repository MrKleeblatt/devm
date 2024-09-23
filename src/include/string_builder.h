#pragma once

#include <stdlib.h>


typedef struct string_builder_node_s {
	size_t section_len;
	char* section;
	struct string_builder_node_s* next;
} string_builder_node;

typedef struct {
	size_t result_len;
	string_builder_node* head;
	string_builder_node* tail;
} string_builder;


void string_builder_append(string_builder* builder, char* section);
char* string_builder_build(string_builder builder);
void string_builder_free(string_builder* builder);
char* str_concat(char* str1, char* str2);
char* arr_to_string(char** arr, char* delimiter);

