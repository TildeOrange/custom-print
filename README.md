# custom-print
A customizable fprintf - v1 - Jan 2021

## Example Program
```C
#define CUSTOM_PRINT_IMPLEMENTATION
#include "custom_print.h"

typedef struct vector3f
{
  float x, y, z;
} vector3f;

#define v3f(x, y, z) (vector3f) { (float) x, (float) y, (float) z }

void _print_vector3f(FILE *stream, va_list *args)
{
  vector3f v = va_arg(*args, vector3f);
  fprintf(stream, "(%.3f, %.3f, %.3f)", v.x, v.y, v.z);
}

void main()
{
  printer_t printer = { 0 };
  printer.callbacks['v'] = _print_vector3f;

  vector3f a, b, c;
  a = v3f(4.0f, 2.0f, 0.0f);
  b = v3f(6.0f, 6.9f, 9.0f);
  c = v3f(a.x + b.x, a.y + b.y, a.z + b.z);

  cp_printf(&printer, "%v + %v = %v\n", a, b, c);
}
```
*Output*:
``
(4.000, 2.000, 0.000) + (6.000, 6.900, 9.000) = (10.000, 8.900, 9.000)
``
