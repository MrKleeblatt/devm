#pragma once

#include "devm_api.h"

typedef void* dll;

// config from shared object
extern struct version_s* version;
#define version_name "version"
extern load_config_t load_config;
#define config_lib_name "config"
#define load_config_name "load_config"


void check_config(config* conf);
void ensure_build_directory(char* cwd);
dll read_dll();
void init_config(config* conf, char* cwd);

