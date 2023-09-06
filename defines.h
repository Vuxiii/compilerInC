//
// Created by William Juhl on 05/09/2023.
//
#pragma once

#define ARRAY(type) type *

#define DECL_RESULT(typename, type) \
    struct typename { \
        enum { \
            STATE_OK, \
            STATE_FAIL \
        } result; \
        type value; \
    };             \


#define uint64Result(...) (struct UInt64Result){ __VA_ARGS__ }
DECL_RESULT(UInt64Result, uint64_t)


#define MATCH(expr, decl) \
    decl; \
    switch (expr)         \

