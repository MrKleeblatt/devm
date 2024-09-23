#include "api/devm_api.h"
#include "string_builder.h"
#include "api/array.h"
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>


static bool devm_extension_filter(char* filename, void* context){
	char* file_extension;
	file_extension = strtok (filename,".");
	while (file_extension != NULL) file_extension = strtok (NULL, ".");
	return !strcmp(file_extension, (char*) context);
}

source* devm_source_dir(char* directory, char* file_extension){
	return devm_source_dir_filter(directory, devm_extension_filter, (void*) file_extension);
}

source* devm_source_dir_filter(char* directory, bool(*filter)(char* filename, void* context), void* context){
	source* result = nullptr;
	arr_init(result);
	// open directory
	DIR* dir = opendir(directory);
	if(dir == nullptr) {
		// error handling
	}
	while(dir) {
		auto entry = readdir(dir);
		if(entry == nullptr) {
			// error handling
		}
		if(entry->d_type != DT_REG) continue;
		if(!filter(entry->d_name, context)) continue;
		char* relative_name = str_concat(directory, entry->d_name);
		source src = devm_source(relative_name);
		src._must_free = true;
		arr_add(result, src);
	}
	return result;
}

source devm_source(char* file){
	source result = {0};
	result.file = file;
	arr_init(result.extra_flags);
	return result;
}


const char* devm_filename_extension(const char *filename) {
	const char *dot = strrchr(filename, '.');
	if(!dot || dot == filename) return nullptr;
	return dot + 1;
}
