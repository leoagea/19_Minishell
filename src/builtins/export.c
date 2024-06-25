#include "../../inc/minishell.h"

char	*min_node(t_list *env)
{
	t_list *node;
	t_list	*node_to_flag;
	char	*str;
	int		i;

	i = 0;
	node = env;
	node_to_flag = node;
	str = "__CF_USER_TEXT_ENCODING=0x0:0:0";
	while (i < env->count - 1)
	{
		if (ft_strncmp(str, node->next->content, ft_strlen(str)) > 0 && node->next->flag == 0 && ft_strncmp("_=/usr/bin/env", node->next->content, 15) != 0)
		{
			str = node->next->content;
			node_to_flag = node->next;
		}
		node = node->next;
		i++;
	}
	node_to_flag->flag = 1;
	return(str);
}

t_list	*init_export(t_list	*env)   // INITIALISE LISTE EXPORT
{
	t_list	*export;
	t_list	*new_node;
	t_list	*node;
	int		i;

	i = 0;
	export = NULL;
	while (i < env->count - 1)
	{
		new_node = ft_lstnew(min_node(env));
		if (!new_node)
			return (NULL);
		ft_lstadd_back(&export, new_node);
		i++;
	}
	return (export);
}

int main(int argc, char **argv, char **envp)
{
	t_list *env;
	t_list *export;
	t_list *node;
	int		i = 0;
	env = init_env(envp);
	export = init_export(env);
	node = export;
	while (i < env->count - 1)
	{
		if (ft_strncmp("_=/Users/vdarras/Cursus/minishell/./minishell", node->content, 46) != 0)
			printf("%s\n", node->content);
		node = node->next;
		i++;
	}
	return (0);
}