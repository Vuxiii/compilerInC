#ifndef LEXER_H
#define LEXER_H
#define TOKEN_QUEUE_SIZE 2
#include "string.h"
#include "token.h"


#define WHITE_SPACE 32


struct Context {
    struct Token TOKEN_QUEUE[TOKEN_QUEUE_SIZE];
    char *STRING_STORE[2048];
    struct String *filename;
    char *file_start;
    char *current_position;
    char current_token_index;
    char peek_token_index;
    unsigned int current_line;
    
};

/**
 *  This funciton retrieves the next token,
 *  and places it inside the
 *  current slot in the token queue.
 *  It returns the new pointer location.
 */
void next_token( struct Context *context );

/**
 *  This function returns a string as represented
 *  by [left, right[
 */
struct String *get_string_from( char *left, char *right);

/**
 * Return the current Token
 */
struct Token *current_token( struct Context *context );
/**
 * Return the peek Token
 */
struct Token *peek_token( struct Context *context );
void print_tokens( struct Context *context );

int is_valid_identifier_char(char c);

#endif
