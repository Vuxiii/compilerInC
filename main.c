#include "lexer.h"
#include "parser.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct Node *NODE_BUFFER;

int main(void) {
    NODE_BUFFER = malloc(sizeof(struct Node) * NODE_BUFFER_INITIAL_SIZE);
    char *input = "fn main() {\n func(a(), 2, 3+2*6); }\n $";

    struct Context context = {
        .current_token_index = 0,
        .peek_token_index = 0,
        .current_line = 0,
        .current_position = input,
        .file_start = input,
        .filename = String( .str = "some_file_name.c", .length = 16 )
    };
    // print_tokens(&context);

    parse(&context);
    
    return 0;
}


