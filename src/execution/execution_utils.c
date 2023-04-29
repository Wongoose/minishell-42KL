/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:39:09 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/28 22:28:58 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*join_str(char *front, char *middle, char *rear)
// {
// 	char	*temp;
// 	char	*ret;

// 	temp = ft_strjoin(front, middle);
// 	if (front)
// 		free(front);
// 	if (middle)
// 		free(middle);
// 	if (rear)
// 	{
// 		ret = ft_strjoin(temp, rear);
// 		free(temp);
// 		free(rear);
// 	}
// 	else
// 	{
// 		ret = ft_strdup(temp);
// 		free(temp);
// 	}
// 	return (ret);
// }

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
		if (WIFEXITED(status))
			vars->last_errno = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				vars->last_errno = 130;
		}
	}
}

int	open_loop(t_pipe cmdlst, int fd[2])
{
	int	i;

	i = -1;
	while (++i < cmdlst.rdr_count)
	{
		if (fd[0] != -2)
			close(fd[0]);
		if (cmdlst.rdr_info[i].rdr_type == OUT)
			fd[0] = open(cmdlst.rdr_info[i].rdr_str, O_CREAT | O_TRUNC | O_RDWR,
						S_IRWXU | S_IRGRP | S_IROTH);
		else if (cmdlst.rdr_info[i].rdr_type == APPEND)
			fd[0] = open(cmdlst.rdr_info[i].rdr_str, O_CREAT | O_APPEND | O_RDWR,
						S_IRWXU | S_IRGRP | S_IROTH);
		if (fd[0] == -1)
			return (error(cmdlst.cmd, "No such file or directory"));
	}
	return (0);
}

int	inout_execute(t_vars *vars, t_pipe cmdlst, int num)
{
	int	fd[2];

	fd[0] = -2;
	fd[1] = dup(STDOUT_FILENO);
	if (open_loop(cmdlst, fd) == 1)
		return (1);
	if (fd[0] != -2)
		ft_dup(cmdlst.cmd, fd[0], STDOUT_FILENO);
	vars->func[num](vars, cmdlst.arg);
	close(fd[0]);
	ft_dup(cmdlst.cmd, fd[1], STDOUT_FILENO);
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
int	do_builtin(t_vars *vars, t_pipe cmdlst)
{
	int	num;
	
	num = -1;
	if (ft_strncmp(cmdlst.cmd, "cd", 3) == 0)
		num = 1;
	else if (ft_strncmp(cmdlst.cmd, "export", 7) == 0)
		num = 3;
	else if (ft_strncmp(cmdlst.cmd, "unset", 6) == 0)
		num = 4;
	else if (ft_strncmp(cmdlst.cmd, "exit", 5) == 0)
		num = 6;
	if (num == -1)
		return (-1);
	else
		return (inout_execute(vars, cmdlst, num));
}
