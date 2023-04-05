/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:46:29 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/05 18:16:25 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_readline(char *rdr_str)
{
	char	*temp_one;
	char	*temp_two;
	char	*str;

	str = ft_strdup("");
	while (1)
	{
		temp_one = readline("> ");
		if (ft_strncmp(temp_one, rdr_str, ft_strlen(rdr_str)) == 0)
			break ;
		temp_two = ft_strjoin(temp_one, "\n");
		free(temp_one);
		temp_one = ft_strjoin(str, temp_two);
		free(str);
		free(temp_two);
		str = ft_strdup(temp_one);
		free(temp_one);
	}
	return (str);
}

char	*handle_per_cmdlst(t_pipe cmdlst)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = -1;
	while (++i < cmdlst.rdr_count)
	{
		if (cmdlst.rdr_info[i].rdr_type == HEREDOC)
		{
			if (ret != NULL)
				free(ret);
			ret = get_readline(cmdlst.rdr_info[i].rdr_str);
		}
	}
	return (ret);
}

char	**handle_heredoc(t_token *group)
{
	int					i;
	char				**hdoc_str;

	hdoc_str = ft_calloc(group->pipe_num, sizeof(char *));
	i = -1;
	while (++i < group->pipe_num)
		hdoc_str[i] = handle_per_cmdlst(group->cmdlst[i]);
	return (hdoc_str);
}
