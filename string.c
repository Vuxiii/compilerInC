#include "string.h"
#include <unistd.h>
void print_string( struct String *str ) {
    write(STDOUT_FILENO, str->str, str->length);  
}
void print_int( int num ) {
    char s[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
    int len = 0;
    do {
        char c = num % 10;
        num = num / 10;
        len++;
        s[10-len] += c;
    } while (num != 0);
    write(STDOUT_FILENO, &s[10-len], len);
}
int cmp_strings( struct String *left, struct String *right ) {
    if (left->length != right->length) return 0;
    for (unsigned long i = 0; i < left->length; ++i) {
        if (left->str[i] != right->str[i])
            return 0;
    }
    return 1;
}
