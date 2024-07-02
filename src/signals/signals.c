#include "../../inc/minishell.h"

void	reset_ctrl_C(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	reset_ctrl_slash(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal(void)
{
	signal(SIGINT, &reset_ctrl_C);
	signal(SIGQUIT, &reset_ctrl_slash);
}