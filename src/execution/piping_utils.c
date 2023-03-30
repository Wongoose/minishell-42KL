/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:22:35 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/30 13:46:27 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int	wait_heredoc_pid(char *cmd, int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (error(cmd, "waitpid failed"));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else
		return (-1);
}

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

char	*get_readline(char *rdr_str)
{
	char	*temp_one;
	char	*temp_two;
	char	*str;

	str = ft_strdup("");
	while (1)
	{
		write(2, "while runs\n", 11);
		temp_one = readline("> ");
		if (ft_strncmp(temp_one, rdr_str, ft_strlen(rdr_str)) == 0)
		{
			write(2, "breaking\n", 9);
			break ;
		}
		write(2, "pass strncmp\n", 13);
		temp_two = ft_strjoin(temp_one, "\n");
		free(temp_one);
		temp_one = ft_strjoin(str, temp_two);
		free(str);
		free(temp_two);
		str = ft_strdup(temp_one);
		free(temp_one);
	}
	write(2, "BRUH\n", 5);
	return (str);
}

int	do_heredoc(char *cmd, t_rdrinfo info, int temp)
{
	char	*gnl;
	int		hdoc_pid;
	int		current_fd;
	int		pipefd[2];
	
	if (pipe(pipefd) == -1)
		exit(error(NULL, "pipe failed"));
	hdoc_pid = fork();
	if (hdoc_pid == -1)
		exit(error(cmd, "heredoc fork failed"));
	else if (hdoc_pid == 0)
	{
		current_fd = dup(STDOUT_FILENO);
		ft_dup(cmd, temp, STDOUT_FILENO);
		gnl = get_readline(info.rdr_str);
		ft_dup(cmd, current_fd, STDOUT_FILENO);
		write(pipefd[1], gnl, ft_strlen(gnl));
		close(pipefd[1]);
		exit(0);
	}
	else
		if (wait_heredoc_pid(cmd, hdoc_pid) != 0)
			return (-1);
	return (pipefd[0]);
}

void	ft_open(char *cmd, t_rdrinfo info, int fd_inout[2], int temp)
{
	if ((info.rdr_type == IN || info.rdr_type == HEREDOC))
	{
		if (fd_inout[0] != -42)
			close(fd_inout[0]);
		if (info.rdr_type == IN)
			fd_inout[0] = open(info.rdr_str, O_RDONLY);
		else if (info.rdr_type == HEREDOC)
		{
			write(2, "heredoc runs\n", 13);
			fd_inout[0] = do_heredoc(cmd, info, temp);
		}
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
