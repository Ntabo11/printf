#include <stdarg.h>
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
	char *rod, c;

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
				rod = va_arg(args_list, char *);
				while (*rod)
				{
					count += write(1, rod++, 1);
				}
			}
			else if (*format == '%')
			{
				count += write(1, "%", 1);
			}
		}
		else
		{
			count += write(1, "%", 1); /*Print unknown specifier*/
			count += write(1, format, 1);
		}
		format++;
	}
	va_end(args_list);
	return (count);
}
