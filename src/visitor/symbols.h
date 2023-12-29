#pragma once
#include "../frontend/token.h"
#include "visitor.h"
#include "../defines.h"
#include "../ds/hashtable.h"
#include <stdint.h>

void collect_symbols( struct Visitor *_visitor, struct Node *root );


void insert_function( struct Symbol_Visitor *visitor, struct Declaration_Function *fn );

struct Symbol_Table *current_symbol_table( struct Symbol_Visitor *visitor );

struct Symbol_Table *get_symbol_table( struct Symbol_Visitor *visitor, Str function_name );
