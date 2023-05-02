/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:41:58 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/30 17:08:09 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_subshell_pid(int *pid)
{
	int	status;

	if (waitpid(*(pid), &status, 0) == -1)
		error("subshell", "waitpid failed");
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (130);
	}
	return (-1);
}

void	start_subshell(t_vars *vars, t_token *group, t_pipe cmdlst, char **envp)
{
	t_vars	new_vars;
	pid_t	new_pid;
	int		ret;

	(void)group;
	(void)vars;
	ret = 0;
	init_vars(&new_vars, envp);
	new_vars.is_subshell = TRUE;
	new_vars.tokens = tokenize_input(&new_vars, cmdlst.cmd);
	ft_fork(&new_pid);
	if (new_pid == 0)
		start_minishell(&new_vars, new_vars.tokens);
	else
		ret = wait_subshell_pid(&new_pid);
	ft_free_tree(new_vars.tokens, 0);
	ft_free_vars(&new_vars);
	exit (ret);
}
