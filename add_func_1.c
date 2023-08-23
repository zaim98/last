#include "shell.h"
/**
 * atoi_err - Entry point.
 * @s: the string to be converted
 * Description: Converts a string to an integer.
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int atoi_err(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_err - Entry point.
 * @info: parameter & return info struct
 * @estr: string containing specified error type
 * Description: Prints an error message.
 * Return: 0 if no numbers, otherwise -1 on error.
 */
void print_err(info_t *info, char *estr)
{
	eputs(info->fname);
	eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	eputs(": ");
	eputs(info->argv[0]);
	eputs(": ");
	eputs(estr);
}

/**
 * print_d - Entry point.
 * @input: the input
 * @fd: the filedescriptor to write to
 * Description: Prints a decimal (integer) number (base 10).
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*_putc)(char) = putchar;
	int i, count = 0;
	unsigned int abs_, current;

	if (fd == STDERR_FILENO)
		_putc = eputchar;
	if (input < 0)
	{
		abs_ = -input;
		_putc('-');
		count++;
	}
	else
		abs_ = input;
	current = abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_ / i)
		{
			_putc('0' + current / i);
			count++;
		}
		current %= i;
	}
	_putc('0' + current);
	count++;

	return (count);
}

/**
 * convert_num - Entry point.
 * @num: number
 * @base: base
 * @flags: argument flags
 * Description: Converter function, a clone of itoa.
 * Return: string
 */
char *convert_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments - Entry point.
 * @buf: address of the string to modify
 * Description: Replaces first instance of '#' with '\0'.
 * Return: Always 0;
 */
void rm_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

