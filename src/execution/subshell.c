/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:41:58 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/03 22:19:01 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_subshell_pid(t_vars *vars, int *pid)
{
	int	status;

	if (waitpid(*(pid), &status, 0) == -1)
		error("subshell", "waitpid failed");
	else if (WIFEXITED(status))
		vars->last_errno = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			vars->last_errno = 130;
	}
}

void	start_subshell(t_vars *vars, t_token *group, t_pipe cmdlst, char **envp)
{
	t_vars	new_vars;
	pid_t	new_pid;

	(void)group;
	(void)vars;
	init_vars(&new_vars, envp);
	new_vars.is_subshell = TRUE;
	new_vars.tokens = tokenize_input(&new_vars, cmdlst.cmd);
	ft_fork(&new_pid);
	if (new_pid == 0)
		start_minishell(&new_vars, new_vars.tokens);
	else
		wait_subshell_pid(&new_vars, &new_pid);
	// ft_free_tree(new_vars.tokens, 0);
	ft_free_vars(&new_vars);
	exit (new_vars.last_errno);
}
