#include "minishell.h"

static size_t	count_words(char const *s)
{
	size_t	words;
	int		quote;

	quote = 1;
	words = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (*s == '"')
			quote *= -1;
		if (*s)
			words++;
		while ((*s != ' ' || (*s != '"' && quote == -1)) && *s)
			s++;
	}
	return (words);
}

char	**parse_split_args(char const *s)
{
	char	**splitstr;
	char	quote_type;
	size_t	start;
	size_t	end;
	size_t	i;

	splitstr = (char **)malloc(sizeof(char *) * (count_words(s) + 1));
	if (!s || !splitstr)
		return (0);
	start = 0;
	end = 0;
	i = 0;
	while (i < count_words(s))
	{
		while (s[start] == ' ')
			start++;
		if ((!quote_type && (s[start] == '"' || s[start] == '\'')) || s[start] == quote_type)
		{
			quote_type = s[start];
			end = ++start;
			while (s[end] != quote_type && s[end])
				end++;
		}
		else
		{
			end = start;
			while (s[end] != ' ' && s[end])
				end++;
		}
		splitstr[i] = ft_substr(s, start, end - start);
		start = end;
		i++;
	}
	splitstr[i] = 0;
	return (splitstr);
}

t_pipe	create_new_pipe(char *value)
{
	t_pipe	pipe;
	int		i;
	int		rdr_i;
	char	*formatted;
	char	*head;

	formatted = (char *)ft_calloc(ft_strlen(value) + 1, sizeof(char));
	pipe.rdr_info = (t_rdrinfo *)ft_calloc(1000, sizeof(t_rdrinfo));
	head = formatted;
	i = -1;
	rdr_i = 0;
	while (value[++i] != 0)
	{
		if (value[i] == '>')
			i = handle_rdr_out(i, value, &pipe.rdr_info[rdr_i++]);
		else if (value[i] == '<')
			i = handle_rdr_in(i, value, &pipe.rdr_info[rdr_i++]);
		else
			ft_memset(formatted++, value[i], 1);
	}
	pipe.rdr_count = rdr_i;
	pipe.arg = parse_split_args(head); // this is where you intepret quotes
	if (pipe.arg && pipe.arg[0])
	{
		pipe.cmd = pipe.arg[0];
		filter_exceptions(&pipe);
	}
	else
		pipe.cmd = NULL;
	return (pipe);
}

t_pipe	*generate_pipe_list(char *value, t_token *token)
{
	int		i;
	int		j;
	int		pipe_count;
	t_pipe	*cmdlst;
	char	*buffer;

	if (is_operator(value))
		return (NULL);
	cmdlst = (t_pipe *)malloc(sizeof(t_pipe) * (count_pipes(value) + 1));
	buffer = (char *)ft_calloc(1000, 1);
	i = 0;
	j = 0;
	pipe_count = 0;
	while (value[i] != 0)
	{
		if (value[i] == '|')
		{
			if (i == 0)
				write(2, "minishell: syntax error near unexpected token '|'\n", 50);
			if (buffer[0] != 0)
			{
				cmdlst[pipe_count++] = create_new_pipe(buffer);
				buffer = (char *)ft_calloc(1000, 1);
				j = 0;
			}
		}
		else
		{
			if (buffer[0] == 0 && value[i] == ' ')
			{
				i++;
				continue ;
			}
			buffer[j++] = value[i];
		}
		i++;
	}
	if (buffer[0] != 0)
		cmdlst[pipe_count++] = create_new_pipe(buffer);
	token->pipe_num = pipe_count;
	free(buffer);
	return (cmdlst);
}
