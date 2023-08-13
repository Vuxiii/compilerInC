#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "error.h"
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

    char *input = malloc( sizeof(char) * sb.st_size );

    if (read(fd, input, sb.st_size) == -1) {
        perror("Reading source file");
        exit(EXIT_FAILURE);
    }

    struct Context context = {
        .current_token_index = 0,
        .peek_token_index = 0,
        .current_line = 1,
        .current_position = input,
        .file_start = input,
        .filename = String( .str = filename, .length = strlen(filename) )
    };
    // print_tokens(&context);

    struct Node *root = parse(&context);
    
    struct Runtime runtime = (struct Runtime) {
        .stack_size = STACK_SIZE,
        .heap_size  = HEAP_SIZE,
        .stack = malloc(sizeof(char) * STACK_SIZE),
        .heap  = malloc(sizeof(char) * HEAP_SIZE),
    };

    interpret(&runtime, root);

    return 0;
}


