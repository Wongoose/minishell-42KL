/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:41:58 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/19 21:19:18 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_subshell(t_pipe cmdlst, char **envp)
{
	t_vars	vars;
	char	*new_str;

	new_str = ft_substr(cmdlst.cmd, 1, ft_strlen(cmdlst.cmd) - 2);
	init_vars(&vars, envp);
	vars.tokens = tokenize_input(&vars, new_str);
	vars.is_subshell = TRUE;
	start_minishell(&vars, vars.tokens);
	exit(0);
}
