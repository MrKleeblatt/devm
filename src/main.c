#include "command_generator.h"
#include "devm_api.h"
#include "cli.h"
#include "cleanup.h"
#include "config_loader.h"
#include <dlfcn.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <unistd.h>

// Idee:
//	- Dynamische Bibliothek, die Methoden definiert
//	- Befehl, der automatisch die Config neu kompiliert und neu lädt
//		-> File Watcher auf Config?
//	- Namen der zu kompilierenden Dateien
//	- restliche Parameter
//		-> https://clang.llvm.org/docs/ClangCommandLineReference.html
//	- Compiler als String anzugeben
//	- JSON für compile_commands.json generieren
//	- File watcher auf src directory
//
// Neovim-Integration
//	- Plugin, welches per IPC auf devm wartet und dann :LspRestart ausführt, wenn das entsprechende Signal kommt
//		-> https://github.com/siffiejoe/lua-luaipc
//		-> https://medium.com/@the_daft_introvert/inter-process-communication-in-operating-systems-a-comprehensive-guide-with-real-life-examples-and-c508cf3bfb1a#c7a4
//	
// CLI:
//	- devm
//		-> erstellt die `compile_commands.json`
//	- devm compile
//		-> führt `devm` aus
//		-> kompiliert die Dateien
//	- devm build
//		-> führt `devm compile` aus
//		-> baut das Projekt (mit Verlinken usw.)
//	- devm run
//		-> führt `devm build` aus
//		-> führt die erstellte EXE aus
//
//



struct version_s* version;
load_config_t load_config;


// TODO: better logging
int main(int argc, char** argv) {
	[[maybe_unused]] cli options = cli_parse(argc, argv);
	String cwd = getcwd(nullptr, 0); // GNU extension. Buffer is automatically allocated on the heap and with sufficient size.
	ensure_build_directory(cwd);
	Dll handle = read_dll();
	// initialize and load config
	Config conf = {0};
	init_config(&conf, cwd);
	load_config(&conf);
	check_config(&conf);

	String json = generate_json(conf);
	File compile_commands = fopen("./build/compile_commands.json", "w");
	// TODO: error handling
	fprintf(compile_commands, "%s", json);
	// TODO: error handling

	//
	// run compilation command
	// make command for linkage
	// run command
	return 0;
}
