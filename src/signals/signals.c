/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:31:33 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 14:12:03 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	prompt(int sig)
{
	g_exit_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	reset_ctrl_c(int sig)
{
	g_exit_status = 130;
	(void)sig;
}

void	reset_ctrl_slash(int sig)
{
	g_exit_status = 131;
	write(2, "Quit: 3\n", 8);
	(void)sig;
}

void	handle_signal(int process)
{
	struct termios	term;

	if (process == 0)
	{
		signal(SIGINT, prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (process == 1)
	{
		signal(SIGINT, reset_ctrl_c);
		signal(SIGQUIT, reset_ctrl_slash);
	}
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}
