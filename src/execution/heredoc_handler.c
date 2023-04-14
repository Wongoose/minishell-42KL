/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:46:29 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/14 21:22:17 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len(char *temp_one, char *rdr_str)
{
	int	len_one;
	int len_two;

	len_one = ft_strlen(temp_one);
	len_two = ft_strlen(rdr_str);
	if (len_one > len_two)
		return (len_one);
	else
		return (len_two);
}

char	*check_existance(t_vars *vars, char *middle)
{
	int		i;
	char	*ret;
	char	**key_val;

	i = -1;
	while(vars->envp[++i] != NULL)
	{
		key_val = ft_split(vars->envp[i], '=');
		if (ft_strncmp(key_val[0], middle, get_len(key_val[0], middle)) == 0)
		{
			ret = ft_strdup(key_val[1]);
			free_doublearray(key_val);
			return (ret);
		}
	}
	ret = ft_strdup("");
	return (ret);
}

char	*check_and_replace(t_vars *vars, char *str, int start, int end)
{
	char	*front;
	char	*middle;
	char	*rear;
	char	*replace;

	front = ft_substr(str, 0, start);
	rear = ft_substr(str, end, ft_strlen(str) - end);
	middle = ft_substr(str, start + 1, end - start - 1);
	free(str);
	replace = check_existance(vars, middle);
	replace = join_str(front, replace, rear);
	str = ft_strdup(replace);
	free(replace);
	return (str);
}

char	*expand_dollar(t_vars *vars, char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i] != 0)
	{
		if (str[i] == '$' && (str[i + 1] != 0 || str[i + 1] != ' '))
		{
			j = i + 1;
			while (str[j] != '\0' && str[j] != ' ')
				j++;
			str = check_and_replace(vars, str, i, j);
		}
	}
	return (str);
}

char	*get_readline(t_vars *vars, char *rdr_str)
{
	char	*temp_one;
	char	*temp_two;
	char	*str;

	str = NULL;
	while (1)
	{
		temp_one = readline("> ");
		temp_one = expand_dollar(vars, temp_one);
		if (temp_one == NULL)
			return (NULL);
		if (ft_strncmp(temp_one, rdr_str, get_len(temp_one, rdr_str)) == 0)
			break ;
		temp_two = ft_strjoin(temp_one, "\n");
		free(temp_one);
		temp_one = ft_strjoin(str, temp_two);
		if (str != NULL)
			free(str);
		free(temp_two);
		str = ft_strdup(temp_one);
		free(temp_one);
	}
	return (str);
}

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
	int					i;
	char				**hdoc_str;

	hdoc_str = ft_calloc(group->pipe_num, sizeof(char *));
	i = -1;
	while (++i < group->pipe_num)
	{
		hdoc_str[i] = handle_per_cmdlst(vars, group->cmdlst[i]);
		if (hdoc_str[i] == NULL)
			return (NULL);
	}
	return (hdoc_str);
}
