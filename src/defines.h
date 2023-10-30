//
// Created by William Juhl on 05/09/2023.
//
#pragma once

#define ARRAY(type) type *
enum RESULT_STATE {
    STATE_OK,
    STATE_FAIL
};

#define DECL_RESULT(typename, type) \
    struct typename { \
        enum RESULT_STATE result; \
        type value; \
    };                              \

#define uint64Result(...) (struct UInt64Result){ __VA_ARGS__ }
#define Result_uint32(...) (struct Result_uint32){ __VA_ARGS__ }

#define Result_User_Type(...) (struct Result_User_Type){ __VA_ARGS__ }

DECL_RESULT(UInt64Result, uint64_t)
DECL_RESULT(Result_uint32, uint32_t)
DECL_RESULT(Result_User_Type, struct User_Type *)

#define MATCH(expr, decl) \
    decl; \
    switch (expr)         \

