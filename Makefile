# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/not_archbtw/dev/c/compilerInC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/not_archbtw/dev/c/compilerInC

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/opt/homebrew/Cellar/cmake/3.28.1/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/Cellar/cmake/3.28.1/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/not_archbtw/dev/c/compilerInC/CMakeFiles /Users/not_archbtw/dev/c/compilerInC//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/not_archbtw/dev/c/compilerInC/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named compiler

# Build rule for target.
compiler: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 compiler
.PHONY : compiler

# fast build rule for target.
compiler/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/build
.PHONY : compiler/fast

src/ds/hashtable.o: src/ds/hashtable.c.o
.PHONY : src/ds/hashtable.o

# target to build an object file
src/ds/hashtable.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/ds/hashtable.c.o
.PHONY : src/ds/hashtable.c.o

src/ds/hashtable.i: src/ds/hashtable.c.i
.PHONY : src/ds/hashtable.i

# target to preprocess a source file
src/ds/hashtable.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/ds/hashtable.c.i
.PHONY : src/ds/hashtable.c.i

src/ds/hashtable.s: src/ds/hashtable.c.s
.PHONY : src/ds/hashtable.s

# target to generate assembly for a file
src/ds/hashtable.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/ds/hashtable.c.s
.PHONY : src/ds/hashtable.c.s

src/error.o: src/error.c.o
.PHONY : src/error.o

# target to build an object file
src/error.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/error.c.o
.PHONY : src/error.c.o

src/error.i: src/error.c.i
.PHONY : src/error.i

# target to preprocess a source file
src/error.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/error.c.i
.PHONY : src/error.c.i

src/error.s: src/error.c.s
.PHONY : src/error.s

# target to generate assembly for a file
src/error.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/error.c.s
.PHONY : src/error.c.s

src/frontend/lexer.o: src/frontend/lexer.c.o
.PHONY : src/frontend/lexer.o

# target to build an object file
src/frontend/lexer.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/frontend/lexer.c.o
.PHONY : src/frontend/lexer.c.o

src/frontend/lexer.i: src/frontend/lexer.c.i
.PHONY : src/frontend/lexer.i

# target to preprocess a source file
src/frontend/lexer.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/frontend/lexer.c.i
.PHONY : src/frontend/lexer.c.i

src/frontend/lexer.s: src/frontend/lexer.c.s
.PHONY : src/frontend/lexer.s

# target to generate assembly for a file
src/frontend/lexer.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/frontend/lexer.c.s
.PHONY : src/frontend/lexer.c.s

src/frontend/parser.o: src/frontend/parser.c.o
.PHONY : src/frontend/parser.o

# target to build an object file
src/frontend/parser.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/frontend/parser.c.o
.PHONY : src/frontend/parser.c.o

src/frontend/parser.i: src/frontend/parser.c.i
.PHONY : src/frontend/parser.i

# target to preprocess a source file
src/frontend/parser.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/frontend/parser.c.i
.PHONY : src/frontend/parser.c.i

src/frontend/parser.s: src/frontend/parser.c.s
.PHONY : src/frontend/parser.s

# target to generate assembly for a file
src/frontend/parser.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/frontend/parser.c.s
.PHONY : src/frontend/parser.c.s

src/interpreter.o: src/interpreter.c.o
.PHONY : src/interpreter.o

# target to build an object file
src/interpreter.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/interpreter.c.o
.PHONY : src/interpreter.c.o

src/interpreter.i: src/interpreter.c.i
.PHONY : src/interpreter.i

# target to preprocess a source file
src/interpreter.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/interpreter.c.i
.PHONY : src/interpreter.c.i

src/interpreter.s: src/interpreter.c.s
.PHONY : src/interpreter.s

# target to generate assembly for a file
src/interpreter.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/interpreter.c.s
.PHONY : src/interpreter.c.s

src/main.o: src/main.c.o
.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/main.c.s
.PHONY : src/main.c.s

src/types.o: src/types.c.o
.PHONY : src/types.o

# target to build an object file
src/types.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/types.c.o
.PHONY : src/types.c.o

src/types.i: src/types.c.i
.PHONY : src/types.i

# target to preprocess a source file
src/types.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/types.c.i
.PHONY : src/types.c.i

src/types.s: src/types.c.s
.PHONY : src/types.s

# target to generate assembly for a file
src/types.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/types.c.s
.PHONY : src/types.c.s

src/visitor/symbols.o: src/visitor/symbols.c.o
.PHONY : src/visitor/symbols.o

# target to build an object file
src/visitor/symbols.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/visitor/symbols.c.o
.PHONY : src/visitor/symbols.c.o

src/visitor/symbols.i: src/visitor/symbols.c.i
.PHONY : src/visitor/symbols.i

# target to preprocess a source file
src/visitor/symbols.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/visitor/symbols.c.i
.PHONY : src/visitor/symbols.c.i

src/visitor/symbols.s: src/visitor/symbols.c.s
.PHONY : src/visitor/symbols.s

# target to generate assembly for a file
src/visitor/symbols.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/visitor/symbols.c.s
.PHONY : src/visitor/symbols.c.s

src/visitor/visitor.o: src/visitor/visitor.c.o
.PHONY : src/visitor/visitor.o

# target to build an object file
src/visitor/visitor.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/visitor/visitor.c.o
.PHONY : src/visitor/visitor.c.o

src/visitor/visitor.i: src/visitor/visitor.c.i
.PHONY : src/visitor/visitor.i

# target to preprocess a source file
src/visitor/visitor.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/visitor/visitor.c.i
.PHONY : src/visitor/visitor.c.i

src/visitor/visitor.s: src/visitor/visitor.c.s
.PHONY : src/visitor/visitor.s

# target to generate assembly for a file
src/visitor/visitor.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/visitor/visitor.c.s
.PHONY : src/visitor/visitor.c.s

src/x86.o: src/x86.c.o
.PHONY : src/x86.o

# target to build an object file
src/x86.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/x86.c.o
.PHONY : src/x86.c.o

src/x86.i: src/x86.c.i
.PHONY : src/x86.i

# target to preprocess a source file
src/x86.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/x86.c.i
.PHONY : src/x86.c.i

src/x86.s: src/x86.c.s
.PHONY : src/x86.s

# target to generate assembly for a file
src/x86.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/x86.c.s
.PHONY : src/x86.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... compiler"
	@echo "... src/ds/hashtable.o"
	@echo "... src/ds/hashtable.i"
	@echo "... src/ds/hashtable.s"
	@echo "... src/error.o"
	@echo "... src/error.i"
	@echo "... src/error.s"
	@echo "... src/frontend/lexer.o"
	@echo "... src/frontend/lexer.i"
	@echo "... src/frontend/lexer.s"
	@echo "... src/frontend/parser.o"
	@echo "... src/frontend/parser.i"
	@echo "... src/frontend/parser.s"
	@echo "... src/interpreter.o"
	@echo "... src/interpreter.i"
	@echo "... src/interpreter.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/types.o"
	@echo "... src/types.i"
	@echo "... src/types.s"
	@echo "... src/visitor/symbols.o"
	@echo "... src/visitor/symbols.i"
	@echo "... src/visitor/symbols.s"
	@echo "... src/visitor/visitor.o"
	@echo "... src/visitor/visitor.i"
	@echo "... src/visitor/visitor.s"
	@echo "... src/x86.o"
	@echo "... src/x86.i"
	@echo "... src/x86.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

