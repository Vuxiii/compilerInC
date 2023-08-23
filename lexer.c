#include "lexer.h"
#include "token.h"

#include <stdio.h>
#include <stdlib.h>


void next_token( struct Context *context ) {
    context->current_token_index = context->peek_token_index;
    context->peek_token_index = (context->peek_token_index + 1) % TOKEN_QUEUE_SIZE;
    
    // Delete spaces
    while ( *context->current_position <= WHITE_SPACE ) {
        if (*context->current_position == '\n')
            context->current_line++;
        context->current_position++;
    }
    char *p = context->current_position;
    // Check for Keywords
    switch (p[0]) {
        case '"': {
            char *left  = p+1;
            char *right = p+1;

            while (*right != '"') {
                if (*right == '\\')
                    right++;
                right++;
            }
            right++;
            peek_token(context)->left  = p      - context->file_start;
            peek_token(context)->right = right  - context->file_start;
            peek_token(context)->line  = context->current_line;
            peek_token(context)->token_type = TOKEN_STRING;
            
            context->current_position = right;
            
            peek_token(context)->data.str = get_string_from(left, right);
            return;
        } case '(': {

            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
            peek_token(context)->token_type = TOKEN_LPAREN;
            context->current_position = p + 1;
            return;
        } case ')': {

            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
            peek_token(context)->token_type = TOKEN_RPAREN;
            context->current_position = p + 1;            
            return;

        } case '[': {

            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
            peek_token(context)->token_type = TOKEN_LBRACKET;
            context->current_position = p + 1;            
            return;

        } case ']': {
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
 
            peek_token(context)->token_type = TOKEN_RBRACKET;
            context->current_position = p + 1;
            return;
        } case '{': {
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
 
            peek_token(context)->token_type = TOKEN_LCURLY;
            context->current_position = p + 1;        
            return;    
        } case '}': {
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
 
            peek_token(context)->token_type = TOKEN_RCURLY;
            context->current_position = p + 1;     
            return;       
        } case ';': {
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
 
            peek_token(context)->token_type = TOKEN_SEMICOLON;
            context->current_position = p + 1;   
            return;         
        } case ':': {
            if (p[1] == ':') {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 2;
                peek_token(context)->line = context->current_line;
    
                peek_token(context)->token_type = TOKEN_DOUBLE_COLON;
                context->current_position = p + 2;    
                return;      
            } else {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 1;
                peek_token(context)->line = context->current_line;
    
                peek_token(context)->token_type = TOKEN_COLON;
                context->current_position = p + 1;    
                return;        
            }
            
        } case ',': {
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
 
            peek_token(context)->token_type = TOKEN_COMMA;
            context->current_position = p + 1;            
            return;
        } case '.': {
            if (p[1] >= '0' && p[1] <= '9') {
                // It is a number.
                break;
            }
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
            peek_token(context)->token_type = TOKEN_DOT;
            context->current_position = p + 1;        
            return;    
        } case '+': {
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
 
            peek_token(context)->token_type = TOKEN_PLUS;
            context->current_position = p + 1;            
            return;
        } case '-': {
            if (p[1] >= '0' || p[1] <= '9') {
                // It is a number.
                break;
            }
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
 
            peek_token(context)->token_type = TOKEN_MINUS;
            context->current_position = p + 1;         
            return;   
        } case '*': {
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
 
            peek_token(context)->token_type = TOKEN_TIMES;
            context->current_position = p + 1;         
            return;   
        } case '/': {
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
 
            peek_token(context)->token_type = TOKEN_DIV;
            context->current_position = p + 1;          
            return;  
        } case '%': {
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
 
            peek_token(context)->token_type = TOKEN_MODULO;
            context->current_position = p + 1;      
            return;      
        } case '$': {
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 1;
            peek_token(context)->line = context->current_line;
 
            peek_token(context)->token_type = TOKEN_EOP;
            context->current_position = p + 1;
            return;      
        } case '&': {
            if (p[1] == '&') {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 2;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_DOUBLE_AND;
                context->current_position = p + 2;
                return;
            } else {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 1;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_AND;
                context->current_position = p + 1;
                return; 
            }
        }  case '|': {
            if (p[1] == '|') {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 2;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_DOUBLE_OR;
                context->current_position = p + 2;
                return;
            } else {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 1;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_OR;
                context->current_position = p + 1;
                return; 
            }
        } case '=': {
            if (p[1] == '=') {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 2;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_DOUBLE_EQ;
                context->current_position = p + 2;
                return;
            } else {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 1;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_EQ;
                context->current_position = p + 1;
                return; 
            }
        } case '!': {
            if (p[1] == '=') {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 2;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_NOT_EQ;
                context->current_position = p + 2;
                return;
            } else {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 1;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_BANG;
                context->current_position = p + 1;
                return; 
            }
        } case '<': {
            if (p[1] == '=') {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 2;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_LESS_EQ;
                context->current_position = p + 2;
                return;
            } else {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 1;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_LESS;
                context->current_position = p + 1;
                return; 
            }
        } case '>': {
            if (p[1] == '=') {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 2;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_GREATER_EQ;
                context->current_position = p + 2;
                return;
            } else {
                peek_token(context)->left = p - context->file_start;
                peek_token(context)->right = peek_token(context)->left + 1;
                peek_token(context)->line = context->current_line;
                peek_token(context)->token_type = TOKEN_GREATER;
                context->current_position = p + 1;
                return; 
            }
        } 
    }
    // For length 2
    if (p[0] == 'f' && p[1] == 'n') {
        if (p[2] <= WHITE_SPACE) {
            
            // It is an TOKEN_FN
            peek_token(context)->left = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 2;
            peek_token(context)->line = context->current_line;

            peek_token(context)->token_type = TOKEN_FN;
            context->current_position = p + 2;
            return;
        }
    }

    // For length 3
    if (p[0] == 'l' && p[1] == 'e' && p[2] == 't') {
        if (p[3] <= WHITE_SPACE || is_valid_identifier_char(p[3]) == 0) { 
            // It is a TOKEN_LET
            peek_token(context)->left  = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 3;
            peek_token(context)->line  = context->current_line;

            peek_token(context)->token_type = TOKEN_LET;
            context->current_position = p + 3;
            return;
        }
    } else if (p[0] == 'f' && p[1] == 'o' && p[2] == 'r') {
        if (p[3] <= WHITE_SPACE || is_valid_identifier_char(p[3]) == 0) {
            // It is a TOKEN_FOR
            peek_token(context)->left  = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 3;
            peek_token(context)->line  = context->current_line;

            peek_token(context)->token_type = TOKEN_FOR;
            context->current_position = p + 3;
            return;
        }
    }

    // For length 4
    if (p[0] == 'e' && p[1] == 'a' && p[2] == 'c' && p[3] == 'h') {
        if (p[4] <= WHITE_SPACE || is_valid_identifier_char(p[4]) == 0) {
            // It is a TOKEN_EACH
            peek_token(context)->left  = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 4;
            peek_token(context)->line  = context->current_line;

            peek_token(context)->token_type = TOKEN_EACH;
            context->current_position = p + 4;
            return;
        }
    } else if (p[0] == 't' && p[1] == 'r' && p[2] == 'u' && p[3] == 'e') {
        if (p[4] <= WHITE_SPACE || is_valid_identifier_char(p[4]) == 0) {
            // It is a TOKEN_EACH
            peek_token(context)->left  = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 4;
            peek_token(context)->line  = context->current_line;

            peek_token(context)->token_type = TOKEN_TRUE;
            context->current_position = p + 4;
            return;
        }
    } else if (p[0] == 't' && p[1] == 'y' && p[2] == 'p' && p[3] == 'e') {
        if (p[4] <= WHITE_SPACE || is_valid_identifier_char(p[4]) == 0) {
            // It is a TOKEN_EACH
            peek_token(context)->left  = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 4;
            peek_token(context)->line  = context->current_line;

            peek_token(context)->token_type = TOKEN_TYPE;
            context->current_position = p + 4;
            return;
        }
    }

    // For length 5
    if (p[0] == 'w' && p[1] == 'h' && p[2] == 'i' && p[3] == 'l' && p[4] == 'e') {
        if (p[5] <= WHITE_SPACE || is_valid_identifier_char(p[5]) == 0) {
            // It is a TOKEN_WHILE
            peek_token(context)->left  = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 5;
            peek_token(context)->line  = context->current_line;

            peek_token(context)->token_type = TOKEN_WHILE;
            context->current_position = p + 5;
            return;
        }
    } else if (p[0] == 'f' && p[1] == 'a' && p[2] == 'l' && p[3] == 's' && p[4] == 'e') {
        if (p[5] <= WHITE_SPACE || is_valid_identifier_char(p[5]) == 0) {
            // It is a TOKEN_WHILE
            peek_token(context)->left  = p - context->file_start;
            peek_token(context)->right = peek_token(context)->left + 5;
            peek_token(context)->line  = context->current_line;

            peek_token(context)->token_type = TOKEN_FALSE;
            context->current_position = p + 5;
            return;
        }
    }

    // Maybe make a goto label here. I know it's bad... But it will probably be faster. I need to check if it is before I do it.
    // Check for number
    if (*p == '-' || (*p >= '0' && *p <= '9')) { 
        char sign = 1;
        if (*p == '-') {
            sign = -1;
            p++;
        }

        char *left = p;
        char *right = p;
        
        char is_float = 0;

        while ( *right == '.' || *right == '_' || (*right >= '0' && *right <= '9') ) {
            if (*right == '.') {
                is_float = 1;
            }
            right++;
        }
        context->current_position = right;
        
        peek_token(context)->left = left - context->file_start;
        peek_token(context)->right = right - context->file_start;
        peek_token(context)->line = context->current_line;

        if (is_float) {
            //TODO! IMPLEMENT ME
            
        } else {
            // Convert string number to decimal
            long long num = 0;
            int  i   = 1;
            while (left != right) {
                if (*right == '_') {
                    right--;
                    continue;
                }
                int c = *(right-1) - '0';
                num += c * i;
                i *= 10;
                right--;
            }
            num *= sign;
            
            peek_token(context)->data.inum  = num;
            peek_token(context)->token_type = TOKEN_NUMBER_D;

        }
        
        return;
    }


    // Check for identifier
    char *left = p;
    char *right = p;
    while (is_valid_identifier_char(*right))
        right++;

    peek_token(context)->data.str  = get_string_from(left, right);
    peek_token(context)->token_type = TOKEN_IDENTIFIER;

    peek_token(context)->left = left - context->file_start;
    peek_token(context)->right = right - context->file_start;
    peek_token(context)->line = context->current_line;

    context->current_position = right;   
    return;
}

