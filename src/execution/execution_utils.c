/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:39:09 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/05 19:33:52 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extract_path(char **path, char **envp)
{
	char	*str;
	char	**path_arr;
	char	**new_path;
	int		i;

	if (path != NULL)
		free_doublearray(path);
	str = get_envp_value(envp, ft_strdup("PATH"));
	if (str == NULL)
		return (NULL);
	else
	{
		path_arr = ft_split(str, ':');
		i = 0;
		while (path_arr[i])
			i++;
		new_path = (char **)ft_calloc(i + 2, sizeof(char *));
		i = -1;
		while (path_arr[++i] != NULL)
			new_path[i] = ft_strdup(path_arr[i]);
		free_doublearray(path_arr);
		new_path[i] = ft_strdup("");
		return (new_path);
	}
}

/**
 * Function waits for child processes with specified pids. Calls waitpid system
 * call which suspends execution of the current process until all the childrens
 * terminates. Function then updates the last exit status in the vars struct
 * using WIFEXITED if the child process exit normally, or WTERMSIG if a signal
 * caused the child process to terminate.
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param group The current token tree containing its command group
 * @param pid The process id to keep track of its child process
 * 
 * @return Function does not return
*/
void	wait_for_pid(t_vars *vars, t_token *group, int *pid)
{
	int	status;
	int	i;

	i = -1;
	while (++i < group->pipe_num)
	{
		if (group->cmdlst[i].cmd == NULL)
			return ;
		if (waitpid(pid[i], &status, 0) == -1)
			error(group->cmdlst[i].cmd, "waitpid failed");
		else if (WIFEXITED(status))
			vars->last_errno = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2 || WTERMSIG(status) == 3)
				vars->last_errno = 130 + WTERMSIG(status) - 2;
			else
				vars->last_errno = WTERMSIG(status);
		}
	}
}

/**
 * ft_open for specific built-in functions.
*/
int	open_loop(t_pipe *cmdlst, int fd[2])
{
	int	i;

	i = -1;
	while (++i < cmdlst->rdr_count)
	{
		if (fd[0] != -2)
			close(fd[0]);
		if (cmdlst->rdr_info[i].rdr_type == OUT)
			fd[0] = open(cmdlst->rdr_info[i].rdr_str,
					O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
		else if (cmdlst->rdr_info[i].rdr_type == APPEND)
			fd[0] = open(cmdlst->rdr_info[i].rdr_str,
					O_CREAT | O_APPEND | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
		if (fd[0] == -1)
			return (error(cmdlst->cmd, "No such file or directory"));
	}
	return (0);
}

/**
 * Execution for specific built-in functions (cd, export, unset, exit).
 * Similar to normal execution, but modified to be run on parent process.
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param cmdlst The struct containing information of current command group,
 * including command and arguments, redirections, etc.
 * @param num The number that denotes the specific function for execution.
 * 
 * @return Function returns 0 if the built-in function is "exit", otherwise,
 * returns 1
*/
int	inout_execute(t_vars *vars, t_pipe *cmdlst, int num)
{
	int	fd[2];

	fd[0] = -2;
	fd[1] = dup(STDOUT_FILENO);
	if (open_loop(cmdlst, fd) == 1)
		return (1);
	if (fd[0] != -2)
		ft_dup(cmdlst->cmd, fd[0], STDOUT_FILENO);
	handle_dollar(vars, cmdlst);
	vars->func[num](vars, cmdlst->arg);
	close(fd[0]);
	ft_dup(cmdlst->cmd, fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (num == 6)
		return (0);
	else
		return (1);
}

/**
 * Function checks for certain built-in functions that are necessary to be run
 * on the parent process, since these functions will manipulate the current
 * behavior of the minishell program environment, and any manipulation ran in a
 * child process with fork will not reflect to the main program.
 * 
 * @param vars The main struct of the program containing the main tree
 * @param cmdlst The group of commands, which can either be a single command,
 * or multiple made up of several pipe members, but not compare operators
 * (&& or ||)
 * 
 * @return If the command parsed is not in the list of specific built-in, return
 * -1; else, returns 0 if command is exit, which should stop the minishell
 * program, otherwise returns 1.
*/
int	do_builtin(t_vars *vars, t_pipe *cmdlst)
{
	int	num;

	num = -1;
	if (ft_strncmp(cmdlst->cmd, "cd", 3) == 0)
		num = 1;
	else if (ft_strncmp(cmdlst->cmd, "export", 7) == 0)
		num = 3;
	else if (ft_strncmp(cmdlst->cmd, "unset", 6) == 0)
		num = 4;
	else if (ft_strncmp(cmdlst->cmd, "exit", 5) == 0)
		num = 6;
	if (num == -1)
		return (-1);
	else
		return (inout_execute(vars, cmdlst, num));
}
