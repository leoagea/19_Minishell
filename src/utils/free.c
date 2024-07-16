#include "../../inc/minishell.h"

int     length_array_char(char **array)
{
	int count;

	count = 0;
	while (array[count])
		count++;
	return (count);
}

void	free_tab_char(char **array)
{
		int	i;

	i = length_array_char(array);
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

void	dll_cmd_clear(t_dll_cmd *dll)
{
	t_cmd	*temp;
	t_cmd	*current;

	if (!dll)
		return ;
	current = dll->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}