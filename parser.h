#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"

#define NODE_BUFFER_INITIAL_SIZE 2048
struct Node *parse( struct Context *context ); 

struct Node *parse_toplevel_statement( struct Context *context );

struct Node *parse_function_declaration( struct Context *context );

struct Node *parse_statement( struct Context *context );

struct Node *parse_assignment( struct Context *context );

struct Node *parse_declaration( struct Context *context );

struct Node *parse_expression( struct Context *context );

struct Node *parse_comparison_expression( struct Context *context );

struct Node *parse_sum( struct Context *context );

struct Node *parse_mult( struct Context *context );

struct Node *parse_token( struct Context *context );

struct Node *get_empty_node();
#endif
