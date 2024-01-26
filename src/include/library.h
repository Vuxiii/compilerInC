#ifndef LIB_H
#define LIB_H
#include <printf.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h>

typedef unsigned int u32;
typedef int i32;
typedef unsigned long long u64;
typedef long long i64;
typedef unsigned char u8;
typedef char i8;
typedef unsigned short u16;
typedef short i16;
typedef float f32;
typedef double f64;
typedef int bool;
#define false 0
#define true 1


// ======= ArrayList LIBRARY =======

#define ARRAY_LIST_DEFAULT_CAP 10
typedef struct ArrayList {
    void *data;
    u32 len;
    u32 cap;
    const u32 elem_size;
} ArrayList;

ArrayList arraylist_new(u32 elem_size);

#define array_push(list, elem) _Generic((elem), \
    u32: arraylist_push(list, &(u32){elem}),    \
    i32: arraylist_push(list, &(i32){elem}),    \
    u64: arraylist_push(list, &(u64){elem}),    \
    i64: arraylist_push(list, &(i64){elem}),    \
    f32: arraylist_push(list, &(f32){elem}),    \
    f64: arraylist_push(list, &(f64){elem}),    \
    u8: arraylist_push(list, &(u8){elem}),      \
    i8: arraylist_push(list, &(i8){elem}),      \
    u16: arraylist_push(list, &(u16){elem}),    \
    i16: arraylist_push(list, &(i16){elem}))

void arraylist_push(ArrayList *list, void *elem);

void arraylist_remove(ArrayList *list, u32 index);

void arraylist_free(ArrayList *list);

#define arraylist_last(list, type) ((type *)list.data)[list.len - 1]
#define forward_it(list, type) for (type *it = (list).data; it != (type *)(list).data + (list).len; it++)
#define reverse_it(list, type) for (type *it = &arraylist_last(list, type); it != (type *)list.data-1; it--)
#define arraylist_at(list, index, type) ((type *)list.data)[index]
#define arraylist_sort(list, compare) qsort((list).data, (list).len, (list).elem_size, compare);


// ======= STRING LIBRARY =======

typedef struct Str {
    const char *str;
    u32 len;
} Str;

typedef struct FormatOption {
    Str format;
    Str (*printer)(va_list * args);
} FormatOption;
#define MAX_FORMAT_OPTIONS 20

void __attribute__((overloadable)) print(char *format, ...);
void __attribute__((overloadable)) print(Str format, ...);

bool str_eq(Str a, Str b);
Str str_concat(Str a, Str b);
Str str_from_cstr(char * cstr);
bool str_a_contains_b(Str a, Str b);

Str str_build_from_arraylist( ArrayList *list );

Str __attribute__((overloadable)) str_format(char * format, ...);
Str __attribute__((overloadable)) str_format(Str format, ...);

void str_register(char * format, Str (* printer)(va_list * args));

#endif
#ifdef LIBS_IMPLEMENTATION
#include <string.h>
ArrayList arraylist_new(u32 elem_size) {
    ArrayList list = {
        .len = 0,
        .elem_size = elem_size,
        .cap = ARRAY_LIST_DEFAULT_CAP,
        .data = malloc(ARRAY_LIST_DEFAULT_CAP * elem_size)
    };
    assert(list.data); // Failed to allocate memory.
    return list;
}

void arraylist_free(ArrayList * list) {
    free(list->data);
}

void arraylist_push(ArrayList * list, void * elem) {
    if (list->len == list->cap) {
        list->cap *= 2;
        list->data = realloc(list->data, list->cap * list->elem_size);
        assert(list->data); // Failed to reallocate memory.
    }
    u32 offset = list->len * list->elem_size;
    memcpy((char*)list->data + offset, elem, list->elem_size);
//    for (u32 i = 0; i < list->elem_size; i++) {
//        ((char *) list->data)[offset + i] = ((char *) elem)[i];
//    }
    list->len++;
}

void arraylist_remove(ArrayList * list, u32 index) {
    assert(index < list->len); // Index out of bounds.
    u32 offset = index * list->elem_size;
    for (u32 j = index; j < list->len; j++) {
        for (u32 i = 0; i < list->elem_size; i++) {
            ((char *) list->data)[offset + i] = ((char *) list->data)[offset + list->elem_size + i];
        }
        offset += list->elem_size;
    }

    list->len--;
}

