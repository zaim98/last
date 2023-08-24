#include "shell.h"
/**
 * get_sigint - Engtry point.
 * @sig: Signal handler
 * Description: This function Handle the crtl + c call in prompt.
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
