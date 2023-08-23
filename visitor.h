#pragma once

#include "context.h"
#include "token.h"

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
    
};

struct Visitor {
    enum Visitor_Kind kind;
    enum Visitor_State state;
    union {
        struct Symbol_Visitor symbol_visitor;
    } contents;
};

void visit( struct Node *node, struct Visitor *visitor );
