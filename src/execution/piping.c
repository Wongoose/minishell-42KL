/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:22:23 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/03 15:40:23 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int	wait_for_pid(t_vars *vars, t_token *group, int *pid)
{
	int	status;
	int	i;

	i = -1;
	while (++i < group->pipe_num)
	{
		if (waitpid(pid[i], &status, 0) == -1)
			return (error(group->cmdlst[i].cmd, "waitpid failed"));
		if (WIFEXITED(status))
		{
			vars->last_errno = WEXITSTATUS(status);
			return (vars->last_errno);
		}
		else if (WIFSIGNALED(status))
		{
			vars->last_errno = WTERMSIG(status);
			return (vars->last_errno);
		}
	}
	return (0);
}

void	ft_fork(char *cmd, int *pid)
{
	*(pid) = fork();
	if (*(pid) == -1)
		exit (error(cmd, "fork failed"));
}

int	multiple_child(t_vars *vars, t_token *group, int *pid)
{	
	int	pipefd[2][2];
	int	i;

	i = -1;
	while (++i < group->pipe_num)
	{
		if (i < group->pipe_num && pipe(pipefd[0]) == -1)
			return (error(group->cmdlst[i].cmd, "pipe failed"));
		ft_fork(group->cmdlst[i].cmd, &(pid[i]));
		if (pid[i] == 0)
		{
			if (i == 0)
				first_child(vars, group, i, pipefd);
			else if (i == group->pipe_num - 1)
				last_child(vars, group, i, pipefd);
			else
				middle_child(vars, group, i, pipefd);
		}
		else
			ft_close_pipe(i, group->pipe_num, pipefd);
	}
	return (0);
}

int	one_child(t_vars *vars, t_token *group, pid_t *pid)
{
	int	rdr_inout[2];

	pid[0] = fork();
	if (pid[0] == -1)
		exit (error(group->cmdlst[0].cmd, "fork failed"));
	else if (pid[0] == 0)
	{
		ft_dup_inoutfile(0, group->cmdlst[0], group->hdoc_str, rdr_inout);
		execution(vars, group->cmdlst[0]);
		exit(0);
	}
	return (0);
}

int	cmdgroup(t_vars *vars, t_token *group)
{
	int		ret;
	int		ret_pid;
	pid_t	*pid;

	ret = 0;
	ret_pid = 0;
	pid = ft_calloc(group->pipe_num, sizeof(int));
	group->hdoc_str = handle_heredoc(group);
	if (group->pipe_num == 1)
		ret = one_child(vars, group, pid);
	else
		ret = multiple_child(vars, group, pid);
	ret_pid = wait_for_pid(vars, group, pid);
	free(pid);
	if (ret == 1 || ret_pid == 1)
		return (1);
	return (0);
}

// t_redirect	init_rdrlst(char *rdr)
// {
// 	t_redirect	ret;
// 	int			i;
// 	char		**lmao;

// 	lmao = ft_split(rdr);
// 	i = -1;
// 	while (lmao[++i] != NULL)
// 	{
		
// 	}
// 	free(lmao);
// 	return (ret);
// }

// t_pipe	bruh(char *in, char *out, char *cmd, char *arg, t_bool has_red, char *rdr)
// {
// 	t_pipe	ret;

// 	ret.infile = in;
// 	ret.outfile = out;
// 	ret.cmd = cmd;
// 	ret.arg = ft_split(arg, ' ');
// 	ret.rdr_list = init_rdrlst(rdr);
// 	return (ret);
// }

// void	test_piping(t_vars *vars)
// {
// 	vars->cmdlst = ft_calloc(10, sizeof(t_pipe));
// 	vars->cmdlst[0] = bruh(NULL, "outfile", "ls", "ls -l src/", 0, "NULL");
// 	vars->cmdlst[1] = bruh("infile", "outfile", "cat", "cat", 0, "NULL");
// 	// vars->cmdlst[2] = bruh(NULL, NULL, "cat", "cat", 0, -1);
// 	// vars->cmdlst[1] = bruh(NULL, NULL, "wc", "wc -l", 0, -1);
// 	piping(vars, 2);
// }
