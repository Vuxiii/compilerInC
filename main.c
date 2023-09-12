#include "parser.h"
#include "context.h"
#include "interpreter.h"
#include "x86.h"
#include "symbols.h"
#include "visitor.h"

#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define STACK_SIZE 4*1024*1024
#define HEAP_SIZE 8*1024*1024

struct Node *NODE_BUFFER;

int main( int argc, char **argv ) { 

    char *filename;
    if (argc == 1) {
        filename = "src.txt";
    } else if (argc == 2) {
        filename = argv[1];
    }

    NODE_BUFFER = malloc(sizeof(struct Node) * NODE_BUFFER_INITIAL_SIZE);
    
    int fd = open( filename, O_RDONLY );
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("File Information");
        exit(EXIT_FAILURE);
    }

    char *input = malloc( sizeof(char) * (size_t)sb.st_size );

    if (read(fd, input, (size_t)sb.st_size) == -1) {
        perror("Reading source file");
        exit(EXIT_FAILURE);
    }

    struct Context context = {
        .current_token_index = 0,
        .peek_token_index = 0,
        .current_line = 1,
        .current_position = input,
        .file_start = input,
        .filename = String( .str = filename, .length = strlen(filename) ),
        .instruction_index = 0,
        .instruction_size = sizeof(struct ASM_Instruction) * 1024,
        .ASM_INSTRUCTION_BUFFER = malloc(sizeof(struct ASM_Instruction) * 1024)
    };
    // print_tokens(&context);

    struct Node *root = parse(&context);

    struct Visitor symbol_visitor = (struct Visitor) {
        .kind = SYMBOL_VISITOR,
        .contents.symbol_visitor = (struct Symbol_Visitor) {
            .context = &context,

            .symbol_table_size = 1,
            .symbol_table_count = 0,
            .symbol_table = malloc(sizeof(struct Symbol_Table) * 1),
            .table_names = malloc(sizeof(struct String) * 1)
        }
    };

    symbol_visitor.contents.symbol_visitor.symbol_table[0] = (struct Symbol_Table) {
        .size = 128,
        .count = 0,
        .symbols = malloc(sizeof(struct String) * 128)
    };

    
    visit(root, &symbol_visitor);

    
    for (uint64_t i = 0; i < symbol_visitor.contents.symbol_visitor.symbol_table_count; ++i) {
        // Each function
        struct Symbol_Table *table = &symbol_visitor.contents.symbol_visitor.symbol_table[i];
        printf("Function [%s]\n", symbol_visitor.contents.symbol_visitor.table_names[i].str);
        for (uint64_t j = 0; j < table->count; ++j) {
            printf("\tSymbol [%s]\n", table->symbols[j].str);
        }
    }


    struct Runtime runtime = (struct Runtime) {
        .stack_size = STACK_SIZE / sizeof(int64_t),
        .heap_size  = HEAP_SIZE / sizeof(int64_t),
        .stack = malloc(sizeof(int64_t) * STACK_SIZE),
        .heap  = malloc(sizeof(int64_t) * HEAP_SIZE),
    };

    RSP(&runtime) = (STACK_SIZE) / sizeof(int64_t) - 1;

    convert_to_x86(&context, root);
    
    interpret(&runtime, &context);

    return 0;
}
