#include "lexer.h"
#include "parser.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

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

    parse(&context);
    
    return 0;
}


