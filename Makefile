COMPILER=clang
OPTIONS=-g -pedantic -Wall -Wextra -Wshadow -Wunreachable-code
COMPILE=$(COMPILER) $(OPTIONS)
BUILD=build

# $(BUILD)/*.o expands to all .o files in the $(BUILD) directory
# In this case, we'll get $(BUILD)/file1.o $(BUILD)/file2.o
a.out: main.c symbols.o visitor.o x86.o error.o interpreter.o lexer.o parser.o ssa.o string.o ir.o

	$(COMPILE) $< $(BUILD)/*.o -o $@

%.o: %.c build
	$(COMPILE) -c $< -o $(BUILD)/$@


# $(BUILD)/file2.o: file2.cpp build
# 	$(COMPILE) -c $< -o $@

# Make the build directory if it doesn't exist
build:
	mkdir -p $(BUILD)

# Delete the build directory and program
clean:
	rm -rf $(BUILD) a.out

# These rules do not correspond to a specific file
.PHONY: build clean