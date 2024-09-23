#include "string_builder.h"
#include "api/array.h"
#include <string.h>

void string_builder_append(string_builder* builder, char* section){
	if(section == nullptr) return;
	string_builder_node* node = calloc(1, sizeof *node);
	node->section = section;
	node->section_len = strlen(section);
	if(builder->tail) builder->tail->next = node;
	else builder->head = node;
	builder->tail = node;
	builder->result_len += node->section_len;
}

char* string_builder_build(string_builder builder){
	char* result = calloc((builder.result_len + 1), sizeof *result);
	auto node = builder.head;
	while(node != nullptr) {
		strcat(result, node->section);
		node = node->next;
	}
	return result;
}

void string_builder_free(string_builder* builder){
	auto node = builder->head;
	while(node != nullptr) {
		auto next = node->next;
		free(node);
		node = next;
	}
}

char* str_concat(char* str1, char* str2){
	size_t result_len = strlen(str1) + strlen(str2);
	char* result = calloc(result_len+1, sizeof *result);
	strcpy(result, str1);
	strcat(result, str2);
	result[result_len] = '\0';
	return result;
}

char* arr_to_string(char** arr, char* delimiter){
	if(arr == nullptr) return nullptr;
	size_t result_len = 0;
	arr_foreach(arr, i) result_len += strlen(arr[i]);
	if(result_len == 0) return nullptr;
	result_len += strlen(delimiter) * (arr_count(arr)-1);
	char* result = calloc(result_len + 1, sizeof *result);
	arr_foreach(arr, i){
		strcat(result, arr[i]);
		if(i == arr_count(arr)-1) break;
		strcat(result, delimiter);
	}
	result[result_len] = '\0';
	return result;
}

