#pragma once

#include "context.h"
#include "defines.h"
#include "include/library.h"

struct User_Type {
    Str identifier;
    u32 field_count;
    ARRAY(uint32_t) size;
    ARRAY(Str) fields;
};

struct Result_User_Type get_type(struct Context *context, u32 descriptor );

struct Result_uint32 get_field_number( struct Context *context, u32 descriptor, Str field);

u32 insert_type( struct Context *context, struct User_Type user_type );
