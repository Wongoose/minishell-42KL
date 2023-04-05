/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:22:35 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/05 18:52:24 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(char *cmd, char *str)
{
	if (cmd != NULL)
		printf("%s: %s\n", cmd, str);
	else
		printf("%s\n", str);
	return (1);
}

int	do_heredoc(int i, char **hdoc)
{
	int	fd[2];

	if (pipe(fd) == -1)
		exit(error(NULL, "Heredoc: pipe failed"));
	write(fd[1], hdoc[i], ft_strlen(hdoc[i]));
	close(fd[1]);
	return (fd[0]);
}

void	ft_open(int i, t_rdrinfo info, char **hdoc, int rdr_inout[2])
{
	if ((info.rdr_type == IN || info.rdr_type == HEREDOC))
	{
		if (rdr_inout[0] != -42)
			close(rdr_inout[0]);
		if (info.rdr_type == IN)
			rdr_inout[0] = open(info.rdr_str, O_RDONLY);
		else if (info.rdr_type == HEREDOC)
			rdr_inout[0] = do_heredoc(i, hdoc);
		if (rdr_inout[0] == -1)
			exit(error(info.rdr_str, "No such file or directory"));
	}
	else if ((info.rdr_type == OUT || info.rdr_type == APPEND))
	{
		if (rdr_inout[1] != -42)
			close(rdr_inout[1]);
		if (info.rdr_type == OUT)
			rdr_inout[1] = open(info.rdr_str, O_CREAT | O_TRUNC | O_RDWR,
					S_IRWXU | S_IRGRP | S_IROTH);
		else if (info.rdr_type == APPEND)
			rdr_inout[1] = open(info.rdr_str, O_CREAT | O_APPEND | O_RDWR,
					S_IRWXU | S_IRGRP | S_IROTH);
		if (rdr_inout[1] == -1)
			exit(error(info.rdr_str, "No such file or directory"));
	}
}

// void	ft_dup_inoutfile(int i, t_pipe cmdlst, int fd_inout[2], int std_fd[2])
void	ft_dup_inoutfile(int i, t_pipe cmdlst, char **hdoc, int rdr_inout[2])
{
	int	j;

	rdr_inout[0] = -42;
	rdr_inout[1] = -42;
	j = -1;
	while (++j < cmdlst.rdr_count)
		ft_open(i, cmdlst.rdr_info[j], hdoc, rdr_inout);
	if (rdr_inout[0] != -42)
		ft_dup("infile", rdr_inout[0], STDIN_FILENO);
	if (rdr_inout[1] != -42)
		ft_dup("outfile", rdr_inout[1], STDOUT_FILENO);
	close(rdr_inout[0]);
	close(rdr_inout[1]);
}
