#include "../../inc/minishell.h"
//mode = 1 ==> print / mode != 1 ==> not print
void	print_env(t_lst *env)
{
	t_env	*node;

	if (!env)
		return ;
	node = env->head;
	while (node != NULL)
	{
		if (node->flag == 1)
		{
			ft_printf("%s=",node->var);
			if (node->value)
				ft_printf("%s\n", node->value);
		}
		node = node->next;
	}
}

