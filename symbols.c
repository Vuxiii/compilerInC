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

        } break;
        case NODE_TYPE_DECLARATION: {

        } break;
        case NODE_ARRAY_DECLARATION: {

        } break;
        case NODE_STRUCT_DECLARATION: {

        } break;
        case NODE_VARIABLE_DECLARATION: {
            struct Declaration_Variable *decl = &root->contents.variable_declaration;

            // Check if we already have this string
            struct Symbol_Table *table = &visitor->symbol_table[visitor->current_block];

            MATCH(res.result, struct UInt64Result res = lookup_symbol( table, decl->variable_name ) ) {
                case STATE_FAIL:
                    // It was not in the table. Therefore, we want to insert it
                    if (table->count == table->size) {
                        table->symbols = realloc(table->symbols, sizeof(struct String) * table->size * 2);
                        if (table->symbols == NULL) {
                            print_string( String( .str = "Not enough memory to increase the size of the symbol table\n", .length = 58));
                            exit(2);
                        }
                        table->size *= 2;
                    }
                    table->symbols[++table->count] = *decl->variable_name;
                case STATE_OK: return;
            }
        } break;
        default: {
            // Do nothing. We don't care about this.
        } break;
    }
}

struct UInt64Result lookup_symbol( struct Symbol_Table *table, struct String *symbol ) {
    for ( uint64_t i = 0; i < table->count; ++i ) {
        struct String *right = &table->symbols[i];
        if ( cmp_strings(symbol, right) == 1 )
            return uint64Result( .result = STATE_OK, .value = 1 );
    }
    return uint64Result( .result = STATE_FAIL );
}
