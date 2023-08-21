#pragma once
struct String {
    unsigned long length;
    char *str;
};

#define String(...) &(struct String){ __VA_ARGS__ }

void print_string( struct String *str );
void print_int( int num );