static u32 _num_options = 0;
static FormatOption options[MAX_FORMAT_OPTIONS] = {0};

void str_register(char * format, Str (* printer)(va_list * args)) {
    assert(_num_options < MAX_FORMAT_OPTIONS); // Ensure that enough space has been allocated for the format options.
    options[_num_options].format = str_from_cstr(format);
    options[_num_options].printer = printer;
    _num_options++;
}

static Str i32_Printer(va_list * args) {
    i32 number = va_arg(*args, i32);
    u32 len = 0;
    i32 temp = number;
    if (number == 0) {
        return str_from_cstr("0");
    }
    if (temp < 0) {
        len++;
        temp = -temp;
    }
    while (temp > 0) {
        len++;
        temp /= 10;
    }
    char *str = malloc(len + 1);
    str[len] = '\0';
    temp = number;
    if (temp < 0) {
        str[0] = '-';
        temp = -temp;
    }
    for (u32 i = len - 1; i > 0; i--) {
        str[i] = (temp % 10) + '0';
        temp /= 10;
    }
    if (number >= 0) {
        str[0] = (temp % 10) + '0';
    }
    return (Str){str, len};
}

static Str u32_Printer(va_list * args) {
    u32 number = va_arg(*args, u32);
    if (number == 0) {
        char *str = malloc(2);
        str[0] = '0';
        str[1] = '\0';
        return (Str){str, 1};
    }
    u32 len = 0;

    u32 temp = number;
    while (temp > 0) {
        len++;
        temp /= 10;
    }
    char *str = malloc(len + 1);
    str[len+1] = '\0';
    temp = number;
    for (i32 i = len - 1; i >= 0; i--) {
        str[i] = (temp % 10) + '0';
        temp /= 10;
    }
    return (Str){str, len};
}

static Str i64_Printer(va_list * args) {
    i64 number = va_arg(*args, i64);
    u32 len = 0;
    i64 temp = number;
    if (number == 0) {
        return str_from_cstr("0");
    }
    if (temp < 0) {
        len++;
        temp = -temp;
    }
    while (temp > 0) {
        len++;
        temp /= 10;
    }
    char *str = malloc(len + 1);
    str[len] = '\0';
    temp = number;
    if (temp < 0) {
        str[0] = '-';
        temp = -temp;
    }
    for (u32 i = len - 1; i > 0; i--) {
        str[i] = (temp % 10) + '0';
        temp /= 10;
    }
    if (number >= 0) {
        str[0] = (temp % 10) + '0';
    }
    return (Str){str, len};
}

static Str u64_Printer(va_list * args) {
    u64 number = va_arg(*args, u64);
    if (number == 0) {
        char *str = malloc(2);
        str[0] = '0';
        str[1] = '\0';
        return (Str){str, 1};
    }
    u32 len = 0;

    u64 temp = number;
    while (temp > 0) {
        len++;
        temp /= 10;
    }
    char *str = malloc(len + 1);
    str[len+1] = '\0';
    temp = number;
    for (i32 i = len - 1; i >= 0; i--) {
        str[i] = (temp % 10) + '0';
        temp /= 10;
    }
    return (Str){str, len};
}

