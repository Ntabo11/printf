#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>

int _printf(const char *format, ...);
int _print(const char *format, ...);
int _putchar(char c);
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
                int flags, int width, int precision, int size);
void print_buffer(char buffer[], int *buff_ind);
int number_function(int is_negative, int ind, char buffer[],
                int flags, int width, int prec, int F_MINUS,
                int F_ZERO, char F_PLUS, char F_SPACE);
int write_num(int ind, char buffer[], int flags, int width, int prec,
		int length, char padd, char extra_c, int F_MINUS);
int print_char(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_string(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_percent(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_int(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_binary(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_unsigned(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_octal(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_hexadecimal(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_hexa_upper(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_pointer(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_non_printable(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_reverse(va_list args, char *buffer, int flags, int width,
		int precision, int size);
int print_rot13string(va_list args, char *buffer, int flags, int width,
		int precision, int size);
/**
 * typedef struct
 */
typedef struct {
	char fmt;
	int (*fn)(va_list, char *, int, int, int, int);
} fmt_t;

#endif /* MAIN_H */