struct Token *current_token(struct Context *context) {
    return &context->TOKEN_QUEUE[context->current_token_index];
}

struct Token *peek_token(struct Context *context) {
    return &context->TOKEN_QUEUE[context->peek_token_index];
}

void print_tokens(struct Context *context) {
    next_token(context);
    while (peek_token(context)->token_type != TOKEN_EOP) {
        printf("Current Token ID [%d]\n", peek_token(context)->token_type); 
        next_token(context);
    }
}
struct String *get_string_from( char *left, char *right) {
    // [1] Compute the hash for the string
    // [2] Check if the string has already been made
    // [3] If yes - Return that String
    // [4] If no  - Make a new String and return that.
    
    // stupid for now
    unsigned int len = right - left;
    char *p = malloc( sizeof(char) * len + sizeof(struct String) );
    char *cpy = sizeof(struct String) + p;
    while (left != right)
        *cpy++ = *left++;
    
    struct String *str = (struct String *)p;
    str->str = sizeof(struct String) + p;
    str->length = len;
    return str;
}

int is_valid_identifier_char(char c) {
    if (c == '_') return 1;
    if (c >= '0' && c <= '9') return 1;
    // Trick to remove the 6th bit
    // We now only have  to compare twice in the range [65, 90]
    c &= 223;
    return c >= 65 && c <= 90;
}
