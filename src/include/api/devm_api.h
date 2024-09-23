#pragma once

struct [[gnu::packed]] version_s {
	unsigned char major;
	unsigned char minor;
};

typedef enum {
	// relative to project root
	// => one directory above build configuration definition
	ROOT_PROJECT,
	// relative to current working directory
	ROOT_CWD,
	// absolute path
	ROOT_ABSOLUTE,
	// relative to build configuration definition
	ROOT_RELATIVE,
	// relative to src directory
	// => expects a directory called `src` in ROOT_PROJECT
	ROOT_SRC,
} root_dir;

typedef struct [[gnu::packed]] {
	char* file;
	char** extra_flags;
	char* _command;
	bool _must_free;
} source;


typedef struct [[gnu::packed]] {
	// current working directory
	char* cwd;
	// the name of the executable to produce
	char* exe;
	// the compiler's name
	char* compiler;
	// compiler flags during compilation
	char** compile_flags;
	// compiler flags during linkage
	char** link_flags;
	// general flags for the compiler (will be in both compile time and linkage time)
	char** general_flags;
	// the source files to compile
	source* sources;
	// whether or not to expand cwd during compilation
	bool expand_cwd;
} config;

source* devm_source_dir(char* directory, char* file_extension);
source* devm_source_dir_filter(char* directory, bool(*filter)(char* filename, void* context), void* context);
source devm_source(char* file);

typedef void(*load_config_t)(config*);

