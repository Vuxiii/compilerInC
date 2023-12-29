#include "error.h"
#include "include/library.h"
#include <stdlib.h>
#include <unistd.h>

void emit_allocation_error_( struct Allocation_Error_Params error ) {
    print("Unable to allocate memory for [{str}] Exiting...\n", error.error_message );
    _Exit(-1);
}

void emit_error_( struct Context *context, struct Error_Params error ) {
    u32 lineno = error.token ? error.token->line : error.node->line;

    print("{str}:{u32}: Error: {str}\n", context->filename, lineno, error.error_string);

    if (error.token) {
        print("Actual: {str}\n", (Str){
            context->file_start + error.token->left,
            error.token->right - error.token->left
        });
    }
    if (error.node) {
        print("Line >> {str}\n", (Str){
            context->file_start + error.node->left,
            error.node->right - error.node->left
        });
    }
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
