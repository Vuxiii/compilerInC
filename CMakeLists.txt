cmake_minimum_required(VERSION 3.12)
project(CompilerInC)


# Define source files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCES
        ${SRC_DIR}/context.h
        ${SRC_DIR}/defines.h
        ${SRC_DIR}/ds/hashtable.c
        ${SRC_DIR}/ds/hashtable.h
        ${SRC_DIR}/error.c
        ${SRC_DIR}/error.h
        ${SRC_DIR}/frontend/lexer.c
        ${SRC_DIR}/frontend/lexer.h
        ${SRC_DIR}/frontend/parser.c
        ${SRC_DIR}/frontend/parser.h
        ${SRC_DIR}/frontend/token.h
        ${SRC_DIR}/include/library.h
        ${SRC_DIR}/interpreter.c
        ${SRC_DIR}/interpreter.h
        ${SRC_DIR}/main.c
        ${SRC_DIR}/types.c
        ${SRC_DIR}/types.h
        ${SRC_DIR}/visitor/symbols.c
        ${SRC_DIR}/visitor/symbols.h
        ${SRC_DIR}/visitor/visitor.c
        ${SRC_DIR}/visitor/visitor.h
        ${SRC_DIR}/x86.c
        ${SRC_DIR}/x86.h
)

# Add executable
add_executable(compiler ${SOURCES})
# Set C standard to C17
set_target_properties(compiler PROPERTIES
        C_STANDARD 17
        C_STANDARD_REQUIRED ON
)
# Set compiler flags
target_compile_options(compiler PRIVATE -Wall -Wextra -pedantic)

# Optionally set additional compiler options or include directories
 target_compile_options(compiler PRIVATE -I${SRC_DIR}/include)

# Optionally link external libraries
# target_link_libraries(my_project PUBLIC some_library)

# Set output directory for the executable
set_target_properties(compiler PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)