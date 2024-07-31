/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:02:24 by vdarras           #+#    #+#             */
/*   Updated: 2024/07/31 20:11:13 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void	wait_child(int child_count, pid_t *child_pids)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < child_count)
    { 
        waitpid(child_pids[i], &wstatus, 0);
        if (WIFEXITED(wstatus))
            g_exit_status = WEXITSTATUS(wstatus);
        i++;
    }
}

// void	parent_process()