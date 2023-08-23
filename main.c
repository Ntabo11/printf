#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include "main.h"
/**
 * main - Entry point
 * Return: Always 0
 */
int main(void)
{
	int len;
	int len2;
	unsigned int ui;
	void *addr;
	
	len = _printf("Let's try to printf a simple sentence.\n");
	len2 = printf("Let's try to printf a simple sentence.\n");
	ui = (unsigned int)INT_MAX + 1024;
	addr = (void *)0x7ffe637541f0;
	_printf("Length:[%d, %i]\n", len, len);
	printf("Length:[%d, %i]\n", len2, len2);
	_printf("Negative:[%d]\n", -762534);
	printf("Negative:[%d]\n", -762534);
	_printf("Unsigned:[%u]\n", ui);
	printf("Unsigned:[%u]\n", ui);
	_printf("Unsigned octal:[%o]\n", ui);
	printf("Unsigned octal:[%o]\n", ui);
	_printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
	printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
	_printf("Character:[%c]\n", 'H');
	printf("Character:[%c]\n", 'H');
	_printf("String:[%s]\n", "I am a string !");
	printf("String:[%s]\n", "I am a string !");
	_printf("Address:[%p]\n", addr);
	printf("Address:[%p]\n", addr);
	len = _printf("Percent:[%%]\n");
	len2 = printf("Percent:[%%]\n");
	_printf("Len:[%d]\n", len);
	printf("Len:[%d]\n", len2);
	_printf("Unknown:[%r]\n");
	printf("Unknown:[%r]\n");
	return (0);
}
/**
 * print_buffer - prints the cont of the buffer id exist
 * @buffer: array of chrs
 * @buff_in: index at which to add next char, represents the length
 * @format: The format string.
 * @...: Additional arguments based on format.
 * This function proides a buffered version of printf-lie formatted output.
 * It accumulates the formatted content in a local and writes it to
 * the standard output in a single operation.
 */
void print_buffer1(const char *buffer[BUFSIZ], int *buff_ind)
{
	
	if (*buff_ind > 0)
	{
		write(1, & buffer[0], *buff_ind);
		*buff_ind = 0;
	}
}
/**
 * main - Entry point of the program.
 *
 * This function demonstrates the usgae of the buffered_printf function
 * Return: Always 0.
 */
int main_buffer(void)
{
        print_buffer("This is a %s example with %d formatted %s.\n",
                        "buffered", 123, "output");
        print_buffer("An unknown specifier: %p\n", (void *)12345);
        return (0);
}
