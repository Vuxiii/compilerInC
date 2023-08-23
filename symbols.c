#include "symbols.h"
#include "token.h"

void collect_symbols(struct Visitor *visitor, struct Node *root) {

    switch (root->node_type) {
        case NODE_FN_DECLARATION: {

        } break;
        case NODE_TYPE_DECLARATION: {

        } break;
        case NODE_ARRAY_DECLARATION: {

        } break;
        case NODE_STRUCT_DECLARATION: {

        } break;
        case NODE_VARIABLE_DECLARATION: {

        } break;

        default: {
            // Do nothing. We don't care about this.
        } break;
    }
}
