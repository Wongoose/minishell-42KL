/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:41:58 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/21 14:02:49 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_subshell(t_pipe cmdlst, char **envp)
{
	t_vars	vars;

	init_vars(&vars, envp);
	vars.tokens = tokenize_input(&vars, cmdlst.cmd);
	vars.is_subshell = TRUE;
	start_minishell(&vars, vars.tokens);
	exit(0);
}
