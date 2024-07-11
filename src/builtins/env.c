#include "../../inc/minishell.h"
//mode = 1 ==> env / mode != 1 ==> export
void	print_env(t_list *env, int mode)
{
	t_list	*node;

	node = env;
	if (mode == 1)
	{
		while (node != NULL)
		{
			ft_printf("%s=",node->var);
			if (node->flag == 1)
				ft_printf("%s\n", node->value);
			node = node->next;
		}
	}
	else
	{
		while (node != NULL)
		{
			ft_printf("%s=",node->var);
			if (node->flag == 1)
				ft_printf("\"%s\"\n", node->value);
			node = node->next;
		}
	}
}

