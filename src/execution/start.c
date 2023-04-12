/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:22:23 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/12 16:07:13 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void	ft_fork(char *cmd, int *pid)
{
	*(pid) = fork();
	if (*(pid) == -1)
		exit (error(cmd, "fork failed"));
}

void	multiple_child(t_vars *vars, t_token *group, int *pid)
{	
	int	pipefd[2][2];
	int	i;

	i = -1;
	while (++i < group->pipe_num)
	{
		if (i < group->pipe_num && pipe(pipefd[0]) == -1)
			exit (error(group->cmdlst[i].cmd, "pipe failed"));
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
}

int	one_child(t_vars *vars, t_token *group, pid_t *pid)
{
	int	ret;
	int	rdr_inout[2];

	ret = do_builtin(vars, group->cmdlst[0]);
	if (ret == 1)
		return (2);
	else if (ret == 0)
		return (1);
	else
	{
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
}

int	cmdgroup(t_vars *vars, t_token *group)
{
	pid_t	*pid;
	int		ret;

	ret = 0;
	signal(SIGINT, SIG_IGN);
	pid = ft_calloc(group->pipe_num, sizeof(int));
	group->hdoc_str = handle_heredoc(vars, group);
	if (group->hdoc_str == NULL)
	{
		vars->last_errno = 0;
		return (0);
	}
	if (group->pipe_num == 1)
		ret = one_child(vars, group, pid);
	else
		multiple_child(vars, group, pid);
	if (ret == 0)
		wait_for_pid(vars, group, pid);
	free(pid);
	return (ret);
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
