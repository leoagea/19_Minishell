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

int		exec_builtin(t_cmd *command, t_data *data)
{
// 	// if (ft_strncmp(command->str[0], "cd", INT_MAX) == 0)
// 	// 	cd(command->env, command->export);
// 	// if (ft_strncmp(command->str[0], "echo", INT_MAX) == 0 )
// 	// 	echo();
// 	// if (ft_strncmp(command->str[0], "env", INT_MAX) == 0 )
// 	// 	env();
// 	// if (ft_strncmp(command->str[0], "exit", INT_MAX) == 0 )
// 	// 	exit();
// 	// if (ft_strncmp(command->str[0], "export", INT_MAX) == 0 )
// 	// 	export();
// 	// if (ft_strncmp(command->str[0], "pwd", INT_MAX) == 0 )
// 	// 	pwd();
// 	// if (ft_strncmp(command->str[0], "unset", INT_MAX) == 0 )
// 	// 	unset();


	if (ft_strncmp(command->str[0], "export", INT_MAX) == 0)
		export(data, command);
	else if (ft_strncmp(command->str[0], "unset", INT_MAX) == 0)
		unset(data, command);
	else if (ft_strncmp(command->str[0], "echo", INT_MAX) == 0)
		echo(command);
	else if (ft_strncmp(command->str[0], "env", INT_MAX) == 0)
		print_env(data->env);
	else if (ft_strncmp(command->str[0], "cd", INT_MAX) == 0)
		cd(data);
	else if ((ft_strncmp(command->str[0], "pwd", INT_MAX) == 0))
		pwd();
	else
		return -1;
	return 0;
}