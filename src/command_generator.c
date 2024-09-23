#include "command_generator.h"
#include "cleanup.h"
#include "string_builder.h"
#include "api/array.h"
#include <curl/curl.h>
#include <string.h>
#include <json-c/json.h>

char* get_source_path(config conf, source src){
	size_t src_file_len = strlen(src.file);
	size_t len = src_file_len + 1;
	char* path;
	// TODO: error handling
	if(conf.expand_cwd) len += strlen(conf.cwd);
	path = calloc(len, sizeof *path);
	if(conf.expand_cwd) strcat(path, conf.cwd);
	strcat(path, src.file);
	return path;
}

char* escape_path(char* path){
	path = str_concat(path, ".o");
	CURL* curl = curl_easy_init();
	char* escaped = curl_easy_escape(curl, path, strlen(path));
	free(path);
	curl_easy_cleanup(curl);
	return escaped;
}

void generate_command(config conf, source* src){
	String general_flags = arr_to_string(conf.general_flags, " ");
	String compile_flags = arr_to_string(conf.compile_flags, " ");
	String extra_flags = arr_to_string(src->extra_flags, " ");
	String source_file_path = get_source_path(conf, *src);
	String object_escaped_name = escape_path(source_file_path);

	StringBuilder builder = {0};
	string_builder_append(&builder, conf.compiler);
	string_builder_append(&builder, " ");
	if(general_flags != nullptr) {
		string_builder_append(&builder, general_flags);
		string_builder_append(&builder, " ");
	}
	if(compile_flags != nullptr) {
		string_builder_append(&builder, compile_flags);
		string_builder_append(&builder, " ");
	}
	if(extra_flags != nullptr) {
		string_builder_append(&builder, extra_flags);
		string_builder_append(&builder, " ");
	}
	string_builder_append(&builder, "-c -o ./build/out/");
	string_builder_append(&builder, object_escaped_name);
	string_builder_append(&builder, " ");
	string_builder_append(&builder, source_file_path);

	src->_command = string_builder_build(builder);
}

char* generate_json(config conf){
	auto json = json_object_new_array();
	// make command for every source file for compilation
	for(size_t i = 0; i < arr_count(conf.sources); ++i){
		auto src = &conf.sources[i];
		auto object = json_object_new_object();
		generate_command(conf, src);
		// TODO: ask directory in config
		json_object_object_add(object, "directory", json_object_new_string(conf.cwd));
		json_object_object_add(object, "file", json_object_new_string(src->file));
		json_object_object_add(object, "command", json_object_new_string(src->_command));
		json_object_array_add(json, object);
	}

	auto json_string = json_object_to_json_string_ext(json, JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_SPACED);
	char* copy = str_concat((char*)json_string, "");
	json_object_put(json);
	return copy;
}
