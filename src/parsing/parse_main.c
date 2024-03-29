/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:54:12 by zwong             #+#    #+#             */
/*   Updated: 2023/05/11 14:53:51 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pipe	prepare_subshell(t_pipe *pipe, char *head)
{
	pipe->has_subshell = TRUE;
	pipe->cmd = ft_trim_paren(head);
	pipe->arg = NULL;
	return (*pipe);
}

static void	loop_rdr_check(char *value, t_pipe *pipe, char *str, int *rdr_i)
{
	int	i;
	int	quote_t;
	int	paren;

	i = -1;
	quote_t = 0;
	paren = 0;
	while (value[++i] != 0)
	{
		quote_t = update_quote_t(quote_t, value[i]);
		if (!quote_t && update_paren_char(value[i], &paren) == 0)
		{
			if (value[i] == '>')
				assign_rdr_out_type(pipe, &i, value, rdr_i);
			else if (value[i] == '<')
				assign_rdr_in_type(pipe, &i, value, rdr_i);
			else
				*str++ = value[i];
		}
		else
			*str++ = value[i];
	}
}

t_pipe	create_new_pipe(char *value)
{
	t_pipe	pipe;
	char	*formatted;
	char	*head;

	formatted = (char *)ft_calloc(ft_strlen(value) + 3, sizeof(char));
	pipe.rdr_info = (t_rdrinfo *)ft_calloc(1000, sizeof(t_rdrinfo));
	head = formatted;
	pipe.rdr_count = 0;
	loop_rdr_check(value, &pipe, formatted, &pipe.rdr_count);
	head = ft_trim(head);
	free(value);
	if (head[0] == '(' && head[ft_strlen(head) - 1] == ')')
		return (prepare_subshell(&pipe, head));
	pipe.has_subshell = FALSE;
	pipe.arg = split_keep_quotes(ft_trim(head));
	if (pipe.arg && pipe.arg[0])
	{
		pipe.cmd = ft_strdup(pipe.arg[0]);
		filter_exceptions(&pipe);
	}
	else
		pipe.cmd = NULL;
	return (pipe);
}

void	handle_if_pipe(int *j, t_pipe *cmdlst, int *pipe_count, char **buffer)
{
	if ((*buffer)[0] != 0)
	{
		cmdlst[(*pipe_count)++] = create_new_pipe(ft_trim(*buffer));
		*buffer = (char *)ft_calloc(1000, 1);
		*j = 0;
	}
}

t_pipe	*generate_pipe_list(char *value, int *pipe_num)
{
	int		j;
	int		paren;
	t_pipe	*cmdlst;
	char	*buffer;
	char	quote_t;

	cmdlst = (t_pipe *)ft_calloc((count_pipes(value) + 1), sizeof(t_pipe));
	buffer = (char *)ft_calloc(1000, 1);
	j = 0;
	paren = 0;
	quote_t = 0;
	while (*value != 0)
	{
		quote_t = update_quote_t(quote_t, *value);
		if (!quote_t && update_paren_char(*value, &paren) == 0 && *value == '|')
			handle_if_pipe(&j, cmdlst, pipe_num, &buffer);
		else if (buffer[0] != 0 || *value != ' ')
			buffer[j++] = *value;
		value++;
	}
	if (buffer[0] != 0)
		cmdlst[(*pipe_num)++] = create_new_pipe(ft_trim(buffer));
	return (cmdlst);
}
