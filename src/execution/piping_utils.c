/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:22:35 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/31 19:54:00 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_in_next(t_token group, int index)
{
	int	i;

	i = index + 1;
	while (i < group.pipe_num)
	{
		if (group.cmdlst[i].rdr_info->rdr_type == 3)
			return (1);
		i++;
	}
	return (0);
}

void	ft_kill(int index, int total_num, t_pipe *cmdlst)
{
	if (index < total_num - 1)
	{
		dprintf(2, "killing pid=%d\n", cmdlst[index + 1].rdr_info->rdr_pid);
		kill(cmdlst[index + 1].rdr_info->rdr_pid, SIGUSR1);
		usleep(10000);
	}
}

int	error(char *cmd, char *str)
{
	if (cmd != NULL)
		printf("%s: %s\n", cmd, str);
	else
		printf("%s\n", str);
	return (1);
}

void	ft_open(int i, char *cmd, t_rdrinfo info, int rdr_inout[2][2])
{
	if ((info.rdr_type == IN || info.rdr_type == HEREDOC))
	{
		if (rdr_inout[0][0] != -42)
			close(rdr_inout[0][0]);
		if (info.rdr_type == IN)
			rdr_inout[0][0] = open(info.rdr_str, O_RDONLY);
		else if (info.rdr_type == HEREDOC)
			rdr_inout[0][0] = do_heredoc(i, cmd, info, rdr_inout[1]);
		if (rdr_inout[0][0] == -1)
			exit(error(cmd, "open error"));
	}
	else if ((info.rdr_type == OUT || info.rdr_type == APPEND))
	{
		if (rdr_inout[0][1] != -42)
			close(rdr_inout[0][1]);
		if (info.rdr_type == OUT)
			rdr_inout[0][1] = open(info.rdr_str, O_CREAT | O_TRUNC | O_RDWR,
					S_IRWXU | S_IRGRP | S_IROTH);
		else if (info.rdr_type == APPEND)
			rdr_inout[0][1] = open(info.rdr_str, O_CREAT | O_APPEND | O_RDWR,
					S_IRWXU | S_IRGRP | S_IROTH);
		if (rdr_inout[0][1] == -1)
			exit(error(cmd, "open error"));
	}
}

// void	ft_dup_inoutfile(int i, t_pipe cmdlst, int fd_inout[2], int std_fd[2])
void	ft_dup_inoutfile(int i, t_pipe cmdlst, int rdr_inout[2][2])
{
	int	j;

	rdr_inout[0][0] = -42;
	rdr_inout[0][1] = -42;
	j = -1;
	while (++j < cmdlst.rdr_count)
		ft_open(i, cmdlst.cmd, cmdlst.rdr_info[j], rdr_inout);
	if (rdr_inout[0][0] != -42)
		ft_dup("infile", rdr_inout[0][0], STDIN_FILENO);
	if (rdr_inout[0][1] != -42)
		ft_dup("outfile", rdr_inout[0][1], STDOUT_FILENO);
	close(rdr_inout[0][0]);
	close(rdr_inout[0][1]);
}
