# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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

# Include any dependencies generated for this target.
include CMakeFiles/compiler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/compiler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compiler.dir/flags.make

CMakeFiles/compiler.dir/src/ds/hashtable.c.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/ds/hashtable.c.o: src/ds/hashtable.c
CMakeFiles/compiler.dir/src/ds/hashtable.c.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/compiler.dir/src/ds/hashtable.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/ds/hashtable.c.o -MF CMakeFiles/compiler.dir/src/ds/hashtable.c.o.d -o CMakeFiles/compiler.dir/src/ds/hashtable.c.o -c /Users/not_archbtw/dev/c/compilerInC/src/ds/hashtable.c

CMakeFiles/compiler.dir/src/ds/hashtable.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/compiler.dir/src/ds/hashtable.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/not_archbtw/dev/c/compilerInC/src/ds/hashtable.c > CMakeFiles/compiler.dir/src/ds/hashtable.c.i

CMakeFiles/compiler.dir/src/ds/hashtable.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/compiler.dir/src/ds/hashtable.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/not_archbtw/dev/c/compilerInC/src/ds/hashtable.c -o CMakeFiles/compiler.dir/src/ds/hashtable.c.s

CMakeFiles/compiler.dir/src/error.c.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/error.c.o: src/error.c
CMakeFiles/compiler.dir/src/error.c.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/compiler.dir/src/error.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/error.c.o -MF CMakeFiles/compiler.dir/src/error.c.o.d -o CMakeFiles/compiler.dir/src/error.c.o -c /Users/not_archbtw/dev/c/compilerInC/src/error.c

CMakeFiles/compiler.dir/src/error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/compiler.dir/src/error.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/not_archbtw/dev/c/compilerInC/src/error.c > CMakeFiles/compiler.dir/src/error.c.i

CMakeFiles/compiler.dir/src/error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/compiler.dir/src/error.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/not_archbtw/dev/c/compilerInC/src/error.c -o CMakeFiles/compiler.dir/src/error.c.s

CMakeFiles/compiler.dir/src/frontend/lexer.c.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/frontend/lexer.c.o: src/frontend/lexer.c
CMakeFiles/compiler.dir/src/frontend/lexer.c.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/compiler.dir/src/frontend/lexer.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/frontend/lexer.c.o -MF CMakeFiles/compiler.dir/src/frontend/lexer.c.o.d -o CMakeFiles/compiler.dir/src/frontend/lexer.c.o -c /Users/not_archbtw/dev/c/compilerInC/src/frontend/lexer.c

CMakeFiles/compiler.dir/src/frontend/lexer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/compiler.dir/src/frontend/lexer.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/not_archbtw/dev/c/compilerInC/src/frontend/lexer.c > CMakeFiles/compiler.dir/src/frontend/lexer.c.i

CMakeFiles/compiler.dir/src/frontend/lexer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/compiler.dir/src/frontend/lexer.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/not_archbtw/dev/c/compilerInC/src/frontend/lexer.c -o CMakeFiles/compiler.dir/src/frontend/lexer.c.s

CMakeFiles/compiler.dir/src/frontend/parser.c.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/frontend/parser.c.o: src/frontend/parser.c
CMakeFiles/compiler.dir/src/frontend/parser.c.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/compiler.dir/src/frontend/parser.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/frontend/parser.c.o -MF CMakeFiles/compiler.dir/src/frontend/parser.c.o.d -o CMakeFiles/compiler.dir/src/frontend/parser.c.o -c /Users/not_archbtw/dev/c/compilerInC/src/frontend/parser.c

CMakeFiles/compiler.dir/src/frontend/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/compiler.dir/src/frontend/parser.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/not_archbtw/dev/c/compilerInC/src/frontend/parser.c > CMakeFiles/compiler.dir/src/frontend/parser.c.i

CMakeFiles/compiler.dir/src/frontend/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/compiler.dir/src/frontend/parser.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/not_archbtw/dev/c/compilerInC/src/frontend/parser.c -o CMakeFiles/compiler.dir/src/frontend/parser.c.s

CMakeFiles/compiler.dir/src/interpreter.c.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/interpreter.c.o: src/interpreter.c
CMakeFiles/compiler.dir/src/interpreter.c.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/compiler.dir/src/interpreter.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/interpreter.c.o -MF CMakeFiles/compiler.dir/src/interpreter.c.o.d -o CMakeFiles/compiler.dir/src/interpreter.c.o -c /Users/not_archbtw/dev/c/compilerInC/src/interpreter.c

