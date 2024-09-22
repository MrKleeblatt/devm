# Development manager

A build tool for low-level developers that aims to be
- simple
- fast
- highly extensible
because configuration is written as pure code and compiled to a shared object.

`devm` expects the following file structure.

```
.
└── build/
    ├── libconfig.so
    ├── compile_commands.json
    └── out/
 ```

`libconfig.so` must export the following symbols.

```c
#include "devm_api.h"
#include "x-watcher/array.h"

struct version_s version = {0, 1};

void load_config(config* conf){

    // example configuration
	conf->compiler = "ccache clang";
	arr_add(conf->compile_flags, "-Wall");

	source main_source = devm_source("src/main.c");
	arr_add(main_source.extra_flags, "-Wno-gnu-statement-expression");
	arr_add(conf->sources, main_source);

	arr_add(conf->sources, devm_source("src/test.c"));
}
```

You can also source an entire directory with the following API functions.

```c
source* devm_source_dir(char* directory, char* file_extension);
source* devm_source_dir_filter(char* directory, bool(*filter)(char* filename, void* context), void* context);
```

`context` is just some value you can pass to `devm_source_dir_filter` and retrieve in your filter function. Nothing fancy.

## Dependencies

- `libcurl` for URL escaping, may be removed later
- `json-c` for generating `compile_commands.json` file which is needed for lsp's like clangd
