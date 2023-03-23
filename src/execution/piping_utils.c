/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:00:06 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/23 16:18:29 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

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

void	ft_dup_inoutfile(t_pipe cmdlst, int *fd_in, int *fd_out)
{
	if (cmdlst.infile != NULL)
	{
		*(fd_in) = open(cmdlst.infile, O_RDWR);
		if (*(fd_in) == -1)
			exit(error(cmdlst.cmd, "open error"));
		ft_dup("infile", *(fd_in), STDIN_FILENO);
	}
	if (cmdlst.outfile != NULL)
	{
		if (check_append(cmdlst.rdr_list))
			*(fd_out) = open(cmdlst.outfile, O_APPEND);
		else
			*(fd_out) = open(cmdlst.outfile, O_RDWR);
		if (*(fd_out) == -1)
			exit(error(cmdlst.cmd, "open error"));
		ft_dup("outfile", *(fd_out), STDOUT_FILENO);
	}
}

int	last_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid)
{
	int	fd_in;
	int	fd_out;

	*(pid) = fork();
	if (*(pid) == -1)
		exit (error(cmdlst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		ft_dup(cmdlst.cmd, pipefd[1][0], STDIN_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(cmdlst, &fd_in, &fd_out);
		execution(vars, cmdlst);
		exit(0);
	}
	return (0);
}

int	middle_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid)
{
	int	fd_in;
	int	fd_out;
	
	*(pid) = fork();
	if (*(pid) == -1)
		exit (error(cmdlst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		ft_dup(cmdlst.cmd, pipefd[0][1], STDOUT_FILENO);
		ft_dup(cmdlst.cmd, pipefd[1][0], STDIN_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(cmdlst, &fd_in, &fd_out);
		execution(vars, cmdlst);
	}
	return (0);
}

int	first_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid)
{
	int	fd_in;
	int	fd_out;

	*(pid) = fork();
	if (*(pid) == -1)
		return (error(cmdlst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		ft_dup(cmdlst.cmd, pipefd[0][1], STDOUT_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(cmdlst, &fd_in, &fd_out);
		execution(vars, cmdlst);
		exit(0);
	}
	return (0);
}
