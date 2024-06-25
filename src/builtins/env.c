#include "../../inc/minishell.h"

int		count_nodes(t_list *list)
{
	int	i;
	t_list	*node;

	i = 0;
	node = list;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

t_list	*init_env(char **envp) // INITIALISE LISTE ENV
{
	t_list	*env;
	t_list	*new_node;
	t_list	*node;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		new_node = ft_lstnew(envp[i]);
		if (!new_node)
			return (NULL); // free elements liste chainee
		ft_lstadd_back(&env, new_node);
		i++;
	}
	node = env;
	while (node != NULL)
	{
		node->flag = 0;
		node = node->next;
	}
	env->count = count_nodes(env);
	return (env);
}

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
