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
	if (format == NULL)
	{
		return (-1);
	}

	va_list args_list;
	int count = 0;

	va_start(args_list, format);

	while (*format)
	{
		if (*format == '%')
		{
			count += handle_format(&format, args_list);
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
 * handle_format - Handle format specifiers.
 * @format: Format string.
 * @args_list: Argument list.
 *
 * Return: Number of characters printed.
 */
int handle_format(const char **format, va_list args_list)
{
	(*format)++; /*move past '%'*/
	if (**format == '\0')
	{
		return (0);
	}
	if (**format == 'c')
	{
		return (handle_char_format(args_list));
	}
	if (**format == 's')
	{
		return (handle_string_format(args_list));
	}
	if (**format == '%')
	{
		return (handle_percent_format());
	}

	/*Handle unknown specifiers*/
	return (handle_unknown_format(**format));
}

/**
 * handle_char_format - Handle char format specifier.
 * @args_list: Argument list.
 *
 * Return: Number of characters printed.
 */
int handle_char_format(va_list args_list)
{
	char c = va_arg(args_list, int);

	return (write(1, &c, 1));
}

/**
 * handle_string_format - Handle string format specifier.
 * @args_list: Argument list.
 *
 * Return:Number of characters printed.
 */
int handle_string_format(va_list args_list)
{
	char *str = va_arg(args_list, char *);

	if (str == NULL)
	{
		str = "(null)";
	}
	return (write(1, str, strlen(str)));
}

/**
 * handle_percent_format - Handle percent format specifier.
 *
 * Return: Number of characters printed.
 */
int handle_percent_format(void)
{
	return (write(1, "%", 1));
}

/**
 * handle_unknown_format - Handle unknown format specifier.
 * @specifier: Unkniwn specifier.
 *
 * Return: Number of characters printed.
 */
int handle_unknown_format(char specifier)
{
	char unknown[2];

	unknown[0] = specifier;
	unknown[1] = '\0';
	return (write(1, unknown, 1));
}
