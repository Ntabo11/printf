#ifndef MAIN_H
#define MAIN_H

int _printf(const char *format, ...);
int _putchar(char c);
int number_function(int is_negative, int ind, char buffer[],
                int flags, int width, int prec, int F_MINUS,
                int F_ZERO, char F_PLUS, char F_SPACE);
int write_num(int ind, char buffer[], int flags, int width, int prec,
		int length, char padd, char extra_c, int F_MINUS);
		
#endif /* MAIN_H */
