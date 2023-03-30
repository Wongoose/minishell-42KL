/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:00:06 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/30 19:15:04 by chenlee          ###   ########.fr       */
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

int	last_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid)
{
	int	fd_inout[2];
	int	std_fd[2];

	*(pid) = fork();
	if (*(pid) == -1)
		exit (error(cmdlst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		std_fd[1] = dup(STDOUT_FILENO);
		std_fd[0] = dup(STDIN_FILENO);
		ft_dup(cmdlst.cmd, pipefd[1][0], STDIN_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(cmdlst, fd_inout, std_fd);
		execution(vars, cmdlst);
		exit(0);
	}
	return (0);
}

int	middle_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid)
{
	int	fd_inout[2];
	int	std_fd[2];
	
	*(pid) = fork();
	if (*(pid) == -1)
		exit (error(cmdlst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		std_fd[1] = dup(STDOUT_FILENO);
		std_fd[0] = dup(STDIN_FILENO);
		ft_dup(cmdlst.cmd, pipefd[0][1], STDOUT_FILENO);
		ft_dup(cmdlst.cmd, pipefd[1][0], STDIN_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(cmdlst, fd_inout, std_fd);
		execution(vars, cmdlst);
	}
	return (0);
}

int	first_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid)
{
	int	fd_inout[2];
	int	std_fd[2];

	*(pid) = fork();
	if (*(pid) == -1)
		return (error(cmdlst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		std_fd[1] = dup(STDOUT_FILENO);
		std_fd[0] = dup(STDIN_FILENO);
		ft_dup(cmdlst.cmd, pipefd[0][1], STDOUT_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(cmdlst, fd_inout, std_fd);
		execution(vars, cmdlst);
		exit(0);
	}
	return (0);
}
