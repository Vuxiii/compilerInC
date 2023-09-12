#include <stdlib.h>
#include "symbols.h"
#include "token.h"
#include "visitor.h"
#include "ir.h"

void collect_symbols(struct Visitor *_visitor, struct Node *root) {
    struct Symbol_Visitor *visitor = &_visitor->contents.symbol_visitor;
    if (root == NULL) return;
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

        } break;
        case NODE_PARAMETER_LIST: {
            // Each parameter is implemented as a Variable Declaration.
        } break;
        case NODE_VARIABLE_DECLARATION: {
            struct Declaration_Variable *decl = &root->contents.variable_declaration;

            // Check if we already have this string
            struct Symbol_Table *table = current_symbol_table( visitor );

            MATCH(res.result, struct UInt64Result res = lookup_symbol( table, decl->variable_name ) ) {
                case STATE_FAIL:
                    // It was not in the table. Therefore, we want to insert it
                    insert_symbol( table, *decl->variable_name );
                    // At this point we can also do type assigning.
                
                    return;
                case STATE_OK: return; // It was already inserted
            }
        } break;
        default: {
            // Do nothing. We don't care about this.
        } break;
    }
}

void insert_function( struct Symbol_Visitor *visitor, struct Declaration_Function *fn ) {
    if (visitor->symbol_table_count == visitor->symbol_table_size) {
        // Increase the size of the table
        visitor->symbol_table = realloc( visitor->symbol_table, visitor->symbol_table_size * 2 );
        if (visitor->symbol_table == NULL) {
            print_string( String( .str = "Not enough memory to increase the size of the function symbol tables\n", .length = 68));
            exit(2);
        }
        visitor->symbol_table_size *= 2;
    }
    // Add a new symbol table, and add it.
    visitor->table_names[visitor->symbol_table_count++] = *fn->function_name;
}

struct Symbol_Table *current_symbol_table( struct Symbol_Visitor *visitor ) {
    return &visitor->symbol_table[visitor->symbol_table_count-1];
}


void insert_symbol( struct Symbol_Table *table, struct String name ) {
    if (table->count == table->size) {
        table->symbols = realloc(table->symbols, sizeof(struct String) * table->size * 2);
        if (table->symbols == NULL) {
            print_string( String( .str = "Not enough memory to increase the size of the symbol table\n", .length = 58));
            exit(2);
        }
        table->size *= 2;
    }
    table->symbols[table->count++] = name;

}

struct UInt64Result lookup_symbol( struct Symbol_Table *table, struct String *symbol ) {
    for ( uint64_t i = 0; i < table->count; ++i ) {
        struct String *right = &table->symbols[i];
        if ( cmp_strings(symbol, right) == 1 )
            return uint64Result( .result = STATE_OK, .value = 1 );
    }
    return uint64Result( .result = STATE_FAIL );
}
