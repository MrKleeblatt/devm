#include "config_loader.h"
#include "cleanup.h"
#include "api/array.h"
#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

struct version_s default_version = {1, 0};
#define build_dir_name "./build"
#define config_dir_name "./build/config"
#define out_dir_name "./build/out"
static void makedir(char* cwd, const char* name);

void check_config(config* conf){
	if(conf->compiler == nullptr) conf->compiler = "clang";
	if(conf->exe == nullptr) conf->exe = "Main";
}

// exits on failure
void ensure_build_directory(char* cwd){
	makedir(cwd, build_dir_name);
	makedir(cwd, config_dir_name);
	makedir(cwd, out_dir_name);
}

dll read_dll(){
	char* libname = config_dir_name "/lib" config_lib_name ".so";
	dll handle = dlopen(libname, RTLD_LAZY | RTLD_GLOBAL);
	if(handle == nullptr) {
		fprintf(stderr, "could not find %s\n", libname);
		exit(0);
		// TODO: exit with helpful error message
	}
	load_config = (load_config_t) dlsym(handle, load_config_name);
	if(load_config == nullptr) {
		fprintf(stderr, "could not load %s\n", load_config_name);
		exit(0);
		// TODO: error handling
	}
	version = dlsym(handle, "version");
	if(version == nullptr){
		version = &default_version;
	}
	return handle;
}

void init_config(config* conf, char* cwd){
	conf->cwd = cwd;
	arr_init(conf->sources);
	arr_init(conf->link_flags);
	arr_init(conf->compile_flags);
	arr_init(conf->general_flags);
}

static void makedir(char* cwd, const char* name){
	const int permissions = 0750;
	File build_dir = fopen(name, "r");
	if(build_dir == nullptr) {
		// TODO: check errno
		printf("No `build` directory in %s\nWould you like to create one? [y/n] ", cwd);
		char answer = getchar();
		getchar(); // discard newline-char
		if(answer != 'y'){
			if(answer != 'n') fprintf(stderr, "unrecognised answer\n");
			fprintf(stderr, "quitting now...\n");
			exit(errno);
		}
		auto err = mkdir(name, permissions);
		if(err) {
			// TODO: error handling
		}
	}
}
