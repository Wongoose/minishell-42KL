/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:50:55 by zwong             #+#    #+#             */
/*   Updated: 2023/05/10 17:55:56 by zwong            ###   ########.fr       */
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

void	assign_rdr_out_type(t_pipe *pipe, int *i, char *value, int *rdr_i)
{
	pipe->rdr_info[*rdr_i].rdr_type = OUT;
	if (value[++(*i)] == '>')
		pipe->rdr_info[*rdr_i].rdr_type = APPEND;
	*i = handle_rdr_out(*i, value, &pipe->rdr_info[(*rdr_i)++]);
}

void	assign_rdr_in_type(t_pipe *pipe, int *i, char *value, int *rdr_i)
{
	pipe->rdr_info[*rdr_i].rdr_type = IN;
	if (value[++(*i)] == '<')
		pipe->rdr_info[*rdr_i].rdr_type = HEREDOC;
	*i = handle_rdr_in(*i, value, &pipe->rdr_info[(*rdr_i)++]);
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