#include <assert.h>
#include <stdlib.h>
#include "symbols.h"
#include "../frontend/token.h"
#include "visitor.h"
#include "../error.h"
#include "../ds/hashtable.h"
#include "../types.h"
#include "../include/library.h"

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

            print("Found a struct\n");
            struct Declaration_Struct struct_declaration = root->contents.struct_declaration;
            print( "{str} :: \\{", struct_declaration.struct_name );
            struct Node *current = struct_declaration.fields;
            struct_declaration.count = 0;

            ArrayList fields = arraylist_new(sizeof(struct User_Field));

            while (current != NULL) {
                struct User_Field field;
                if (current->node_type == NODE_PARAMETER_LIST) {
                    struct Parameter_List *list = (struct Parameter_List *) &current->contents.parameter_list;

                    field.name = list->parameter->contents.variable_declaration.variable_name;
                    field.type = list->parameter->contents.variable_declaration.variable_type;
                    field.size = get_size_for(list->parameter->contents.variable_declaration.variable_type);

                    current = list->next;
                } else { // if (current->node_type == NODE_VARIABLE_DECLARATION) {
                    field.name = current->contents.variable_declaration.variable_name;
                    field.type = current->contents.variable_declaration.variable_type;
                    field.size = get_size_for(current->contents.variable_declaration.variable_type);

                    current = NULL;
                }
                arraylist_push(&fields, &field);
                struct_declaration.count++;
            }
//            print("\n}\nFields: {u32}\n", struct_declaration.count);
            struct User_Type type = {
                .field_count = struct_declaration.count,
                .fields = malloc(sizeof(struct User_Field) * struct_declaration.count),
                .identifier = struct_declaration.struct_name
            };
            u32 i = 0;
            forward_it(fields, struct User_Field) {
                print("\n\t{str}: {str} -> {u32}", it->name, it->type, it->size);
                type.fields[i++] = *it;
            }
            print("\n}\n");
            insert_type(visitor->context, type);

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
                emit_error( visitor->context, .error_string = str_from_cstr("Tried to redeclare a symbol\n"), .node = root);
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

u32 get_size_for( Str type ) {
    if ( str_eq( type, str_from_cstr("i32") ) == true ) {
        return 4;
    } else if ( str_eq( type, str_from_cstr("i64") ) == true ) {
        return 8;
    }
    return 0;
}

void insert_function( struct Symbol_Visitor *visitor, struct Declaration_Function *fn ) {
    if (visitor->function_count == visitor->function_size) {
        // Increase the size of the table
        visitor->functions = realloc( visitor->functions, visitor->function_size * 2 * sizeof(struct SymbolTable *) );

        if (visitor->functions == NULL) {
            emit_allocation_error(str_from_cstr("Symbol Table"));
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

struct Symbol_Table *get_symbol_table( struct Symbol_Visitor *visitor, Str function_name ) {
    for (uint64_t i = 0; i < visitor->function_count; ++i) {
        if ( str_eq( visitor->functions[i]->fn->function_name, function_name ) != 0 ) {
            return visitor->functions[i];
        }
    }
    return NULL;
}
