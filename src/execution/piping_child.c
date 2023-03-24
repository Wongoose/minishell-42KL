/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:00:06 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/24 19:28:54 by chenlee          ###   ########.fr       */
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

void	ft_dup_inoutfile(t_pipe pipelst, int *fd_in, int *fd_out)
{
	int	i;

	*(fd_in) = -42;
	*(fd_out) = -42;
	i = -1;
	while (++i < pipelst.rdr_count)
		ft_open(pipelst.cmd, pipelst.rdr_info[i], fd_in, fd_out);
	// if (pipelst.infile != NULL)
	// {
	// 	*(fd_in) = open(pipelst.infile, O_RDWR);
	// if (*(fd_in) == -1 )
	// 	exit(error(pipelst.cmd, "open error"));
	if (*(fd_in) != -42)
		ft_dup("infile", *(fd_in), STDIN_FILENO);
	if (*(fd_out) != -42)
		ft_dup("outfile", *(fd_out), STDOUT_FILENO);
	// }
	// if (pipelst.outfile != NULL)
	// {
	// 	if (check_append(pipelst.rdr_list))
	// 		*(fd_out) = open(pipelst.outfile, O_APPEND);
	// 	else
	// 		*(fd_out) = open(pipelst.outfile, O_RDWR);
	// if (*(fd_out) == -1)
	// 	exit(error(pipelst.cmd, "open error"));
	// }
}

int	last_child(t_vars *vars, t_pipe pipelst, int pipefd[2][2], pid_t *pid)
{
	int	fd_in;
	int	fd_out;

	*(pid) = fork();
	if (*(pid) == -1)
		exit (error(pipelst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		ft_dup(pipelst.cmd, pipefd[1][0], STDIN_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(pipelst, &fd_in, &fd_out);
		execution(vars, pipelst);
		exit(0);
	}
	return (0);
}

int	middle_child(t_vars *vars, t_pipe pipelst, int pipefd[2][2], pid_t *pid)
{
	int	fd_in;
	int	fd_out;
	
	*(pid) = fork();
	if (*(pid) == -1)
		exit (error(pipelst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		ft_dup(pipelst.cmd, pipefd[0][1], STDOUT_FILENO);
		ft_dup(pipelst.cmd, pipefd[1][0], STDIN_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(pipelst, &fd_in, &fd_out);
		execution(vars, pipelst);
	}
	return (0);
}

int	first_child(t_vars *vars, t_pipe pipelst, int pipefd[2][2], pid_t *pid)
{
	int	fd_in;
	int	fd_out;

	*(pid) = fork();
	if (*(pid) == -1)
		return (error(pipelst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		ft_dup(pipelst.cmd, pipefd[0][1], STDOUT_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(pipelst, &fd_in, &fd_out);
		execution(vars, pipelst);
		exit(0);
	}
	return (0);
}
