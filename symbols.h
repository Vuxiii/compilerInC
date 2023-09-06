#pragma once
#include "token.h"
#include "visitor.h"
#include "defines.h"
#include <stdint.h>

void collect_symbols( struct Visitor *_visitor, struct Node *root );


struct UInt64Result lookup_symbol( struct Symbol_Table *table, struct String *symbol );
