#include "../../inc/minishell.h"

void	cd(t_list **env, t_list **export)
{
	t_list *node;
	char	buffer[PATH_MAX];
	char	*old_dir;

	node = *env;
	if (chdir("/Users/vdarras") == -1)
	{
		perror("cd");
		return ;
	}
	if (!getcwd(buffer, sizeof(buffer)))
	{
		perror("getcwd");
		return ;
	}
	old_dir = ft_strjoin("OLDPWD=", buffer);
	while (node)
	{
		if (ft_strncmp(node->content, "OLDPWD", 6) == 0)
			node->content = old_dir;
		else if (ft_strncmp(node->content, "PWD", 3) == 0)
			node->content = "PWD=/Users/vdarras";
		node = node->next;
	}
	node = *export;
	while (node)
	{
		if (ft_strncmp(node->content, "OLDPWD", 6) == 0)
			node->content = old_dir;
		else if (ft_strncmp(node->content, "PWD", 3) == 0)
			node->content = "PWD=/Users/vdarras";
		node = node->next;
	}
	chdir("/Users/vdarras");
}

// void	cd(t_list **env, t_list **export, char *dir)
// {
// 	t_list	*node;
// 	char	buffer[PATH_MAX];
// 	char	*old_dir;
// 	char	*new_dir;

// 	node = *env;
	
// }