CMakeFiles/compiler.dir/src/interpreter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/compiler.dir/src/interpreter.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/not_archbtw/dev/c/compilerInC/src/interpreter.c > CMakeFiles/compiler.dir/src/interpreter.c.i

CMakeFiles/compiler.dir/src/interpreter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/compiler.dir/src/interpreter.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/not_archbtw/dev/c/compilerInC/src/interpreter.c -o CMakeFiles/compiler.dir/src/interpreter.c.s

CMakeFiles/compiler.dir/src/main.c.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/main.c.o: src/main.c
CMakeFiles/compiler.dir/src/main.c.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/compiler.dir/src/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/main.c.o -MF CMakeFiles/compiler.dir/src/main.c.o.d -o CMakeFiles/compiler.dir/src/main.c.o -c /Users/not_archbtw/dev/c/compilerInC/src/main.c

CMakeFiles/compiler.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/compiler.dir/src/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/not_archbtw/dev/c/compilerInC/src/main.c > CMakeFiles/compiler.dir/src/main.c.i

CMakeFiles/compiler.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/compiler.dir/src/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/not_archbtw/dev/c/compilerInC/src/main.c -o CMakeFiles/compiler.dir/src/main.c.s

CMakeFiles/compiler.dir/src/types.c.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/types.c.o: src/types.c
CMakeFiles/compiler.dir/src/types.c.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/compiler.dir/src/types.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/types.c.o -MF CMakeFiles/compiler.dir/src/types.c.o.d -o CMakeFiles/compiler.dir/src/types.c.o -c /Users/not_archbtw/dev/c/compilerInC/src/types.c

CMakeFiles/compiler.dir/src/types.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/compiler.dir/src/types.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/not_archbtw/dev/c/compilerInC/src/types.c > CMakeFiles/compiler.dir/src/types.c.i

CMakeFiles/compiler.dir/src/types.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/compiler.dir/src/types.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/not_archbtw/dev/c/compilerInC/src/types.c -o CMakeFiles/compiler.dir/src/types.c.s

CMakeFiles/compiler.dir/src/visitor/symbols.c.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/visitor/symbols.c.o: src/visitor/symbols.c
CMakeFiles/compiler.dir/src/visitor/symbols.c.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/compiler.dir/src/visitor/symbols.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/visitor/symbols.c.o -MF CMakeFiles/compiler.dir/src/visitor/symbols.c.o.d -o CMakeFiles/compiler.dir/src/visitor/symbols.c.o -c /Users/not_archbtw/dev/c/compilerInC/src/visitor/symbols.c

CMakeFiles/compiler.dir/src/visitor/symbols.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/compiler.dir/src/visitor/symbols.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/not_archbtw/dev/c/compilerInC/src/visitor/symbols.c > CMakeFiles/compiler.dir/src/visitor/symbols.c.i

CMakeFiles/compiler.dir/src/visitor/symbols.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/compiler.dir/src/visitor/symbols.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/not_archbtw/dev/c/compilerInC/src/visitor/symbols.c -o CMakeFiles/compiler.dir/src/visitor/symbols.c.s

CMakeFiles/compiler.dir/src/visitor/typechecker.c.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/visitor/typechecker.c.o: src/visitor/typechecker.c
CMakeFiles/compiler.dir/src/visitor/typechecker.c.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/compiler.dir/src/visitor/typechecker.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/visitor/typechecker.c.o -MF CMakeFiles/compiler.dir/src/visitor/typechecker.c.o.d -o CMakeFiles/compiler.dir/src/visitor/typechecker.c.o -c /Users/not_archbtw/dev/c/compilerInC/src/visitor/typechecker.c

CMakeFiles/compiler.dir/src/visitor/typechecker.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/compiler.dir/src/visitor/typechecker.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/not_archbtw/dev/c/compilerInC/src/visitor/typechecker.c > CMakeFiles/compiler.dir/src/visitor/typechecker.c.i

CMakeFiles/compiler.dir/src/visitor/typechecker.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/compiler.dir/src/visitor/typechecker.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/not_archbtw/dev/c/compilerInC/src/visitor/typechecker.c -o CMakeFiles/compiler.dir/src/visitor/typechecker.c.s

