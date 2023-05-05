/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:12:27 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/05 19:32:02 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar(t_vars *vars, t_pipe *cmdlst)
{
	int		i;
	char	*str;

	str = ft_strdup(cmdlst->arg[0]);
	i = 0;
	while (cmdlst->arg[++i] != NULL)
		str = join_str(str, ft_strdup(" "), ft_strdup(cmdlst->arg[i]));
	if (ft_strchr(str, '$') || ft_strchr(str, '*'))
		str = expand_env_dollar(vars, str);
	free_doublearray(cmdlst->arg);
	cmdlst->arg = split_keep_quotes(str);
	i = -1;
	while (cmdlst->arg[++i])
		cmdlst->arg[i] = exclude_quotes(cmdlst->arg[i]);
	free(cmdlst->cmd);
	cmdlst->cmd = ft_strdup(cmdlst->arg[0]);
}
