#include <stdarg.h>
#include <unistd.h>
#include "main.h"
/**
 * _print_integer - print an integer
 * @num: the int to printed
 * @c: integer
 * @count: pointer to the count of printed char
 */
void _print_integer(int num, int *count)
{
	int c;

	if (num < 0)
	{
		write(1, "-", 1);
		num = -num;
		(*count)++;
	}
	if (num / 10 != 0)
	{
		_print_integer(num / 10, count);
	}
	c = num % 10 + '0';
	write(1, &c, 1);
	(*count)++;
}