static Str f32_Printer(va_list * args) {
    f64 number = va_arg(*args, f64);

    i32 int_part = (i32)number;
    f32 frac_part = (number - int_part);
    i32 pad_with_zero = -1;
    u32 frac_len = 0;
    while (frac_part != (i32)frac_part) {
        if ((i32)frac_part == 0) {
            pad_with_zero++;
        } else {
            ++frac_len;
        }
        frac_part *= 10;
    }
    i32 frac_part_i32 = (i32)frac_part;

    Str int_str;
    {
        u32 len = 0;
        i64 temp = int_part;
        if (temp == 0) {
            int_str = str_from_cstr("0");
        } else {
            if (temp < 0) {
                len++;
                temp = -temp;
            }
            while (temp > 0) {
                len++;
                temp /= 10;
            }
            char *str = malloc(len + 1);
            str[len] = '\0';
            temp = int_part;
            if (temp < 0) {
                str[0] = '-';
                temp = -temp;
            }
            for (u32 i = len - 1; i > 0; i--) {
                str[i] = (temp % 10) + '0';
                temp /= 10;
            }
            if (temp >= 0) {
                str[0] = (temp % 10) + '0';
            }
            int_str = (Str) {str, len};
        }
    }
    Str frac_str;
    {
        u32 len = 1 + frac_len;
        i64 temp = frac_part_i32;
        if (number == 0) {
            frac_str = str_from_cstr("0");
        } else {
            if (temp < 0) {
                temp = -temp;
            }
            len += pad_with_zero;
            char *str = malloc(len + 1);
            str[len] = '\0';
            temp = frac_part_i32;
            if (temp < 0) {
                temp = -temp;
            }
            for (i32 i = len - 1; i > 0; i--) {
                str[i] = (temp % 10) + '0';
                temp /= 10;
            }
            if (temp >= 0) {
                str[0] = (temp % 10) + '0';
            }
            for (i32 i = 0; i < pad_with_zero; i++) {
                str[i] = '0';
            }
            frac_str = (Str) {str, len};
        }
    }

    const Str dot_str = str_from_cstr(".");
    const Str out = str_concat(int_str, str_concat(dot_str, frac_str));
    return out;
}

static Str f64_Printer(va_list * args) {
    f64 number = va_arg(*args, f64);

    i64 int_part = (i64)number;
    f64 frac_part = (number - int_part);
    i32 pad_with_zero = -1;
    u32 frac_len = 0;
    while (frac_part != (i64)frac_part) {
        if ((i64)frac_part == 0) {
            pad_with_zero++;
        } else {
            ++frac_len;
        }
        frac_part *= 10;
    }
    i64 frac_part_i32 = (i64)frac_part;

    Str int_str;
    {
        u32 len = 0;
        i64 temp = int_part;
        if (temp == 0) {
            int_str = str_from_cstr("0");
        } else {
            if (temp < 0) {
                len++;
                temp = -temp;
            }
            while (temp > 0) {
                len++;
                temp /= 10;
            }
            char *str = malloc(len + 1);
            str[len] = '\0';
            temp = int_part;
            if (temp < 0) {
                str[0] = '-';
                temp = -temp;
            }
            for (u32 i = len - 1; i > 0; i--) {
                str[i] = (temp % 10) + '0';
                temp /= 10;
            }
            if (temp >= 0) {
                str[0] = (temp % 10) + '0';
            }
            int_str = (Str) {str, len};
        }
    }
    Str frac_str;
    {
        u32 len = 1 + frac_len;
        i64 temp = frac_part_i32;
        if (number == 0) {
            frac_str = str_from_cstr("0");
        } else {
            if (temp < 0) {
                temp = -temp;
            }
            len += pad_with_zero;
            char *str = malloc(len + 1);
            str[len] = '\0';
            temp = frac_part_i32;
            if (temp < 0) {
                temp = -temp;
            }
            for (u32 i = len - 1; i > 0; i--) {
                str[i] = (temp % 10) + '0';
                temp /= 10;
            }
            if (temp >= 0) {
                str[0] = (temp % 10) + '0';
            }
            for (i32 i = 0; i < pad_with_zero; i++) {
                str[i] = '0';
            }
            frac_str = (Str) {str, len};
        }
    }

    const Str dot_str = str_from_cstr(".");
    const Str out = str_concat(int_str, str_concat(dot_str, frac_str));
    return out;
}

static Str bool_Printer(va_list * args) {
    bool i = va_arg(*args, bool);
    if (i) {
        return str_from_cstr("true");
    } else {
        return str_from_cstr("false");
    }
}

static Str str_Printer(va_list * args) {
    Str str = va_arg(*args, Str);
    return str;
}

//#if defined(__clang__)
static void init_printers(void) { //__attribute__((constructor)) {
    str_register("{i32}", i32_Printer);
    str_register("{u32}", u32_Printer);
    str_register("{i64}", i64_Printer);
    str_register("{u64}", u64_Printer);
    str_register("{f32}", f32_Printer);
    str_register("{f64}", f64_Printer);
    str_register("{bool}", bool_Printer);
    str_register("{str}", str_Printer);
}
//#endif

