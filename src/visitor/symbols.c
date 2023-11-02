#include <assert.h>
#include <stdlib.h>
#include "symbols.h"
#include "../token.h"
#include "visitor.h"
#include "../ir.h"
#include "../error.h"
#include "../ds/hashtable.h"

void collect_symbols(struct Visitor *_visitor, struct Node *root) {
    if (root == NULL) return;

    struct Symbol_Visitor *visitor = &_visitor->contents.symbol_visitor;
    switch (root->node_type) {
        case NODE_FN_DECLARATION: {
            // Possibly check if it already has been declared...
            insert_function( visitor, &root->contents.function_declaration );
        } break;
        case NODE_TYPE_DECLARATION: {

        } break;
        case NODE_ARRAY_DECLARATION: {

        } break;
        case NODE_STRUCT_DECLARATION: {
            // Here we want to ensure correct offset placement for each individual field in the struct.

        } break;
        case NODE_PARAMETER_LIST: {
            // Each parameter is implemented as a Variable Declaration.
        } break;
        case NODE_VARIABLE_DECLARATION: {
            struct Declaration_Variable *decl = &root->contents.variable_declaration;

            // Check if we already have this string
            struct Symbol_Table *table = current_symbol_table( visitor );
            
            if ( ht_contains(&table->symbol_table, decl->variable_name) == 1 ) {
                // It was already inserted
                // This is an error for now. We can maybe do some shadowing later on if that is cool.
                emit_error( visitor->context, .error_string = String(
                        .str = "Tried to redeclare a symbol\n",
                        .length = 28
                        ), .node = root);
                return;
            }

            // It was not in the table. Therefore, we want to insert it
            ht_insert( &table->symbol_table, decl->variable_name, NULL );
            // At this point we can also do type assigning.

        } break;
        default: {
            // Do nothing. We don't care about this.
        } break;
    }
}

void insert_function( struct Symbol_Visitor *visitor, struct Declaration_Function *fn ) {
    if (visitor->function_count == visitor->function_size) {
        // Increase the size of the table
        visitor->functions = realloc( visitor->functions, visitor->function_size * 2 * sizeof(struct SymbolTable *) );

        if (visitor->functions == NULL) {
            emit_allocation_error(String( .str = "Symbol Table", .length = 12 ));
        }
        visitor->function_size = visitor->function_size * 2;
    }
    // Add a new symbol table, and add it.
    visitor->functions[visitor->function_count] = malloc( sizeof(struct Symbol_Table) );
    visitor->functions[visitor->function_count]->fn = fn;
    visitor->functions[visitor->function_count]->symbol_table = ht_construct();
    visitor->function_count++;
}

struct Symbol_Table *current_symbol_table( struct Symbol_Visitor *visitor ) {
    return visitor->functions[visitor->function_count-1];
}

struct Symbol_Table *get_symbol_table( struct Symbol_Visitor *visitor, struct String *function_name ) {
    for (uint64_t i = 0; i < visitor->function_count; ++i) {
        if ( cmp_strings( visitor->functions[i]->fn->function_name, function_name ) != 0 ) {
            return visitor->functions[i];
        }
    }
    return NULL;
}
