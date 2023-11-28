#pragma once
struct String {
    unsigned long length;
    char *str;
};

#define String(...) (struct String){ __VA_ARGS__ }

// Returns true iff both strings contain the same characters in order
int cmp_strings( struct String *left, struct String *right );
void print_string( struct String str );
void print_int( int num );
