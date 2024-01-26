#include "types.h"
#include "error.h"
#include "include/library.h"

uint32_t insert_type( struct Context *context, struct User_Type user_type ) {
    // Check size
    if (context->type_count == context->type_size) {
        context->user_types = realloc( context->user_types, sizeof(struct User_Type) * context->type_size * 2 );
        if ( context->user_types == NULL ) {
            // Error
            emit_error( context, .error_string = str_from_cstr("Unable to allocate memory for user types\n"));
        }
        context->type_size *= 2;
    }
    context->user_types[context->type_count] = user_type;
    return context->type_count++;
}

struct Result_User_Type get_type( struct Context *context, u32 descriptor ) {
    if (descriptor > context->type_count) {
        return Result_User_Type( .result = STATE_FAIL );
    }
    return Result_User_Type (.result = STATE_OK, .value = &context->user_types[descriptor] );
}

struct Result_uint32 get_field_number( struct Context *context, u32 descriptor, Str field ) {
    MATCH( type.result, struct Result_User_Type type = get_type(context, descriptor )) {
        case STATE_FAIL: {
            return Result_uint32(.result = STATE_FAIL );
        } break;
        case STATE_OK: {
            for ( u32 i = 0; i < type.value->field_count; ++i ) {
                if (str_eq(field, type.value->fields[i].name)) {
                    return Result_uint32(.result = STATE_OK, .value = i );
                }
            }
            return Result_uint32(.result = STATE_FAIL );
        } break;
    }
}
