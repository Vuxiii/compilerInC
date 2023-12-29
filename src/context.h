#pragma once
#define TOKEN_QUEUE_SIZE 2

#include "include/library.h"
#include "frontend/lexer.h"
#include "frontend/token.h"
#include "defines.h"

struct Context {
    struct Token TOKEN_QUEUE[TOKEN_QUEUE_SIZE];
    char *STRING_STORE[2048];

    Str filename;
    char *file_start;
    char *current_position;
    char current_token_index;
    char peek_token_index;
    unsigned long current_line;
    
    struct ASM_Instruction *ASM_INSTRUCTION_BUFFER;
    unsigned int instruction_index;
    unsigned int instruction_size;

    unsigned int type_count;
    unsigned int type_size;
    ARRAY(struct User_Type) user_types;

};
