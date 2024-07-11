#include "../../inc/minishell.h"

void	print_env(t_list *env)     // print/reproduit la commande "env"
{
	t_list	*node;
	int		i;

	i = 0;
	node = env;
	while (node != NULL)
	{
		if (i != env->count - 1)
			ft_printf("%s\n", node->content);
		else
			ft_printf("_=/usr/bin/env\n");
		node = node->next;
		i++;
	}
}
