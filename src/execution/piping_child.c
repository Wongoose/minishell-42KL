/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:00:06 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/25 18:37:16 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 * Function creates a backup of current pipefd which will be used for the next
 * function, if there is an existing backup, function closes them, then close
 * the current pipefd.
 * 
 * @param index The current command list
 * @param n_cmds Total number of commands
 * @param pipefd The file 
*/
void	ft_close_pipe(int index, int n_cmds, int pipefd[2][2])
{
	if (index != 0)
		close(pipefd[1][0]);
	if (index != n_cmds - 1)
		pipefd[1][0] = pipefd[0][0];
	close(pipefd[0][1]);
	if (index == n_cmds - 1)
		close(pipefd[0][0]);
}

void	ft_dup(char *cmd, int fd_one, int fd_two)
{
	int	ret;
	ret = dup2(fd_one, fd_two);
	if (ret == -1)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		perror("dup2 failed");
		exit(1);
	}
}

void	last_child(t_vars *vars, t_token *group, int index, int pipefd[2][2])
{
	int	rdr_inout[2];
	// int	backup_inout[2];

	// backup_inout[0] = dup(STDIN_FILENO);
	// backup_inout[1] = dup(STDOUT_FILENO);
	ft_dup(group->cmdlst[index].cmd, pipefd[1][0], STDIN_FILENO);
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	ft_dup_inoutfile(index, group->cmdlst[index], group->hdoc_str, rdr_inout);
	if (group->cmdlst[index].has_subshell == TRUE)
		start_subshell(group->cmdlst[index], vars->envp);
	else
		execution(vars, group->cmdlst[index]);
}

void	middle_child(t_vars *vars, t_token *group, int index, int pipefd[2][2])
{
	int	rdr_inout[2];
	// int	backup_inout[2];

	// backup_inout[0] = dup(STDIN_FILENO);
	// backup_inout[1] = dup(STDOUT_FILENO);
	ft_dup(group->cmdlst[index].cmd, pipefd[0][1], STDOUT_FILENO);
	ft_dup(group->cmdlst[index].cmd, pipefd[1][0], STDIN_FILENO);
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	ft_dup_inoutfile(index, group->cmdlst[index], group->hdoc_str, rdr_inout);
	if (group->cmdlst[index].has_subshell == TRUE)
		start_subshell(group->cmdlst[index], vars->envp);
	else
		execution(vars, group->cmdlst[index]);
}

void	first_child(t_vars *vars, t_token *group, int index, int pipefd[2][2])
{
	int	rdr_inout[2];
	// int	backup_inout[2];

	// backup_inout[0] = dup(STDIN_FILENO);
	// backup_inout[1] = dup(STDOUT_FILENO);
	ft_dup(group->cmdlst[index].cmd, pipefd[0][1], STDOUT_FILENO);
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	ft_dup_inoutfile(index, group->cmdlst[index], group->hdoc_str, rdr_inout);
	if (group->cmdlst[index].has_subshell == TRUE)
		start_subshell(group->cmdlst[index], vars->envp);
	else
		execution(vars, group->cmdlst[index]);
}
