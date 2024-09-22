#include "cleanup.h"
#include "x-watcher/array.h"
#include <dlfcn.h>
#include <stdlib.h>

inline void cleanup_fclose(FILE** f){
	if(*f == nullptr) return;
	fclose(*f);
	*f = NULL;
}

inline void cleanup_dlclose(void** handle){
	if(*handle == nullptr) return;
	dlclose(*handle);
	*handle = NULL;
}

inline void cleanup_config(config* conf){
	arr_free(conf->compile_flags);
	arr_free(conf->link_flags);
	arr_free(conf->general_flags);
	arr_free(conf->sources);
	conf->compile_flags = nullptr;
	conf->link_flags = nullptr;
	conf->general_flags = nullptr;
	conf->sources = nullptr;
}

inline void cleanup_string(char** str){
	free(*str);
	*str = nullptr;
}
