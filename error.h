#pragma once

#include "lexer.h"
#include "string.h"

struct Error_Params {
    struct String *error_string;
    struct Token *token;
    struct Node *node;
};

enum CURRENT_OR_PEEK {
    PEEK,
    CURRENT,
};

struct Assert_Token_Type {
    struct String *error_string;
    enum TOKEN expected_token;
    enum CURRENT_OR_PEEK which;
};

void emit_error_( struct Context *context, struct Error_Params error );

void assert_token_type_( struct Context *context, struct Assert_Token_Type error );

#define emit_error(context, ...) emit_error_((context), (struct Error_Params){__VA_ARGS__})

#define assert_token_type(context, ...) assert_token_type_((context), (struct Assert_Token_Type){__VA_ARGS__}) 
