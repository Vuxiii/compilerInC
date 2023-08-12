#include "string.h"
#include <unistd.h>
void print_string( struct String *str ) {
    write(STDOUT_FILENO, str->str, str->length);  
}
void print_int( int num ) {
    char s[10] = {'0','0', '0', '0', '0', '0', '0', '0', '0', '0'};
    int len = 0;
    while (num != 0) {
        char c = num % 10;
        num = num / 10;
        len++;
        s[10-len] += c;
    }
    write(STDOUT_FILENO, &s[10-len], len);
}
