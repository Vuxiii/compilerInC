#pragma once

#include <stdint.h>
#include "context.h"
#include "defines.h"
#include "include/library.h"

struct User_Type {
    Str identifier;
    uint32_t field_count;
    ARRAY(uint32_t) size;
    ARRAY(Str) fields;
};

struct Result_User_Type get_type(struct Context *context, uint32_t descriptor );

struct Result_uint32 get_field_number( struct Context *context, uint32_t descriptor, Str field);

uint32_t insert_type( struct Context *context, struct User_Type user_type );
