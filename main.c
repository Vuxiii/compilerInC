#include "lexer.h"
#include "parser.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct Node *NODE_BUFFER;

int main(void) {
    NODE_BUFFER = malloc(sizeof(struct Node) * NODE_BUFFER_INITIAL_SIZE);
    char *input = "fn main() { let a: int = 2; a == 2; let Point :: struct { x: int; y: int; }; } $";

    struct Context context = {
        .current_token_index = 0,
        .peek_token_index = 0,
        .current_line = 1,
        .current_position = input,
        .file_start = input,
        .filename = String( .str = "inmem.c", .length = 7)
    };
    // print_tokens(&context);

    parse(&context);
    
    return 0;
}