static inline Str str_format_impl(Str format, va_list args ) {
    ArrayList strs = arraylist_new(sizeof(Str));
    u32 last_printed = 0;
    // Scan through the format string and discover any registered format options.
    for (u32 i = 0; i < format.len; i++) {
        if (format.str[i] == '\\' && format.str[i + 1] == '{') {
            // We want to print upto here, but not the next character.
            arraylist_push(&strs, &(Str){
                    .str = format.str + last_printed,
                    .len = i - last_printed
            });
            i++;
            last_printed = i;
            continue;
        }
        if (format.str[i] == '{') {
            arraylist_push(&strs, &(Str){
                    .str = format.str + last_printed,
                    .len = i - last_printed
            });
            u32 j = i;
            bool found = false;
            while (j < format.len) {
                j++;
                if (format.str[j] == '}') {
                    found = true;
                    break;
                }
            }
            if ( found ) {
                last_printed = j + 1;
                Str option = {format.str + i, j - i + 1};
                // Match for any registered options.
                found = false;
                for ( u32 k = 0; k < _num_options; k++ ) {
                    if ( str_eq( option, options[k].format ) ) {
                        const Str fmt = options[k].printer(&args);
                        arraylist_push(&strs, (void*)&fmt);
                        i = j + 1;
                        found = true;
                        break;
                    }
                    assert(k < _num_options); // No matching format option found.
                }
                assert(found); // Did not find a matching format option.
            } else {
                assert(false); // No matching '}' found.
            }
        }
    }
    arraylist_push(&strs, &(Str){
            .str = format.str + last_printed,
            .len = format.len - last_printed
    });

    Str out = str_build_from_arraylist(&strs);

    arraylist_free(&strs);
    return out;
}

Str __attribute__((overloadable)) str_format(char * format_c, ...) {
    va_list args;
    va_start(args, format_c);
    const Str format = str_from_cstr(format_c);
    const Str out = str_format_impl(format, args);
    va_end(args);
    return out;
}

Str __attribute__((overloadable)) str_format(Str format, ...) {
    va_list args;
    va_start(args, format);
    const Str out = str_format_impl(format, args);
    va_end(args);
    return out;
}

void __attribute__((overloadable)) print(char *format_c, ...) {
    va_list args;
    va_start(args, format_c);
    const Str string = str_format_impl(str_from_cstr(format_c), args);

    write(STDOUT_FILENO, string.str, string.len);
    va_end(args);
}

void __attribute__((overloadable)) print(Str format, ...) {
    va_list args;
    va_start(args, format);
    const Str string = str_format_impl(format, args);
    write(STDOUT_FILENO, string.str, string.len);
    va_end(args);
}

Str str_concat(Str a, Str b) {
    u32 len = a.len + b.len;
    char *str = malloc(len + 1);
    for (u32 i = 0; i < a.len; i++) {
        str[i] = a.str[i];
    }
    for (u32 i = 0; i < b.len; i++) {
        str[a.len + i] = b.str[i];
    }
    str[len] = '\0';
    Str c = {str, len};
    return c;
}

Str str_from_cstr(char *cstr) {
    Str str = {cstr, 0};
    while (cstr[str.len] != '\0') {
        str.len++;
    }
    return str;
}

bool str_eq(Str a, Str b) {
    if (a.len != b.len) {
        return 0;
    }
    for (u32 i = 0; i < a.len; i++) {
        if (a.str[i] != b.str[i]) {
            return 0;
        }
    }
    return 1;
}

bool str_a_contains_b(Str a, Str b) {
    if (a.len < b.len) {
        return 0;
    }
    for (u32 i = 0; i < a.len - b.len; i++) {
        bool found = 1;
        for (u32 j = 0; j < b.len; j++) {
            if (a.str[i + j] != b.str[j]) {
                found = 0;
                break;
            }
        }
        if (found) {
            return 1;
        }
    }
    return 0;
}

Str str_build_from_arraylist( ArrayList *list ) {
    u32 total_len = 0;
    forward_it(*list, Str) {
        total_len += it->len;
    }
    char *str = malloc(total_len + 1);
    u32 offset = 0;
    forward_it(*list, Str) {
        for (u32 i = 0; i < it->len; i++) {
            str[offset + i] = it->str[i];
        }
        offset += it->len;
    }
    str[total_len] = '\0';
    return (Str){str, total_len};
}

#endif
