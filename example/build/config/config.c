#include "devm_api.h"
#include "array.h"

struct version_s version = {0, 1};

void load_config(config* conf){

	conf->compiler = "ccache clang";
	arr_add(conf->compile_flags, "-Wall");

	source main_source = devm_source("src/main.c");
	arr_add(main_source.extra_flags, "-Wno-gnu-statement-expression");
	arr_add(conf->sources, main_source);

	arr_add(conf->sources, devm_source("src/test.c"));
}
