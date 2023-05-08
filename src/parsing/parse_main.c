/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:54:12 by zwong             #+#    #+#             */
/*   Updated: 2023/05/05 17:46:51 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pipe	prepare_subshell(t_pipe *pipe, char *value, char *formatted)
{
	pipe->has_subshell = TRUE;
	pipe->cmd = ft_trim_paren(value);
	pipe->arg = NULL;
	pipe->rdr_count = 0;
	free(formatted);
	return (*pipe);
}

static int	loop_rdr_check(char *value, t_pipe *pipe, char *formatted)
{
	int	i;
	int	rdr_i;
	int	quote_t;

	i = -1;
	rdr_i = 0;
	quote_t = 0;
	while (value[++i] != 0)
	{
		quote_t = update_quote_t(quote_t, value[i]);
		if (!quote_t && value[i] == '>')
		{
			pipe->rdr_info[rdr_i].rdr_type = OUT;
			if (value[++i] == '>')
				pipe->rdr_info[rdr_i].rdr_type = APPEND;
			i = handle_rdr_out(i, value, &pipe->rdr_info[rdr_i++]);
		}
		else if (!quote_t && value[i] == '<')
		{
			pipe->rdr_info[rdr_i].rdr_type = IN;
			if (value[++i] == '<')
				pipe->rdr_info[rdr_i].rdr_type = HEREDOC;
			i = handle_rdr_in(i, value, &pipe->rdr_info[rdr_i++]);
		}
		else
			ft_memset(formatted++, value[i], 1);
	}
	return (rdr_i);
}

t_pipe	create_new_pipe(char *value)
{
	t_pipe	pipe;
	char	*formatted;
	char	*head;

	formatted = (char *)ft_calloc(ft_strlen(value) + 1, sizeof(char));
	pipe.rdr_info = (t_rdrinfo *)ft_calloc(1000, sizeof(t_rdrinfo));
	head = formatted;
	if (value[0] == '(' && value[ft_strlen(value) - 1] == ')')
		return (prepare_subshell(&pipe, value, formatted));
	pipe.rdr_count = loop_rdr_check(value, &pipe, formatted);
	pipe.has_subshell = FALSE;
	pipe.arg = split_keep_quotes(head);
	if (pipe.arg && pipe.arg[0])
	{
		pipe.cmd = ft_strdup(pipe.arg[0]);
		filter_exceptions(&pipe);
	}
	else
		pipe.cmd = NULL;
	free(value);
	return (pipe);
}

void	handle_if_pipe(int *j, t_pipe *cmdlst, int *pipe_count, char **buffer)
{
	if (*j == 0)
		write(2, "minishell: syntax error near unexpected token '|'\n", 50);
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
