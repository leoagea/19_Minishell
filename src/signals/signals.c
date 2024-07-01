#include "../../inc/minishell.h"

void	reset(int nb)
{
	(void)nb;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_c_d(void)
{
	signal(SIGINT, &reset);
}