//
// custom_printf 
// v1
// Jan 2021
// Boyd Thomas
//
//
// Define CUSTOM_PRINT_IMPLEMENTATION in one .c or .cpp file before including
// this file.
//
// How to Use:
// ----------------------------------------------------------------------------
// >> main.c
// 
// #define CUSTOM_PRINT_IMPLEMENTATION
// #include "custom_print.h"
// 
// static void _print_vector(FILE *stream, va_list *args)
// {
//     const vector_t *v = va_arg(*args, const vector_t*);
//     fprintf(stream, "(%.3f, %.3f, %.3f)", v->x, v->y, v->z);
// }
// 
// void main()
// {
//     printer_t printer = { 0 };
//     printer.callbacks['v'] = _print_vector;
// 
//     cp_printf("%v - %v = %v", &a, &b, &c);
// }
// 
// ----------------------------------------------------------------------------
// >> stdout
// (2.00, 5.00, 3.00) - (1.00, 2.00, 3.00) = (1.00, 3.00, 0.00)
// ----------------------------------------------------------------------------
//
// See bottom for license information.
//

#ifndef _CUSTOM_PRINT_H
#define _CUSTOM_PRINT_H

#include <stdarg.h>
#include <stdio.h>

typedef void (*custom_print_cb_t)(FILE *stream, va_list *args);

typedef struct printer_t
{
    custom_print_cb_t callbacks[0xff];
} printer_t;

void cp_fprintf(const printer_t *printer, FILE *stream, const char *format, ...);
void cp_vfprintf(const printer_t *printer, FILE *stream, const char *format, va_list args);
#define cp_printf(printer, format, ...) cp_fprintf(printer, stdout, format, __VA_ARGS__)
#define cp_vprintf(printer, format, args) cp_vfprintf(printer, stdout, format, args)


#ifdef CUSTOM_PRINT_IMPLEMENTATION

void cp_fprintf(const printer_t *printer, FILE *stream, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    cp_vfprintf(printer, stream, format, args);
    va_end(args);
}

void cp_vfprintf(const printer_t *printer, FILE *stream, const char *format, va_list args)
{
    char c;
    while ((c = *format++) != '\0')
    {
        if (c != '%')
        {
            putc(c, stream);
            continue;
        }

        // Handle Escape Sequence
        c = *format++;

        if (c == '\0')
            break;

        custom_print_cb_t cb = printer->callbacks[c];
        if (!cb || c == '%')
        {
            putc(c, stream);
            continue;
        }

        cb(stream, &args);
    }
}

#endif

#endif 

// ----------------------------------------------------------------------------
// Public Domain (www.unlicense.org)
// This is free and unencumbered software released into the public domain.
// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
// software, either in source code form or as a compiled binary, for any purpose,
// commercial or non-commercial, and by any means.
// In jurisdictions that recognize copyright laws, the author or authors of this
// software dedicate any and all copyright interest in the software to the public
// domain. We make this dedication for the benefit of the public at large and to
// the detriment of our heirs and successors. We intend this dedication to be an
// overt act of relinquishment in perpetuity of all present and future rights to
// this software under copyright law.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// ----------------------------------------------------------------------------
