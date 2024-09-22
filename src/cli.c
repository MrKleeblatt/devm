#include <getopt.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cli.h"

struct option cli_options[] = {
	{ "watch", no_argument, nullptr, OPTION_WATCH },
};
const char* cli_subcommands[] = { "compile", "build", "run", nullptr };

static void parse_arguments(cli* c, int argc, char** argv);
static void parse_subcommand(cli* c, int argc, char** argv);

cli cli_parse(int argc, char** argv){
	cli result = {
		.watch=false,
		.subcommand=_OPTION_SUBCOMMAND__SIZE,
	};
	parse_arguments(&result, argc, argv);
	parse_subcommand(&result, argc, argv);

	return result;
}

static void parse_arguments(cli* c, int argc, char** argv) {
	int index;
	int opt = 0;
	do {
		// If the program accepts only long options, then optstring should be specified as an empty string (""), not NULL.
		// https://www.man7.org/linux/man-pages/man3/getopt.3.html
		opt = getopt_long(argc, argv, "", cli_options, &index);
		switch(opt){
			case OPTION_WATCH: c->watch = true; break;
		}
	} while(opt != -1);
}

static void parse_subcommand(cli* c, int argc, char** argv) {
	if(optind == argc) return; // no subcommand
	if(optind+1 < argc) {
		errno = E2BIG;
		perror("Don't provide more than one subcommand.");
		exit(errno);
	}
	char* subcommand = argv[optind];
	// just to be sure
	if((sizeof cli_subcommands / sizeof *cli_subcommands) != _OPTION_SUBCOMMAND__SIZE) {
		errno = ENOSYS;
		perror("Sorry, my fault. option_subcommands don't have the same size.");
		exit(errno);
	}
	for (size_t i  = 0; i < (sizeof(cli_subcommands) / sizeof *cli_subcommands); ++i) {
		if (strcmp(subcommand, cli_subcommands[i])) continue;
		c->subcommand = i;
		break;
	}
}
