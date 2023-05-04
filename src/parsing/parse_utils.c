/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:50:55 by zwong             #+#    #+#             */
/*   Updated: 2023/05/04 11:22:32 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(char *value)
{
	int	i;
	int	count;
	int	paren;

	i = 0;
	count = 1;
	paren = 0;
	while (value[i] != 0)
	{
		if (value[i] == '(')
			paren++;
		else if (value[i] == ')')
			paren--;
		if (value[i] == '|' && paren == 0)
			count++;
		i++;
	}
	return (count);
}

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
	j = i;
	while (value[j] != 0)
	{
		if ((!quote_t && (value[j + 1] == ' ' || value[j + 1] == '\0'))
			|| value[j + 1] == quote_t)
		{
			if (rdr_info->rdr_str)
				free(rdr_info->rdr_str);
			rdr_info->rdr_str = ft_substr(value, i, j++ - i + 1);
			break ;
		}
		j++;
	}
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

void	filter_exceptions(t_pipe *pipe)
{
	int	i;

	if (ft_strcmp(pipe->cmd, "cat") != 0)
		return ;
	if (pipe->arg[1] != 0)
	{
		i = -1;
		while (++i < pipe->rdr_count)
		{
			if (pipe->rdr_info[i].rdr_type == IN)
			{
				free(pipe->rdr_info);
				pipe->rdr_info
					= remove_rdr_from_list(pipe->rdr_info, i, pipe->rdr_count);
			}
		}
	}
}

// void	print_pipe_info(t_pipe pipe)
// {
// 	int	i;

// 	i = -1;
// 	printf("RDR_COUNT is: %d\n", pipe.rdr_count);
// 	while (pipe.arg[++i])
// 		printf("Arg [%d]: %s\n", i, pipe.arg[i]);
// 	i = 0;
// 	while (i < pipe.rdr_count)
// 	{
// 		printf("INFO %d: %s", i, pipe.rdr_info[i].rdr_str);
// 		if (pipe.rdr_info[i].rdr_type == IN)
// 			printf(", IN\n\n");
// 		else if (pipe.rdr_info[i].rdr_type == OUT)
// 			printf(", OUT\n\n");
// 		else if (pipe.rdr_info[i].rdr_type == APPEND)
// 			printf(", APPEND\n\n");
// 		else if (pipe.rdr_info[i].rdr_type == HEREDOC)
// 			printf(", HEREDOC\n\n");
// 		i++;
// 	}
// }