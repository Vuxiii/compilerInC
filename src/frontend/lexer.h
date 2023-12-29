#pragma once

#include "token.h"
#include "../context.h"
#include "../x86.h"

#define WHITE_SPACE 32



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
Str get_string_from( char *left, char *right );

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
