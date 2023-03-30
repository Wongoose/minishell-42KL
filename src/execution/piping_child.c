/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:00:06 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/30 13:43:00 by chenlee          ###   ########.fr       */
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

void	ft_dup_inoutfile(t_pipe cmdlst, int fd_inout[2], int temp)
{
	int	i;

	fd_inout[0] = -42;
	fd_inout[1] = -42;
	i = -1;
	while (++i < cmdlst.rdr_count)
		ft_open(cmdlst.cmd, cmdlst.rdr_info[i], fd_inout, temp);
	// if (cmdlst.infile != NULL)
	// {
	// 	*(fd_in) = open(cmdlst.infile, O_RDWR);
	// if (*(fd_in) == -1 )
	// 	exit(error(cmdlst.cmd, "open error"));
	if (fd_inout[0] != -42)
		ft_dup("infile", fd_inout[0], STDIN_FILENO);
	if (fd_inout[1] != -42)
		ft_dup("outfile", fd_inout[1], STDOUT_FILENO);
	// }
	// if (cmdlst.outfile != NULL)
	// {
	// 	if (check_append(cmdlst.rdr_list))
	// 		*(fd_out) = open(cmdlst.outfile, O_APPEND);
	// 	else
	// 		*(fd_out) = open(cmdlst.outfile, O_RDWR);
	// if (*(fd_out) == -1)
	// 	exit(error(cmdlst.cmd, "open error"));
	// }
}

int	last_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid)
{
	int	fd_inout[2];
	int	temp;

	*(pid) = fork();
	if (*(pid) == -1)
		exit (error(cmdlst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		temp = dup(STDOUT_FILENO);
		ft_dup(cmdlst.cmd, pipefd[1][0], STDIN_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(cmdlst, fd_inout, temp);
		execution(vars, cmdlst);
		exit(0);
	}
	return (0);
}

int	middle_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid)
{
	int	fd_inout[2];
	int	temp;
	
	*(pid) = fork();
	if (*(pid) == -1)
		exit (error(cmdlst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		temp = dup(STDOUT_FILENO);
		ft_dup(cmdlst.cmd, pipefd[0][1], STDOUT_FILENO);
		ft_dup(cmdlst.cmd, pipefd[1][0], STDIN_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(cmdlst, fd_inout, temp);
		execution(vars, cmdlst);
	}
	return (0);
}

int	first_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid)
{
	int	fd_inout[2];
	int	temp;

	*(pid) = fork();
	if (*(pid) == -1)
		return (error(cmdlst.cmd, "fork failed"));
	else if (*(pid) == 0)
	{
		temp = dup(STDOUT_FILENO);
		ft_dup(cmdlst.cmd, pipefd[0][1], STDOUT_FILENO);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		ft_dup_inoutfile(cmdlst, fd_inout, temp);
		execution(vars, cmdlst);
		exit(0);
	}
	return (0);
}
