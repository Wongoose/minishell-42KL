/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:22:23 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/05 18:02:11 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 * The forking function for child pids.
 * 
 * @param pid The pointer to an int that will store the process id upon forking.
 * @return Function does not return.
*/
void	ft_fork(int *pid)
{
	*(pid) = fork();
	if (*(pid) == -1)
		perror("fork");
}

/**
 * Function will be called if the command group has pipes (eg: cmd1 | cmd2),
 * where function will loop through the command group and execute them through
 * a loop. Seperate functions will be called to execute every command inside the
 * group, as the fd duping will be different (From above-mentioned example,
 * "cmd1" should dup the STDOUT_FILENO to the writing end of the pipe; and
 * "cmd2" should dup the STDIN_FILENO to the reading end of the pipe instead).
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param group The current token tree containing its command group
 * @param pid The process ids to keep track of its child process
 * @return Function does not return
*/
void	multiple_child(t_vars *vars, t_token *group, int *pid)
{	
	int	pipefd[2][2];
	int	i;

	i = -1;
	while (++i < group->pipe_num)
	{
		if (i < group->pipe_num && pipe(pipefd[0]) == -1)
			exit (error(group->cmdlst[i].cmd, "pipe failed"));
		ft_fork(&(pid[i]));
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

/**
 * Function will be called if the command group has no pipes (eg: cmd1).
 * If the command is of built-in functions (cd, export, unset, exit), the
 * execution will be handled seperately in the parent process; otherwise,
 * fork a child process to handle other commands.
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param group The current token tree containing its command group
 * @param pid The process id to keep track of its child process
 * @return Function will only returns if the command is of the said built-in
 * functions, whereby the execution should be done in parent process, requiring
 * proper handling of the execution process
*/
int	one_child(t_vars *vars, t_token *group, pid_t *pid)
{
	int	ret;
	int	rdr_inout[2];

	if (group->cmdlst[0].has_subshell != TRUE)
	{
		ret = 0;
		if (group->cmdlst[0].cmd != NULL)
			ret = do_builtin(vars, &group->cmdlst[0]);
		if (ret != -1)
			return (ret);
	}
	ft_fork(&pid[0]);
	if (pid[0] == 0)
	{
		ft_dup_inoutfile(0, group->cmdlst[0], group->hdoc_str, rdr_inout);
		if (group->cmdlst[0].has_subshell == TRUE)
			start_subshell(vars, group, group->cmdlst[0], vars->envp);
		else
			execution(vars, &group->cmdlst[0]);
	}
	return (-1);
}

/**
 * Function marks the start of the piping/execution process, whereby heredocs
 * are first handled and parsed into string array, along with allocating
 * memories for the pids that will be used for forking child processes.
 * Next, function determines if the command group doesn't contain any pipes
 * (eg: cmd1) or pipes are present (eg: cmd1 | cmd2) and will call respective
 * functions to handle them.
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param group The current token tree containing its command group
 * @return Function will only returns if the command is of the built-in
 * functions (cd, export, unset, exit), whereby the execution should be done
 * in parent process, requiring proper handling of the execution process.
 * Returns 0 if command is exit, which should stop the minishell program,
 * otherwise returns 1.
*/
int	cmdgroup(t_vars *vars, t_token *group)
{
	pid_t	*pid;
	int		ret;

	vars->path = extract_path(vars->path, vars->envp);
	ret = -1;
	signal(SIGINT, SIG_IGN);
	group->hdoc_str = handle_heredoc(vars, group);
	if (group->hdoc_str == NULL)
	{
		vars->last_errno = 0;
		return (-2);
	}
	pid = ft_calloc(group->pipe_num, sizeof(int));
	if (group->pipe_num == 1)
		ret = one_child(vars, group, pid);
	else
		multiple_child(vars, group, pid);
	if (ret == -1)
		wait_for_pid(vars, group, pid);
	free(pid);
	return (ret);
}
