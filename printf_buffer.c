#include <stdio.h>
#include <stdarg.h>

#define BUFFER_SIZE 1024

/**
 * buffered_printf - Formatted output with buffering.
 * @format: The format string.
 * @...: Additional arguments based on format.
 *
 * This function proides a buffered version of printf-lie formatted output.
 * It accumulates the formatted content in a local and writes it to
 * the standard output in a single operation.
 */
void buffered_printf(const char *format, ...)
{
	char buffer[BUFFER_SIZE];
	int position = 0;
	va_list argms;

	va_start(argms, format);

	int chars_written = vsnprintf(buffer, BUFFER_SIZE, format, argms);

	va_end(argms);

	if (chars_written > -1 && chars_written < BUFFER_SIZE)
	{
		/*Write buffer to output (stdout) */
		fwrite(buffer, 1, chars_written, stdout);
	}
}

/**
 * main - Entry point of the program.
 *
 * This function demonstrates the usgae of the buffered_printf function
 * Return: Always 0.
 */
int main(void)
{
	buffered_printf("This is a %s example with %d formatted %s.\n",
			"buffered", 123, "output");
	buffered_printf("An unknown specifier: %p\n", (void *)12345);
	return (0);
}
