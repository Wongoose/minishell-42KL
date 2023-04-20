/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:46:29 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/20 01:11:33 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_per_cmdlst(t_vars *vars, t_pipe cmdlst)
{
	int		i;
	char	*ret;

	ret = ft_strdup(" ");
	i = -1;
	while (++i < cmdlst.rdr_count)
	{
		if (cmdlst.rdr_info[i].rdr_type == HEREDOC)
		{
			free(ret);
			ret = get_readline(vars, cmdlst.rdr_info[i].rdr_str);
			if (ret == NULL)
				return (NULL);
		}
	}
	return (ret);
}

// void	dup_heredoc(t_vars *vars, int temp[2], int situation)
// {
// 	if (situation == 1)
// 	{
// 		ft_dup("dup", STDIN_FILENO, temp[0]);
// 		ft_dup("dup", STDOUT_FILENO, temp[1]);
// 		ft_dup("dup", vars->backup_inout[0], STDIN_FILENO);
// 		ft_dup("dup", vars->backup_inout[1], STDOUT_FILENO);
// 	}
// 	else if (situation == 2)
// 	{
// 		ft_dup("dup", temp[0], STDIN_FILENO);
// 		ft_dup("dup", temp[1], STDOUT_FILENO);
// 	}
// }

char	**handle_heredoc(t_vars *vars, t_token *group)
{
	int		i;
	int		ret;
	// int		temp[2];
	char	**hdoc_str;

	ret = 0;
	hdoc_str = ft_calloc(group->pipe_num, sizeof(char *));
	i = -1;
	while (++i < group->pipe_num)
	{
		hdoc_str[i] = handle_per_cmdlst(vars, group->cmdlst[i]);
		if (hdoc_str[i] == NULL)
		{
			ret = 1;
			break ;
		}
	}
	if (ret == 1)
		return (NULL);
	return (hdoc_str);
}
