/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:39:09 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/14 21:22:36 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_str(char *front, char *middle, char *rear)
{
	char	*temp;
	char	*ret;

	temp = ft_strjoin(front, middle);
	free(front);
	free(middle);
	ret = ft_strjoin(temp, rear);
	free(temp);
	free(rear);
	return (ret);
}

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
	return (0);
}

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

// if (ft_strncmp(cmd, "echo", 5) == 0)
// 	num = 0;
// else if (ft_strncmp(cmd, "cd", 3) == 0)
// 	num = 1;
// else if (ft_strncmp(cmd, "pwd", 4) == 0)
// 	num = 2;
// else if (ft_strncmp(cmd, "env", 4) == 0)
// 	num = 5;
