/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:55:41 by zwong             #+#    #+#             */
/*   Updated: 2023/05/10 17:55:52 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_rdr_out(int i, char *value, t_rdrinfo *rdr_info)
{
	int		j;
	char	quote_t;

	quote_t = 0;
	if (value[i] == '>')
		i++;
	while (value[i] == ' ')
		i++;
	if (!quote_t && ft_isquote(value[i]))
		quote_t = value[i++];
	j = i - 1;
	while (value[++j] != 0)
	{
		if ((!quote_t && (value[j + 1] == ' ' || value[j + 1] == '\0'))
			|| value[j + 1] == quote_t)
		{
			if (rdr_info->rdr_str)
				free(rdr_info->rdr_str);
			rdr_info->rdr_str = ft_substr(value, i, j++ - i + 1);
			break ;
		}
	}
	if (value[j] == 0)
		j -= 1;
	return (j);
}

int	handle_rdr_in(int i, char *value, t_rdrinfo *rdr_info)
{
	int		j;
	char	quote_t;

	quote_t = 0;
	if (value[i] == '<')
		i++;
	while (value[i] == ' ')
		i++;
	if (!quote_t && ft_isquote(value[i]))
		quote_t = value[i++];
	j = i - 1;
	while (value[++j] != 0)
	{
		if ((!quote_t && (value[j + 1] == ' ' || value[j + 1] == '\0'))
			|| value[j + 1] == quote_t)
		{
			if (rdr_info->rdr_str)
				free(rdr_info->rdr_str);
			rdr_info->rdr_str = ft_substr(value, i, j++ - i + 1);
			break ;
		}
	}
	if (value[j] == 0)
		j -= 1;
	return (j);
}

t_rdrinfo	*remove_rdr_from_list(t_rdrinfo *list, int index, int item_count)
{
	int			i;
	int			j;
	t_rdrinfo	*new_list;

	new_list = malloc(sizeof(t_rdrinfo) * (item_count + 1));
	i = -1;
	j = 0;
	while (++i < item_count)
	{
		if (i != index)
			new_list[j++] = list[i];
	}
	return (new_list);
}
