#include "shell.h"
/**
 * hist - Entry point.
 * @info: Parameter struct.
 * Description: This function Display the history list, one command
 *	per line, preceded by line numbers starting at 0.
 * Return: Always 0.
 */
int hist(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unalias - Entry point.
 * @info: Parameter struct.
 * @alias: The custom alias to unset.
 * Description: This function Unsets a custom alias.
 * Return: Always 0 on success, 1 on error.
 */
int unalias(info_t *info, char *alias)
{
	char *equalsign, temp;
	int ret;

	equalsign = _strchr(alias, '=');
	if (!equalsign)
		return (1);
	temp = *equalsign;
	*equalsign = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, alias, -1)));
	*equalsign = temp;
	return (ret);
}

/**
 * alias - Entry point.
 * @info: Parameter struct.
 * Description: This function Sets or displays custom aliases.
 * Return: Always 0.
 */
int alias(info_t *info)
{
	int i = 0;
	char *equalsign;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_custom_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equalsign = _strchr(info->argv[i], '=');
		if (equalsign)
			set_custom_alias(info, info->argv[i]);
		else
			print_custom_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
