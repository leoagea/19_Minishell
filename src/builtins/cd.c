#include "../../inc/minishell.h"

void	cd_home(t_list **env, t_list **export)
{
	t_list *node;
	char	buffer[PATH_MAX];
	char	*old_dir;

	node = *env;
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
		if (ft_strncmp(node->content, "PWD", 3) == 0)
			node->content = "PWD=/Users/vdarras";
		node = node->next;
	}
	node = *export;
	while (node)
	{
		if (ft_strncmp(node->content, "OLDPWD", 6) == 0)
			node->content = old_dir;
		if (ft_strncmp(node->content, "PWD", 3) == 0)
			node->content = "PWD=/Users/vdarras";
		node = node->next;
	}
	chdir("/Users/vdarras");
}

