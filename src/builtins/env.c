#include "../../inc/minishell.h"

t_list	*init_env(char **envp)
{
	t_list	*env;
	t_list	*new_node;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		new_node = ft_lstnew(envp[i]);
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&env, new_node);
		i++;
	}
	return (env);
}

void print_env(t_list *env)
{
	while (env != NULL)
	{
		ft_printf("%s\n", env->content);
		env = env->next;
	}
}