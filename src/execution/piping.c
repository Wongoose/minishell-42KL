/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:22:23 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/17 21:20:56 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int	error(char *cmd, char *str)
{
	if (cmd != NULL)
		printf("%s: %s\n", cmd, str);
	return (1);
}

int	execution(t_vars *vars, t_pipe cmdlst)
{
	int		i;
	int		ret;
	char	*pathname;
	char	*temp;

	i = -1;
	while (vars->path[++i] != NULL)
	{
		temp = ft_strjoin(vars->path[i], "/");
		pathname = ft_strjoin(temp, cmdlst.cmd);
		ret = execve(pathname, cmdlst.arg, NULL);
		free(temp);
		free(pathname);
		if (ret != -1)
			break ;
	}
	if (vars->path[i] == NULL)
		return (error(cmdlst.cmd, "command not found"));
	return (0);
}

void	ft_dup(char *cmd, int fd_one, int fd_two)
{
	if (dup2(fd_one, fd_two) == -1)
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

	printf("LAST CHILD @ %s\n", cmdlst.cmd);
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

	printf("MIDDLE CHILD @ %s\n", cmdlst.cmd);
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

	printf("FIRST CHILD @ %s\n", cmdlst.cmd);
	*(pid) = fork();
	if (*(pid) == -1)
		exit (error(cmdlst.cmd, "fork failed"));
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

int	piping(t_vars *vars, t_pipe *cmdlst, int n_cmds)
{
	int		pipefd[2][2];
	int		i;
	int		ret;
	pid_t	pid;

	i = -1;
	pid = 0;
	while (++i < n_cmds)
	{
		if (pipe(pipefd[0]) == -1)
			return (error(cmdlst->cmd, "pipe failed"));
		if (i == 0)
			ret = first_child(vars, cmdlst[i], pipefd, &pid);
		else if (i == n_cmds - 1)
			ret = last_child(vars, cmdlst[i], pipefd, &pid);
		else
			ret = middle_child(vars, cmdlst[i], pipefd, &pid);
		if (ret == 1)
			return (1);
		pipefd[1][0] = dup(pipefd[0][0]);
		pipefd[1][1] = dup(pipefd[0][1]);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
	}
	return (0);
}

t_pipe	bruh(char *in, char *out, char *cmd, char *arg, t_bool has_red, t_redirect type)
{
	t_pipe	ret;

	ret.infile = in;
	ret.outfile = out;
	ret.cmd = cmd;
	ret.arg = ft_split(arg, ' ');
	ret.has_redirect = has_red;
	ret.redirect_type = type;
	return (ret);
}

void	test_piping(t_vars *vars)
{
	vars->cmdlst = malloc(sizeof(t_pipe) * 4);
	vars->cmdlst[0] = bruh(NULL, NULL, "cat", "cat", 0, -1);
	vars->cmdlst[1] = bruh(NULL, NULL, "cat", "cat", 0, -1);
	vars->cmdlst[2] = bruh(NULL, NULL, "ls", "ls -l", 0, -1);
	piping(vars, vars->cmdlst, 3);
}
