#include "main.h"
/**
 * handle_funct - Print a strg
 * @c: char types
 * @buffer: Buffer array to handle print
 * @flags: calc active flags
 * @width: width
 * @precision: precision specifier
 * @size: size specifier
 * Return: Nbr of chars printed
 */
int handle_funct(char c, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = 0;
	char padd =  '';
	
	if (flags & F_ZERO)
		padd = '0';
	buffer[i++] = c;
	buffer[i] = '\0';
	
	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i -2] = padd;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1)+
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1)+
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/**
 * number_funct - prints a strg
 * @is_negative: lista of arguments
 * @ind: char types
 * @buffer: Buffer array to handle print
 * @flags: Calc actives flags
 * @width: get width
 * @prec: precision specifier
 * @size: size specifier
 * return: Nbr of char printed
 */
int number_funct(int is_negative, int ind, char buffer[],
		int flags, int width, int prec, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char pad = '', extra_ch = 0;

	if ((flags & F_ZERO) && !(FLAGS & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '_';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = '';
	return (write_num(ind, buffer, flags, width, prec,
				length, padd, extra_ch));
}
/**
 * write_num - Write a Nbr using a buffer
 * @ind: index at which the Nbr starts on the buffer
 * @buffer: Buffer
 * @flags: flags
 * @width: Width
 * @prec: precision specifier
 * @length: Nbr length
 * @padd: pading char
 * @extra_c:Xtra char
 * Return: Nbr of printed Char
 */
int num_funct(int ind, char buffer[], int flags, int width,
		int prec, int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = '';
	of (prec > 0 && prec < length)
		padd = '';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	

