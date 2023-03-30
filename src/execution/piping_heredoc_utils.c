/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:59:27 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/30 19:37:50 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	dup_heredoc(char *cmd, int curr_fd[2], int std_fd[2], int situation)
{
	if (situation == 1)
	{
		curr_fd[0] = dup(STDIN_FILENO);
		curr_fd[1] = dup(STDOUT_FILENO);
		ft_dup(cmd, std_fd[0], STDIN_FILENO);
		ft_dup(cmd, std_fd[1], STDOUT_FILENO);
	}
	else if (situation == 2)
	{
		ft_dup(cmd, curr_fd[0], STDIN_FILENO);
		ft_dup(cmd, curr_fd[1], STDOUT_FILENO);
	}
}

char	*get_readline(char *rdr_str)
{
	char	*temp_one;
	char	*temp_two;
	char	*str;

	str = ft_strdup("");
	while (1)
	{
		temp_one = readline("> ");
		if (ft_strncmp(temp_one, rdr_str, ft_strlen(rdr_str)) == 0)
			break ;
		temp_two = ft_strjoin(temp_one, "\n");
		free(temp_one);
		temp_one = ft_strjoin(str, temp_two);
		free(str);
		free(temp_two);
		str = ft_strdup(temp_one);
		free(temp_one);
	}
	return (str);
}

int	do_heredoc(char *cmd, t_rdrinfo info, int std_fd[2])
{
	char	*gnl;
	int		hdoc_pid;
	int		curr_fd[2];
	int		pipefd[2];
		
	if (pipe(pipefd) == -1)
		exit(error(NULL, "pipe failed"));
	hdoc_pid = fork();
	if (hdoc_pid == -1)
		exit(error(cmd, "heredoc fork failed"));
	else if (hdoc_pid == 0)
	{
		dup_heredoc(cmd, curr_fd, std_fd, 1);
		gnl = get_readline(info.rdr_str);
		dup_heredoc(cmd, curr_fd, std_fd, 2);
		write(pipefd[1], gnl, ft_strlen(gnl));
		close(pipefd[0]);
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	if (wait_heredoc_pid(cmd, hdoc_pid) >= 0)
		return (pipefd[0]);
	return (-1);
}
