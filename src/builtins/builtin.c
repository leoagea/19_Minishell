#include "../../inc/minishell.h"

void	is_builtin(t_cmd *command)
{
	t_cmd	*node;

	node = command;
	while (node)
	{
		if (ft_strncmp(node->str[0], "cd", INT_MAX) == 0 ||
			ft_strncmp(node->str[0], "echo", INT_MAX) == 0 ||
			ft_strncmp(node->str[0], "env", INT_MAX) == 0 ||
			ft_strncmp(node->str[0], "exit", INT_MAX) == 0 ||
			ft_strncmp(node->str[0], "export", INT_MAX) == 0 ||
			ft_strncmp(node->str[0], "pwd", INT_MAX) == 0 ||
			ft_strncmp(node->str[0], "unset", INT_MAX) == 0)
			node->is_builtin = true;
		else
			node->is_builtin = false;
		node = node->next;
	}
}


// int		exec_builtin(t_cmd *command)
// {
// 	if (ft_strncmp(command->str[0], "cd", INT_MAX) == 0)
// 	{
// 		cd(command->env)
// 	}
// 	else if (ft_strncmp(command->str[0], "cd", INT_MAX) == 0 )

// }