#pragma once

#include <stdint.h>
#include "context.h"
#include "ds/string.h"
#include "defines.h"

struct User_Type {
    struct String identifier;
    uint32_t field_count;
    ARRAY(uint32_t) size;
    ARRAY(struct String) fields;
};

struct Result_User_Type get_type(struct Context *context, uint32_t descriptor );

struct Result_uint32 get_field_number( struct Context *context, uint32_t descriptor, struct String *field);

uint32_t insert_type( struct Context *context, struct User_Type user_type );