CMakeFiles/compiler.dir/src/visitor/visitor.c.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/visitor/visitor.c.o: src/visitor/visitor.c
CMakeFiles/compiler.dir/src/visitor/visitor.c.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/compiler.dir/src/visitor/visitor.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/visitor/visitor.c.o -MF CMakeFiles/compiler.dir/src/visitor/visitor.c.o.d -o CMakeFiles/compiler.dir/src/visitor/visitor.c.o -c /Users/not_archbtw/dev/c/compilerInC/src/visitor/visitor.c

CMakeFiles/compiler.dir/src/visitor/visitor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/compiler.dir/src/visitor/visitor.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/not_archbtw/dev/c/compilerInC/src/visitor/visitor.c > CMakeFiles/compiler.dir/src/visitor/visitor.c.i

CMakeFiles/compiler.dir/src/visitor/visitor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/compiler.dir/src/visitor/visitor.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/not_archbtw/dev/c/compilerInC/src/visitor/visitor.c -o CMakeFiles/compiler.dir/src/visitor/visitor.c.s

CMakeFiles/compiler.dir/src/x86.c.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/x86.c.o: src/x86.c
CMakeFiles/compiler.dir/src/x86.c.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/compiler.dir/src/x86.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compiler.dir/src/x86.c.o -MF CMakeFiles/compiler.dir/src/x86.c.o.d -o CMakeFiles/compiler.dir/src/x86.c.o -c /Users/not_archbtw/dev/c/compilerInC/src/x86.c

CMakeFiles/compiler.dir/src/x86.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/compiler.dir/src/x86.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/not_archbtw/dev/c/compilerInC/src/x86.c > CMakeFiles/compiler.dir/src/x86.c.i

CMakeFiles/compiler.dir/src/x86.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/compiler.dir/src/x86.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/not_archbtw/dev/c/compilerInC/src/x86.c -o CMakeFiles/compiler.dir/src/x86.c.s

# Object files for target compiler
compiler_OBJECTS = \
"CMakeFiles/compiler.dir/src/ds/hashtable.c.o" \
"CMakeFiles/compiler.dir/src/error.c.o" \
"CMakeFiles/compiler.dir/src/frontend/lexer.c.o" \
"CMakeFiles/compiler.dir/src/frontend/parser.c.o" \
"CMakeFiles/compiler.dir/src/interpreter.c.o" \
"CMakeFiles/compiler.dir/src/main.c.o" \
"CMakeFiles/compiler.dir/src/types.c.o" \
"CMakeFiles/compiler.dir/src/visitor/symbols.c.o" \
"CMakeFiles/compiler.dir/src/visitor/typechecker.c.o" \
"CMakeFiles/compiler.dir/src/visitor/visitor.c.o" \
"CMakeFiles/compiler.dir/src/x86.c.o"

# External object files for target compiler
compiler_EXTERNAL_OBJECTS =

compiler: CMakeFiles/compiler.dir/src/ds/hashtable.c.o
compiler: CMakeFiles/compiler.dir/src/error.c.o
compiler: CMakeFiles/compiler.dir/src/frontend/lexer.c.o
compiler: CMakeFiles/compiler.dir/src/frontend/parser.c.o
compiler: CMakeFiles/compiler.dir/src/interpreter.c.o
compiler: CMakeFiles/compiler.dir/src/main.c.o
compiler: CMakeFiles/compiler.dir/src/types.c.o
compiler: CMakeFiles/compiler.dir/src/visitor/symbols.c.o
compiler: CMakeFiles/compiler.dir/src/visitor/typechecker.c.o
compiler: CMakeFiles/compiler.dir/src/visitor/visitor.c.o
compiler: CMakeFiles/compiler.dir/src/x86.c.o
compiler: CMakeFiles/compiler.dir/build.make
compiler: CMakeFiles/compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/not_archbtw/dev/c/compilerInC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking C executable compiler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compiler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compiler.dir/build: compiler
.PHONY : CMakeFiles/compiler.dir/build

CMakeFiles/compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compiler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compiler.dir/clean

CMakeFiles/compiler.dir/depend:
	cd /Users/not_archbtw/dev/c/compilerInC && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/not_archbtw/dev/c/compilerInC /Users/not_archbtw/dev/c/compilerInC /Users/not_archbtw/dev/c/compilerInC /Users/not_archbtw/dev/c/compilerInC /Users/not_archbtw/dev/c/compilerInC/CMakeFiles/compiler.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/compiler.dir/depend

