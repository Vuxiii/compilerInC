#include "visitor.h"
#include "symbols.h"
#include "token.h"

void visit( struct Node *node, struct Visitor *visitor ) {
    visitor->state = VISITOR_NODE_ENTER;
    switch (visitor->kind) {
        case SYMBOL_VISITOR: {

            collect_symbols( visitor, node );

        } break;
    }
    if (node) {
    switch (node->node_type) {
        case NODE_COMPOUND_STATEMENT: {
            visit( node->contents.compound_statement.left, visitor );
            visit( node->contents.compound_statement.right, visitor );
        } break;
        case NODE_STRUCT_DECLARATION: {
            struct Declaration_Struct *strct = &node->contents.struct_declaration;
            // Check for -1 in count. If not set
            for (long long i = 0; i < strct->count; ++i) {
                visit( &strct->fields[i], visitor );
            }
        } break;

        case NODE_VARIABLE_DECLARATION: {} break; // Do nothing
        case NODE_ARRAY_DECLARATION: {} break;    // Do nothing
        case NODE_TYPE_DECLARATION: {} break;     // TODO
        case NODE_FN_DECLARATION: {
            visit( node->contents.function_declaration.parameters, visitor );
            visit( node->contents.function_declaration.body, visitor );
        } break;
        case NODE_BINARY_OPERATION: {
            visit( node->contents.binary_operation.left, visitor );
            visit( node->contents.binary_operation.right, visitor );
        } break;
        case NODE_FN_CALL: {
            visit( node->contents.function_call.lhs, visitor );
            visit( node->contents.function_call.arguments, visitor );
        } break;
        case NODE_SYMBOL: {} break; // Do nothing
        case NODE_FIELD_ACCESS: {
            visit( node->contents.field_access.lhs, visitor );
            visit( node->contents.field_access.rhs, visitor );
        } break;
        case NODE_ARRAY_ACCESS: {
            visit( node->contents.array_access.index, visitor );
        } break;
        case NODE_ASSIGNMENT: {
            visit( node->contents.assignment.lhs, visitor );
            visit( node->contents.assignment.rhs, visitor );
        } break;
        case NODE_ADDRESS_OF: {
            visit( node->contents.address_of.expression, visitor );
        } break;
        case NODE_DEREF: {
            visit( node->contents.deref.expression, visitor );
        } break;
        case NODE_PARAMETER_LIST: {
            visit( node->contents.parameter_list.parameter, visitor );
            visit( node->contents.parameter_list.next, visitor );
        } break;
        case NODE_ARGUMENT_LIST: {
            visit( node->contents.argument_list.argument, visitor );
            visit( node->contents.argument_list.next, visitor );
        } break;
        case NODE_FOR: {
            visit( node->contents.for_loop.init, visitor );
            visit( node->contents.for_loop.guard, visitor );
            visit( node->contents.for_loop.advance, visitor );
            visit( node->contents.for_loop.body, visitor );
        } break;
        case NODE_EACH: {
            visit( node->contents.each_loop.container, visitor );
            visit( node->contents.each_loop.body, visitor );
        } break;
        case NODE_SCOPE: {
            visit( node->contents.scope.expression, visitor );    
        }
        default: {} break;
    }
    }
    visitor->state = VISITOR_NODE_LEAVE;
    // switch (visitor->kind) {
    //     case SYMBOL_VISITOR: {

    //         collect_symbols( visitor->contents.symbol_visitor.context, node );

    //     } break;
    // }

}
