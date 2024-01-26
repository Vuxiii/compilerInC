#pragma once
#include "../context.h"
#include "../frontend/token.h"
#include "../defines.h"
#include "../ds/hashtable.h"
#include "../include/library.h"

enum Visitor_Kind {
    SYMBOL_VISITOR,
    TYPECHECKER_VISITOR,
};

enum Visitor_State {
    VISITOR_NODE_ENTER,
    VISITOR_NODE_LEAVE,
    VISITOR_NODE_BEFORE_CHILD,
    VISITOR_NODE_AFTER_CHILD,
};

struct Symbol_Visitor {
    struct Context *context;

    u32 function_count;
    u32 function_size;

    ARRAY(struct Symbol_Table *) functions;
};

struct TypeChecker_Visitor {
    struct Context *context;
};

struct Symbol_Table {
    struct Declaration_Function *fn;
    struct HashTable symbol_table;
};

struct Visitor {
    enum Visitor_Kind kind;
    enum Visitor_State state;
    void (*pre_visit)(struct Visitor *visitor, struct Node *node);
    void (*mid_visit)(struct Visitor *visitor, struct Node *node);
    void (*post_visit)(struct Visitor *visitor, struct Node *node);
    union {
        struct Symbol_Visitor symbol_visitor;
        struct TypeChecker_Visitor typechecker_visitor;
    } contents;
};

void visit( struct Node *node, struct Visitor *visitor );
