#ifndef STRING_H
#define STRING_H

struct String {
    unsigned int length;
    char *str;
};

#define String(...) &(struct String){ __VA_ARGS__ }

void print_string( struct String *str );
void print_int( int num );
#endif
