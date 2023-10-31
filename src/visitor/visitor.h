#pragma once
#include <stdint.h>
#include "../context.h"
#include "../token.h"
#include "../string.h"
#include "../defines.h"
#include "../ds/hashtable.h"

enum Visitor_Kind {
    SYMBOL_VISITOR
};

enum Visitor_State {
    VISITOR_NODE_ENTER,
    VISITOR_NODE_LEAVE,
    VISITOR_NODE_BEFORE_CHILD,
    VISITOR_NODE_AFTER_CHILD,
};

struct Symbol_Visitor {
    struct Context *context;

    uint64_t function_count;
    uint64_t function_size;

    ARRAY(struct Symbol_Table *) functions;
};

struct Symbol_Table {
    struct Declaration_Function *fn;
    struct HashTable symbol_table;
};

struct Visitor {
    enum Visitor_Kind kind;
    enum Visitor_State state;
    union {
        struct Symbol_Visitor symbol_visitor;
    } contents;
};

void visit( struct Node *node, struct Visitor *visitor );
