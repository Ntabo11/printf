#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * _printf - Custom printf function.
 * @format: Format string.
 *
 * Return: Number of characters printed.
 */
int _printf(const char *format, ...)
{
	va_list args_list;
	int count = 0;
	char *str, c;

	va_start(args_list, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c')
			{
				c = va_arg(args_list, int);
				count += write(1, &c, 1);
			}
			else if (*format == 's')
			{
				str = va_arg(args_list, char *);
				while (*str)
				{
					count += write(1, str++, 1);
				}
			}
			else if (*format == '%')
			{
				count += write(1, "%", 1);
			}
			else
			{
				count += write(1, "%", 1);
				count += write(1, format, 1);
			}
		}
		else
		{
			count += write(1, format, 1);
		}
		format++;
	}
	va_end(args_list);
	return (count);
}
/**
 * _print - funct
 * @format: format.
 * Return: printed chars.
 * @get_flags: character
 * @get_width: character
 * @get_precision: character
 * @get_size: character
 */
int _print(const char *format, ...)
{
	int get_flags(const char *format, int *i);
	int get_width(const char *format, int *i, va_list list);
	int get_precision(const char *format, int *i, va_list list);
	int get_size(const char *format, int *i);

	int handle_print(const char *format, int *i, va_list list, char *buffer,
			int flags, int width, int precision, int size);
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFSIZ];

	if (format == NULL)
		return (-1);
	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFSIZ)
				print_buffer(buffer, & buff_ind);/*write(1,&format,1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, & buff_ind);
			flags = get_flags(format, & i);
			width = get_width(format, & i, list);
			precision = get_precision(format, & i, list);
			size = get_size(format, & i);
			++i;
			printed = handle_print(format, & i, list, buffer,
					flags, width, precision, size);
			if (printed == -1)
			{
				va_end(list);
				return (-1);
			}
			printed_chars += printed;
		}
	}
	print_buffer(buffer, & buff_ind);
	va_end(list);
	return (printed_chars);
}
/**
 * print_buffer - prints the cont of the buffer id exist
 * @buffer: array of chrs
 * @buff_in: index at which to add next char, represents the length
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, & buffer[0], *buff_ind);
	*buff_ind = 0;
}

#define S_LONG 1
#define S_SHORT 2
#define F_PLUS 1
#define MY_FD_ZERO 2
#define F_HASH 3
#define f_space 4
/**
 * get_width - calc the width for printing
 * @format: formatted strg
 * @i: list of arg
 * @list: list of arg
 * Return: width
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int width = 0;

	for (curr_i +=  1; format[curr_i] != '\0'; curr_i++)
	{
		if(isxdigit(format[curr_i]))
		{
			width *=10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
	}
	*i = curr_i - 1;
	return (width);
}
/**
 * get_size - calc size to cast the arg
 * @format: formatted strg in which to print the arg
 * @i: list of arg
 * Return: precision
 */
int get_size(const char *format, int *i)
{
	int curr_i = *i = 1;
	int size = 0;
	if (format[curr_i] == '|')
		size = S_LONG;
	else if (format[curr_i] == 'h')
		size = S_SHORT;
	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;
	return (size);
}
/**
 * get_precision - calc the precision for printing
 * @format: formatted strg in which to print the arg
 * @i:lis of arguments to be printed
 * @list: list of arg
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int precision = -1;

	if (format[curr_i] !='.')
		return (precision);
	precision = 0;
	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (isxdigit(format[curr_i]))
		{
			precision *= 10;
			precision +=format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = curr_i - 1;
	return (precision);
}
/**
 * get_flags - calc active falgs
 * @format: formatted strg in which print arg
 * @i: take a parameer
 * return: flags
 */
int get_flags(const char *format, int *i)
{
	int j, curr_i = *i + 1;
	int flags = 0;

	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ' , '\0'};
	const int FLAGS_ARR[] = {F_PLUS, MY_FD_ZERO, F_HASH,f_space, 0};
	
	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if(format[curr_i] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}
		if (FLAGS_CH[j] == 0)
			break;
	}
	return (flags);
}
/**
 * handle_print - Prints an arg based on its type
 * @fmt: formatted stg in which to print the arg
 * @list: list of arg to be printed
 * @ind: ind
 * @buffer: buffer array to handle print
 * @flags: calc active flags
 * @width: get width
 * @precision: precision specification
 * @size: size specifier
 * Return: 1 or 2
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
		int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string},{'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_non_printable},
		{'X', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));
	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
