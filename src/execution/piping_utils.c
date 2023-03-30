/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:22:35 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/30 19:37:47 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void	ft_open(char *cmd, t_rdrinfo info, int fd_inout[2], int std_fd[2])
{
	if ((info.rdr_type == IN || info.rdr_type == HEREDOC))
	{
		if (fd_inout[0] != -42)
			close(fd_inout[0]);
		if (info.rdr_type == IN)
			fd_inout[0] = open(info.rdr_str, O_RDONLY);
		else if (info.rdr_type == HEREDOC)
			fd_inout[0] = do_heredoc(cmd, info, std_fd);
		if (fd_inout[0] == -1)
			exit(error(cmd, "open error"));
	}
	else if ((info.rdr_type == OUT || info.rdr_type == APPEND))
	{
		if (fd_inout[1] != -42)
			close(fd_inout[1]);
		if (info.rdr_type == OUT)
			fd_inout[1] = open(info.rdr_str, O_CREAT | O_TRUNC | O_RDWR,
					S_IRWXU | S_IRGRP | S_IROTH);
		else if (info.rdr_type == APPEND)
			fd_inout[1] = open(info.rdr_str, O_CREAT | O_APPEND | O_RDWR,
					S_IRWXU | S_IRGRP | S_IROTH);
		if (fd_inout[1] == -1)
			exit(error(cmd, "open error"));
	}
}

void	ft_dup_inoutfile(t_pipe cmdlst, int fd_inout[2], int std_fd[2])
{
	int	i;

	fd_inout[0] = -42;
	fd_inout[1] = -42;
	i = -1;
	while (++i < cmdlst.rdr_count)
		ft_open(cmdlst.cmd, cmdlst.rdr_info[i], fd_inout, std_fd);
	if (fd_inout[0] != -42)
		ft_dup("infile", fd_inout[0], STDIN_FILENO);
	if (fd_inout[1] != -42)
		ft_dup("outfile", fd_inout[1], STDOUT_FILENO);
	close(fd_inout[0]);
	close(fd_inout[1]);
}
