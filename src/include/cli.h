#pragma once
#include <getopt.h>

enum cli_option {
	OPTION_WATCH,
};

enum cli_subcommand {
	OPTION_SUBCOMMAND_COMPILE = 1,
	OPTION_SUBCOMMAND_BUILD,
	OPTION_SUBCOMMAND_RUN,
	_OPTION_SUBCOMMAND__SIZE,
};

typedef struct {
	bool watch;
	enum cli_subcommand subcommand;
} cli;


cli cli_parse(int argc, char** argv);
