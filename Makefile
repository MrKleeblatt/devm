NAME=devm
IGNORE := $(shell mkdir -p ./out/objects/)

all: build run

build: clear_console clean compile

CC=clang
DEBUG=-g
COMPILE_FLAGS=-g --std=gnu2x -Wall -Wextra -Wpedantic -Werror -O0
LINK_FLAGS=-lm -Wl,--export-dynamic -lcurl -ljson-c

SOURCES=$(shell find ./src/ -name '*.c')
OBJECTS=$(addprefix ./out/objects/,$(SOURCES:./src/%.c=%.o))
INCLUDES=-I./dep/ -I./src/include/
STATIC_LIBS=


clear_console:
	@clear

clean:
	rm -f $(OBJECTS)
	rm -f ./out/$(NAME)

compile: link
link: $(OBJECTS)
	$(CC) $(COMPILE_FLAGS) $(LINK_FLAGS) -o ./out/$(NAME) $(OBJECTS) $(STATIC_LIBS)

# compile
./out/objects/%.o: ./src/%.c
	$(CC) $(COMPILE_FLAGS) $(INCLUDES) -c -o $@ $<

run:
	@echo
	@ cd example && pwd && ../out/$(NAME)
	@echo
