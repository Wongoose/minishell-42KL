/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:41:58 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/28 22:16:55 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_subshell(t_vars *vars, t_token *group, t_pipe cmdlst, char **envp)
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
		wait_for_pid(&new_vars, new_vars.tokens, &new_pid);
	exit (new_vars.last_errno);
}
