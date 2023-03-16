/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:22:23 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/16 14:18:26 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_pipe
{
	char	*infile;
	char	*outfile;
	char	*cmd;
	char	*arguments;
}			t_pipe;

int	error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	execution(t_vars *vars, t_pipe cmdlst)
{
	int		i;

	i = -1;
	while (vars->path[++i] != NULL)
	{
		if (execve(vars->path[i], cmdlst))
	}
}

int	first_child(t_vars *vars, t_pipe cmdlst, int pipefd[2], pid_t *pid)
{
	int		fd;

	*(pid) = fork();
	if (*(pid) == -1)
		return (error("fork failed"));
	else if (*(pid) == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (error("dup failed"));
		close(pipefd[1]);
		if (cmdlst.outfile != NULL)
			fd = open(cmdlst.outfile, O_RDWR);
		if (fd == -1)
			return (error("open failed"));
		execution(vars, cmdlst);
	}
}

int	piping(t_vars *vars, t_pipe *cmdlst, int n_cmds)
{
	int		pipefd[2];
	int		i;
	pid_t	pid;

	i = -1;
	pid = 0;
	while (++i < n_cmds)
	{
		if (pipe(pipefd) == -1)
			return (error("pipe failed"));
		if (i == 0 && first_child(vars, cmdlst[i], pipefd, &pid))
			return (1);
		else if (i == n_cmds - 1 && last_child(vars, cmdlst[i], pipefd, &pid))
			return (1);
		else if (middle_child(vars, cmdlst[i], pipefd, &pid))
			return (1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
}
