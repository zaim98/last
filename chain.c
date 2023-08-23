#include "shell.h"
/**
 * check_delimiters - Entry point.
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Description: Tests if the current character
 *	in the buffer is a chain delimiter.
 * Return: 1 if a chain delimiter, 0 otherwise
 */
int check_delimiters(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * adjust_chain - Entry point.
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Description: Checks whether we should continue
 *	chaining based on the last status.
 * Return: Void
 */
void adjust_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_aliases - Entry point.
 * @info: the parameter struct
 * Description: Replaces an alias in the tokenized string.
 * Return: 1 if replaced, 0 otherwise
 */
int replace_aliases(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_alias_starting_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = find_character(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_variables - Entry point.
 * @info: the parameter struct
 * Description: Replaces variables in the tokenized string.
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_str(&(info->argv[i]),
					_strdup(convert_num(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_str(&(info->argv[i]),
					_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = find_var_starting_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_str(&(info->argv[i]),
					_strdup(find_character(node->str, '=') + 1));
			continue;
		}
		replace_str(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_str - Entry point.
 * @old: address of the old string
 * @new: new string
 * Description: Replaces a string.
 * Return: 1 if replaced, 0 otherwise
 */
int replace_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
