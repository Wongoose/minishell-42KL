/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:46:29 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/01 17:45:21 by chenlee          ###   ########.fr       */
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

char	**handle_heredoc(t_vars *vars, t_token *group)
{
	int		i;
	int		ret;
	char	**hdoc_str;

	ret = 0;
	hdoc_str = ft_calloc(group->pipe_num + 1, sizeof(char *));
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
		return (free(hdoc_str), NULL);
	return (hdoc_str);
}
