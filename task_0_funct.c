#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
/**
 * _printf - printf funct()
 * @format:string containing directive
 * @...: var Nbr of Arg
 * Return: Always(0)
 */
int _printf(const char *format, ...)
{
	int count = 0;
	va_list args;
	char c;
	char *s;
	int d;
	unsigned int i;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
				case 'c':
					c = (char) va_arg(args, int);
					write(1, &c, 1);
					count++;
					break;
				case 's':
					s = va_arg(args, char *);
					while (*s)
					{
						write(1, s, 1);
						s++;
						count++;
					}
					break;
				case '%':
					write(1, "%", 1);
					count++;
					break;
				case 'd':
					d = va_arg(args, int);
					if(d < 0)
					{
						d = -d;
						write(1, "-", 1);
						count++;
					}
					print_numberd(d, &count);
					break;
				case 'i':
					i = va_arg(args, unsigned int);
					print_hex(i, &count);
					break;
			}
		}
		else
		{
			write(1, format, 1);
			count++;
		}
		format++;
	}

	va_end(args);
	return (count);
}
/**
 * print_numb - print an int
 * @n: the integer to be printed
 * @count: *p to the count of printed char
 */
void print_numberd(int n, int *count)
{
	char c;

	if(n < 0)
	{
		write(1, "-", 1);
		n = -n;
		(*count)++;
	}
	if (n / 10 != 0)
	{
		print_numberd(n / 10, count);
	}
	c = n % 10 + '0';
	write(1, &c, 1);
	(*count)++;
}
void print_hex(unsigned int n, int *count)
{
	char digit;

	if (n / 16 != 0)
		print_hex(n / 16, count);

	digit = n % 16;

	if (digit < 10)
		digit += '0';
	else
		digit += 'a' - 10;
	write(1, &digit, 1);
	(*count)++;
}
