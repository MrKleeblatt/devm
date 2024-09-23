#pragma once

#include "api/devm_api.h"

char* escape_path(char* path);
char* get_source_path(config conf, source src);
void generate_command(config conf, source* src);
char* generate_json(config conf);
