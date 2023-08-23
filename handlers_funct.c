#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * handle_funct - Print a strg
 * @c: char types
 * @buffer: Buffer array to handle print
 * @flags: calc active flags
 * @width: width
 * @FD_ZERO: character
 * @BUFSIZ: size of Buffe
 * @F_MINUS: charatcer
 * Return: Nbr of chars printed
 */
int handle_funct(char c, char buffer[],
		int flags, int width, int F_MINUS, int FD_ZERO)
{
	int i = 0;
	char padd =  ' ';
	
	if (flags & FD_ZERO)
		padd = '0';
	buffer[i++] = c;
	buffer[i] = '\0';
	
	if (width > 1)
	{
		buffer[BUFSIZ - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFSIZ - i -2] = padd;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1)+
					write(1, &buffer[BUFSIZ - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFSIZ - i - 1], width - 1)+
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/**
 * number_function - prints a strg
 * @is_negative: lista of arguments
 * @ind: char types
 * @buffer: Buffer array to handle print
 * @flags: Calc actives flags
 * @width: get width
 * @FD_ZERO: cahracter
 * @BUFSIZ: size of Buffe
 * @F_MINUS: charatcer
 * @F_PLUS: charatcer
 * @prec: precision specifier
 * @size: size specifier
 * return: Nbr of char printed
 */
int number_function(int is_negative, int ind, char buffer[],
		int flags, int width, int prec, int F_MINUS,
		int F_ZERO, char F_PLUS, char F_SPACE)
{
	int length = BUFSIZ - ind - 1;
	char padd = ' ', extra_ch = 0;

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '_';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';
	return (write_num(ind, buffer, flags, width, prec, length, padd, extra_ch, F_MINUS));
	return (0);
}

/**
 * write_num - Write a Nbr using a buffer
 * @ind: index at which the Nbr starts on the buffer
 * @buffer: Buffer
 * @flags: flags
 * @FD_ZERO: cahracter
 * @BUFSIZ: size of Buffe
 * @F_MINUS: charatcer
 * @F_PLUS: charatcer
 * @width: Width
 * @prec: precision specifier
 * @length: Nbr length
 * @padd: pading char
 * @extra_c:Xtra char
 * Return: Nbr of printed Char
 */
int write_num(int ind, char buffer[], int flags, int width, int prec,
		int length, char padd, char extra_c, int F_MINUS)
{
	int i, padd_start= 1;

	if (prec == 0 && ind == BUFSIZ - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFSIZ - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length++)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, & buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if(extra_c)
				buffer[--ind] = extra_c;
			return(write(1, & buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, & buffer[padd_start], i - padd_start) + 
					write(1, & buffer [ind], length - (1 - padd_start)));
		}
	}
	return (0);
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, & buffer[ind], length));
}
