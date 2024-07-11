#include "../../inc/minishell.h"

char	*min_node(t_list *env)
{
	t_list *node;
	t_list	*node_to_flag;
	char	*str;
	int		i;
	int		total;

	i = 0;
	total = 0;
	node = env;
	node_to_flag = node;
	str = "~~~~~~~~~~~~~~~~~~~";
	while (i < env->count - 1)
	{
		if (ft_strncmp(str, node->content, ft_strlen(str)) > 0 && node->flag == 0 && ft_strncmp("_=/usr/bin/env", node->content, 15) != 0)
		{
			str = node->content;
			node_to_flag = node;
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

void	print_export(t_list *export)    // command : export
{
	t_list *node;
	int		i;

	i = 0;
	node = export;
	while (node)
	{
		if (ft_strncmp("_=/Users/vdarras/Cursus/minishell/./minishell", node->content, 46) != 0)
		{
			ft_printf("declare -x ");
			ft_printf("%s\n", (char *)node->content);
		}
		node = node->next;
		i++;
	}
}

// int		check_existing(t_list *list, char *str)
// {
	
// }

int		check_mutlitple_equal(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '=')
			i++;
		str++;
	}
	if (i > 1)
		return (2);
	if (i == 1)
		return (1);
	return (0);
}

void	export_node_0equal(t_list **export, char *str)
{
	t_list *new_node;
	t_list *node;
	char	*temp;
	char	*new_str;

	node = *export;
	temp = ft_strjoin(str, "=''");
	new_str = temp;
	new_node = ft_lstnew(temp);
	if (ft_strncmp(str, node->content, ft_strlen(str)) <= 0)
	{
		ft_lstadd_front(export, new_node);
		return ;
	}
	while (ft_strncmp(str, node->next->content, ft_strlen(str)) > 0 && node->next->next != NULL)
		node = node->next;
	if (node->next->next != NULL)
	{
		new_node->next = node->next->next;
		node->next->next = new_node;
		return ;
	}
	ft_lstadd_back(export, new_node);
	free(temp);
}

void	export_node_1equal(t_list **env, t_list **export, char *str)      // export VAR=XXXX
{
	t_list *new_node;
	t_list *new_node2;
	t_list *node;

	new_node = ft_lstnew(str);
	new_node2 = ft_lstnew(str);
	node = *export;
	ft_lstadd_back(env, new_node);
	if (ft_strncmp(str, node->content, ft_strlen(str)) <= 0)
	{
		ft_lstadd_front(export, new_node2);
		return ;
	}
	while (ft_strncmp(str, node->next->content, ft_strlen(str)) > 0 && node->next->next != NULL)
		node = node->next;
	if (node->next->next != NULL)
	{
		new_node2->next = node->next->next;
		node->next->next = new_node2;
		return ;
	}
	ft_lstadd_back(export, new_node2);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_list *env;
// 	t_list *export;

// 	env = init_env(envp);
// 	export = init_export(env);
// 	export_node(&env, &export, "NNN");
// 	print_export(export);

// 	return (0);
// }

//TODO : REPLACE IF ALREADY EXISTING VAR ; VAR+=XXXX -> ft_strjoin

//export sans rien a check
//export avec une variable sans = a check

//a faire export += et export multi variabbles et export var="string"