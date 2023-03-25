/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:22:23 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/25 18:13:04 by chenlee          ###   ########.fr       */
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
	else
		printf("%s\n", str);
	return (1);
}

int	wait_for_pid(t_token group, int *pid, int n_cmds)
{
	int	status;
	int	i;

	i = -1;
	while (++i < n_cmds)
	{
		if (waitpid(pid[i], &status, 0) == -1)
			return (error(group.cmdlst[i].cmd, "waitpid"));
		// if (WEXITSTATUS(status) != 0)
		// 	return (error(vars->cmdlst[i].cmd, "Child process terminated abnormally"));
	}
	return (0);
}

int	multiple_child(t_vars *vars, t_token group, int *pid)
{	
	int	pipefd[2][2];
	int	i;
	int	ret;

	i = -1;
	while (++i < group.pipe_num)
	{
		if (i < group.pipe_num - 1 && pipe(pipefd[0]) == -1)
			return (error(group.cmdlst[i].cmd, "pipe failed"));
		if (i == 0)
			ret = first_child(vars, group.cmdlst[i], pipefd, &pid[i]);
		else if (i == group.pipe_num - 1)
			ret = last_child(vars, group.cmdlst[i], pipefd, &pid[i]);
		else
			ret = middle_child(vars, group.cmdlst[i], pipefd, &pid[i]);
		if (ret == 1)
			return (1);
		ft_close_pipe(i, group.pipe_num, pipefd);
	}
	return (0);
}

int	one_child(t_vars *vars, t_pipe cmdlst, pid_t *pid)
{
	int	fd_in;
	int	fd_out;

	pid[0] = fork();
	if (pid[0] == -1)
		exit (error(cmdlst.cmd, "fork failed"));
	else if (pid[0] == 0)
	{
		write(2, "runs\n", 5);
		ft_dup_inoutfile(cmdlst, &fd_in, &fd_out);
		execution(vars, cmdlst);
		exit(0);
	}
	return (0);
}

int	cmdgroup(t_vars *vars, t_token group)
{
	int		ret;
	int		ret_pid;
	pid_t	*pid;

	ret = 0;
	ret_pid = 0;
	pid = ft_calloc(group.pipe_num, sizeof(int));
	if (group.pipe_num == 1)
		ret = one_child(vars, group.cmdlst[0], pid);
	else
	{
		ret = multiple_child(vars, group, pid);
		ret_pid = wait_for_pid(group, pid, group.pipe_num);
	}
	if (ret == 1 || ret_pid == 1)
	{
		free(pid);
		return (1);
	}
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
