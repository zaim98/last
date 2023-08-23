#include "shell.h"
/**
 * isInteractiveMode - Entry point.
 * @info: struct containing shell information
 * Description: Returns true if the shell is in interactive mode.
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int isInteractiveMode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - Entry point.
 * @c: the character to check
 * @delim: the delimiter string
 * Description: Checks if a character is a delimiter.
 * Return: 1 if true, 0 if false.
 */
int isDelimiter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * isAlpha - Entry point.
 * @c: The character to check
 * Description: Checks for an alphabetic character.
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int isAlpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * stringToInteger - Entry point.
 * @s: the string to be converted
 * Description: Converts a string to an integer.
 * Return: 0 if no numbers in the string, the converted number otherwise.
 */
int stringToInteger(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
