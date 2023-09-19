#include "error.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void emit_error_( struct Context *context, struct Error_Params error ) {
    print_string(context->filename);
    print_string(String(.str = ":", .length = 1));
    if (error.token)
        print_int((int)error.token->line);
    else if (error.node)
        print_int((int)error.node->line);
        
    print_string(String(.str = ": error: ", .length = 9));
    if (error.error_string)
        print_string(error.error_string);
    print_string(String(.str = "\n", .length = 1));
    if (error.token) {
        print_string(String(.str = "Actual: ", .length = 8));
        print_string(String(.str = context->file_start + error.token->left, 
                            .length = error.token->right - error.token->left));
    }
    if (error.node) {
        print_string(String(.str = "Line >> ", .length = 8));
        print_string(String(.str = context->file_start + error.node->left, 
                            .length = error.node->right - error.node->left));

    }
    print_string( String( .str = "\n", .length = 1 ) );
    _Exit(-1);
}

void assert_token_type_( struct Context *context, struct Assert_Token_Type error ) {
    if (error.which == PEEK) {
        if (peek_token(context)->token_type != error.expected_token) {
            emit_error(context, .token = peek_token(context),
                              .error_string = error.error_string);
        }
    } else {
        if (current_token(context)->token_type != error.expected_token) {
            emit_error(context, .token = current_token(context),
                              .error_string = error.error_string);
        }
    }
}
