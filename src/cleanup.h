#pragma once

#include "devm_api.h"
#include <stdio.h>

void cleanup_fclose(FILE** f);
void cleanup_dlclose(void** handle);
void cleanup_config(config* conf);
void cleanup_string(char** str);

#define File [[gnu::cleanup(cleanup_fclose)]] FILE*
#define Dll [[gnu::cleanup(cleanup_dlclose)]] void*
#define Config [[gnu::cleanup(cleanup_config)]] config
#define String [[gnu::cleanup(cleanup_string)]] char*
#define StringBuilder [[gnu::cleanup(string_builder_free)]] string_builder
